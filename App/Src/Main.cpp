/********************************************************
* @file     Main.cpp
* @brief    Main program
* @details  This file contains the main program use 
*           multithreading to display data (speed, mode, 
*           battery level,...), data will be updated to
*           display when use keyboard to adjust parameters
*           (accelerator, brake, ...).
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#include "Main.hpp"

using namespace std;

/********************************************************
* @brief Variable mutex ensures only one thread can access 
*        DashboardController object at a time
********************************************************/

mutex mtx;

/********************************************************
* @brief Variable in the functions that use for create 
*        thread and can stop the loop when this variable 
*        is false 
********************************************************/
atomic<bool> isRunning(true);
void readCSV(DashboardController* dashboardController);
void keyboardInputHandler(DashboardController* dashboardController, SpeedCalculator* speedCalculator, 
    DriveModeManager* driveMode, SafetyManager* safetyManager, BatteryManager* batteryManager);
void display(DashboardController *dashboardController);
void saveToCSV(DashboardController* dashboardController);
/********************************************************
* @brief Main function
********************************************************/
int main() 
{
    /* Initialize system component object */ 
    DashboardController dashboardController;
    DisplayManager displayManager(&dashboardController);
    SpeedCalculator speedCalculator;
    BatteryManager batteryManager;
    DriveModeManager driveModeManager;
    SafetyManager safetyManager;

    /* Register DisplayManager object to Observer */  
    dashboardController.registerObserver(&displayManager);

    /* Create threads */ 
    thread t1(readCSV, &dashboardController);
    
    thread t2(keyboardInputHandler, &dashboardController, 
                &speedCalculator, &driveModeManager, 
                &safetyManager, &batteryManager);

    thread mainTask(display, &dashboardController);

    t1.join();
    t2.join();
    mainTask.join();
	
    return 0;
}

/********************************************************
* @brief    readCSV
* @details  This function reads data from CSV file and 
*           update data to DashboardController.
* @param    dashboardController Pointer to DashboardController 
*                               object that receive updated data
* @return   None 
********************************************************/
void readCSV(DashboardController* dashboardController) {
    // Check NULL pointer 
    if (!dashboardController) {
        return;
    }

    while(isRunning)
    {
        // Lock
        unique_lock<mutex> lock(mtx);

        ifstream file(DATABASE_PATH);
        if (!file.is_open()) {
            cerr << "Cannot open file " << DATABASE_PATH << endl;
            return;
        }

        // Map stores system parameters and its values 
        unordered_map<string, string> data; 
        string line, key, value;

        // Read each line and save the parameters and values ​​into the map as string
        while (getline(file, line)) {
            stringstream ss(line);
            if (getline(ss, key, ',') && getline(ss, value, ',')) { 
                data[key] = value;
            }
        }

        file.close();

        /* Find paramters and save the correspond value */

        // Speed
        if (data.find("SPEED") != data.end()) {
            int newSpeed = stoi(data["SPEED"]);

            if (newSpeed >= 0) {
                dashboardController->setSpeed(newSpeed);
            }
        }

        // Drive mode
        if (data.find("DRIVE MODE") != data.end()) {
            string newDriveMode = data["DRIVE MODE"];
            
            if (newDriveMode == "ECO") {
                dashboardController->setDriveMode(ECO);
            }

            if (newDriveMode == "SPORT") {
                dashboardController->setDriveMode(SPORT);
            }
        }

        // Battery level
        if (data.find("BATTERY LEVEL") != data.end()) {
            int newLevel = stoi(data["BATTERY LEVEL"]);

            if (newLevel >= 0 && newLevel <= 100) {
                dashboardController->setBatteryLevel(newLevel);
            }
        }

        // AC temperature
        if (data.find("AC TEMPERATURE") != data.end()) {
            int newTemp = stoi(data["AC TEMPERATURE"]);

            if (newTemp >= 0) {
                dashboardController->setAcTemp(newTemp);
            }
        }

        // Wind level
        if (data.find("WIND LEVEL") != data.end()) {
            int newLevel = stoi(data["WIND LEVEL"]);

            if (newLevel >= 0) {
                dashboardController->setAcTemp(newLevel);
            }
        }

        // Remaining range
        if (data.find("REMAINING RANGE") != data.end()) {
            double newRemainingRange = stod(data["REMAINING RANGE"]);

            if (newRemainingRange >= 0.0) {
                dashboardController->setRemainingRange(newRemainingRange);
            }
        }

        delay_ms(1000);

        // Unlock
        lock.unlock();
    }
}

/********************************************************
* @brief    keyboardInputHandler
* @details  This function handles input from keyboard, 
*           new data will updated to DashboardController
*           and save this data to CSV file.
* @param    dashboardController Pointer to DashboardController object
* @param    speedCalculator     Pointer to SpeedCalculator object    
* @param    driveMode           Pointer to DriveModeManager object
* @param    safetyManager       Pointer to SafetyManager object    
* @param    batteryManager      Pointer to BatteryManager object
* @return   None
********************************************************/
void keyboardInputHandler(DashboardController* dashboardController, SpeedCalculator* speedCalculator, 
    DriveModeManager* driveMode, SafetyManager* safetyManager, BatteryManager* batteryManager) {
    
    // Check NULL pointer
    if (!dashboardController || !speedCalculator || !driveMode || !safetyManager) {
        return;
    }

    // Map stores state of keys that use for change data
    unordered_map<char, bool> keyStates; 

    // Initial variables use for calculate data per 100ms and save into DashboardController
    bool isAccelerating = false;
    bool isBraking = false;  
    int acTemp = dashboardController->getAcTemp();
    int windLevel = dashboardController->getWindLevel();
    int speed = dashboardController->getSpeed();
    DriveMode mode = dashboardController->getDriveMode();
    int batteryLevel = dashboardController->getBatteryLevel();
    double remainingRange = dashboardController->getRemainingRange();

    speedCalculator->setCurrentSpeed(speed);
    driveMode->setDriveMode(mode);

    while (isRunning)
    {
        /* Check key states and process paramters remotely change via keyboard */ 

        // Accelerator
        if (GetAsyncKeyState('A') & 0x8000) {  // Key 'a' is pressed
            keyStates['a'] = true;  // Mark key 'a' is pressed
            isAccelerating = true;
            isBraking = false;
            
            // Accelerator is pressed, brake is not pressed
            speed = speedCalculator->calculateSpeed(true, false);   

            if (driveMode->getCurrentDriveMode() == ECO) {
                speedCalculator->adjustSpeedForDriveMode(ECO);
            } else {
                speedCalculator->adjustSpeedForDriveMode(SPORT);
            }
            
            speed = speedCalculator->getCurrentSpeed();
        } else {
            keyStates['a'] = false; // Reset state if key is not pressed
            isAccelerating = false;
        }

        // Brake
        if (GetAsyncKeyState('B') & 0x8000) {  // Key 'b' is pressed
            keyStates['b'] = true;  // Mark key 'b' is pressed
            isBraking = true;
            isAccelerating = false;
            
            // Accelerator is not pressed, brake is pressed
            speed = speedCalculator->calculateSpeed(false, true);   
        } else {
            keyStates['b'] = false; // Reset state if key is not pressed
            isBraking = false;
        }
        
        // Accelerator and brake are both not pressed 
        if (!keyStates['a'] && !keyStates['b']) {   // Key 'a' and 'b' are both not pressed
            isAccelerating = false;
            isBraking = false;

            // Accelerator and brake are both not pressed
            speed = speedCalculator->calculateSpeed(false, false);  
        }

        // Drive mode
        if (GetAsyncKeyState('M') & 0x8000) {  // Key 'b' is pressed
                keyStates['m'] = true;  // Mark key 'm' is pressed

                if (driveMode->getCurrentDriveMode() == ECO) {
                    driveMode->setDriveMode(SPORT);
                } else {
                    driveMode->setDriveMode(ECO);
                }
                mode = driveMode->getCurrentDriveMode();
            
        } else {
            keyStates['m'] = false; // Reset state if key is not pressed
        }

        // Turn up AC temperature
        if (GetAsyncKeyState(VK_UP) & 0x8000) {  // Key UP arrow is pressed
            if (!keyStates[VK_UP]) {  
                acTemp = min(acTemp + 1, 30);  // Turn up AC temperature, max 30°C
                keyStates[VK_UP] = true;  
            }
        } else {
            keyStates[VK_UP] = false;  // Reset state if key is not pressed
        }

        // Turn down AC temperature
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {  // Key DOWN arrow is pressed
            if (!keyStates[VK_DOWN]) { 
                acTemp = max(acTemp - 1, 16);  // Turn down AC temperature, min 16°C
                keyStates[VK_DOWN] = true;  
            }
        } else {
            keyStates[VK_DOWN] = false;  // Reset state if key is not pressed
        }

        // Turn up wind level
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {  // Key RIGHT arrow is pressed
            if (!keyStates[VK_RIGHT]) { 
                windLevel = min(windLevel + 1, 5);  // Turn up wind level, max level 5
                keyStates[VK_RIGHT] = true;  
            }
        } else {
            keyStates[VK_RIGHT] = false;  // Reset state if key is not pressed
        }

        // Turn down wind level
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {  // Key LEFT arrow is pressed
            if (!keyStates[VK_LEFT]) {  
                windLevel = max(windLevel - 1, 1);  // Turn down wind level, min level 1
                keyStates[VK_LEFT] = true;  
            }
        } else {
            keyStates[VK_LEFT] = false;  // Reset state if key is not pressed
        }
        
        /* Other paramters */

        // Battery level 
        batteryManager->updateBatteryLevel(speed, acTemp, windLevel);
        batteryLevel = batteryManager->getBatteryLevel();
        
        if (batteryLevel == 0) {
            speed = 0;
        }

        // Remaining range
        remainingRange = batteryManager->calculateRamainingRange();

        // Update new data to DashboardController
        dashboardController->setDriveMode(mode);
        dashboardController->setSpeed(speed);
        dashboardController->setAcTemp(acTemp);
        dashboardController->setWindLevel(windLevel);
        dashboardController->setBatteryLevel(batteryLevel);
        dashboardController->setRemainingRange(remainingRange);

        // Save new data into CSV file
        saveToCSV(dashboardController);

        delay_ms(100);
    }

}

/********************************************************
* @brief    display
* @details  This function calls DashboardController update
*           data methods to display data from DisplayManager. 
* @param    dashboardController Pointer to DashboardController 
*                               object to display updated data
* @return   None
********************************************************/
void display(DashboardController *dashboardController) {
    while (isRunning)
    {
        dashboardController->updateData();

        // Warning if battery level is low
        if (dashboardController->getBatteryLevel() <= 20) {
            cout << "Warning: Low Battery. Find a Charging Station!" << endl << endl;
        }

        delay_ms(1000);
    }
    
}

/********************************************************
* @brief    saveToCSV
* @details  This functions save data into CSV file, include
*           drive mode, speed, battery level,...
* @param    dashboardController Pointer to DashboardController 
*                               object to read and save data
* @return   None
********************************************************/
void saveToCSV(DashboardController* dashboardController) {
    ofstream file(DATABASE_PATH);
    if (file.is_open()) {
        file << "DRIVE MODE, " << (dashboardController->getDriveMode() == ECO ? "ECO" : "SPORT")  << endl;
        file << "SPEED, " << dashboardController->getSpeed() << endl;
        file << "BATTERY LEVEL, " << dashboardController->getBatteryLevel() << endl;
        file << "AC TEMPERATURE, " << dashboardController->getAcTemp() << endl;
        file << "WIND LEVEL, " << dashboardController->getWindLevel() << endl;
        file << "REMAINING RANGE, " << dashboardController->getRemainingRange() << endl;

        file.close();
    } else {
        cerr << "Failed to open Database.csv for writing." << endl;
    }
}
