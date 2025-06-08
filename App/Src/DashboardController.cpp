/********************************************************
* @file     DashboardController.cpp
* @brief    Define methods related to dashboard controller
* @details  This file contains methods definition related
*           to dashboard controller includes getters, setters,
*           update data and notify to all registered observers.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#include "DashboardController.hpp"

using namespace std;

/********************************************************
* @brief Constructor 
********************************************************/
DashboardController::DashboardController() : speed(0), driveMode(ECO), 
    batteryLevel(100), remainingRange(400.0), acTemp(25), windLevel(0) {}

/********************************************************
* @brief Destructor
********************************************************/
DashboardController::~DashboardController() {
    observers.clear();
}

/********************************************************
* @brief    getSpeed
* @details  This method gets current speed.
* @param    None
* @return   int     Return current speed 
********************************************************/
int DashboardController::getSpeed() const {
    return speed;
}

/********************************************************
* @brief    getDriveMode
* @details  This method gets drive mode.
* @param    None
* @return   DriveMode     Return current drive mode
********************************************************/
DriveMode DashboardController::getDriveMode() const {
    return driveMode;
}

/********************************************************
* @brief    getBatteryLevel
* @details  This method gets battery level.
* @param    None
* @return   int     Return current battery level  
********************************************************/
int DashboardController::getBatteryLevel() const {
    return batteryLevel;
}

/********************************************************
* @brief    getRemainingRange
* @details  This method gets remaining range.
* @param    None
* @return   double  Return current remaining range
********************************************************/
double DashboardController::getRemainingRange() const {
    return remainingRange;
}

/********************************************************
* @brief    getAcTemp
* @details  This method gets AC temperature.
* @param    None
* @return   int     Return current AC temperature
********************************************************/
int DashboardController::getAcTemp() const {
    return acTemp;
}

/********************************************************
* @brief    getWindLevel
* @details  This method gets wind level.
* @param    None
* @return   int     Return current wind level
********************************************************/
int DashboardController::getWindLevel() const {
    return windLevel;
}

/********************************************************
* @brief    setSpeed
* @details  This method sets new speed.
* @param    newSpeed    Value to set new speed  
* @return   None
********************************************************/
void DashboardController::setSpeed(int newSpeed) {
    if (newSpeed < 0) {
        speed = 0;
    }
    speed = newSpeed;
}

/********************************************************
* @brief    setDriveMode
* @details  This method sets new drive mode.
* @param    newDriveMode    Mode to set new drive mode 
* @return   None
********************************************************/
void DashboardController::setDriveMode(DriveMode newDriveMode) {
    driveMode = newDriveMode;
}

/********************************************************
* @brief    setBatteryLevel
* @details  This method sets new battery level.
* @param    newLevel    Value to set new battery level 
* @return   None
********************************************************/
void DashboardController::setBatteryLevel(int newLevel) {
    if (newLevel < 0 || newLevel > 100) {
        return;
    }
    batteryLevel = newLevel;
}

/********************************************************
* @brief    setRemainingRange
* @details  This method sets remaining range.
* @param    newRemainingRange   Value to set remaining range 
* @return   None
********************************************************/
void DashboardController::setRemainingRange(double newRemainingRange) {
    remainingRange = newRemainingRange;
}

/********************************************************
* @brief    setAcTemp
* @details  This method sets new AC temperature.
* @param    newTemp    Value to set new AC temperature  
* @return   None
********************************************************/
void DashboardController::setAcTemp(int newTemp) {
    if (newTemp < 16 || newTemp > 30) {
        return;
    }
    acTemp = newTemp;
}

/********************************************************
* @brief    setWindLevel
* @details  This method sets new wind level.
* @param    newLevel    Value to set new wind level  
* @return   None
********************************************************/
void DashboardController::setWindLevel(int newLevel) {
    if (newLevel < 0 || newLevel > 5) {
        return;
    }
    windLevel = newLevel;
}

/********************************************************
* @brief    updateData
* @details  This method reads data from CSV file, updates
*           new data to system parameters and notifies to
*           observers to update new data.
* @param    None
* @return   None
********************************************************/
void DashboardController::updateData()
{
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
            speed = newSpeed;
        }
    }

    // Drive mode
    if (data.find("DRIVE MODE") != data.end()) {
        string newDriveMode = data["DRIVE MODE"];
        
        if (newDriveMode == "ECO") {
            driveMode = ECO;
        }

        if (newDriveMode == "SPORT") {
            driveMode = SPORT;
        }
    }

    // Battery level
    if (data.find("BATTERY LEVEL") != data.end()) {
        int newBatteryLevel = stoi(data["BATTERY LEVEL"]);

        if (newBatteryLevel >= 0 && newBatteryLevel <= 100) {
            batteryLevel = newBatteryLevel;
        }
    }

    // AC temperature
    if (data.find("AC TEMPERATURE") != data.end()) {
        int newTemp = stoi(data["AC TEMPERATURE"]);

        if (newTemp >= 0) {
            acTemp = newTemp;
        }
    }

    // Wind level
    if (data.find("WIND LEVEL") != data.end()) {
        int newLevel = stoi(data["WIND LEVEL"]);

        if (newLevel >= 0) {
            windLevel = newLevel;
        }
    }

    // Remaining range
    if (data.find("REMAINING RANGE") != data.end()) {
        double newRemainingRange = stod(data["REMAINING RANGE"]);

        if (newRemainingRange >= 0.0) {
            remainingRange = newRemainingRange;
        }
    }

    // Notify to all observers
    notifyObservers();
}

/********************************************************
* @brief    registerObserver
* @details  This method registers observer to the list of 
*           observes.
* @param    observer  Pointer to object to register observer
* @return   None
********************************************************/
void DashboardController::registerObserver(Observer *observer) {
    observers.push_back(observer);
}

/********************************************************
* @brief    removeObserver
* @details  This method removes observer from the list of 
*           observes.
* @param    observer  Pointer to object to remove observer
* @return   None
********************************************************/
void DashboardController::removeObserver(Observer *observer) {
    vector<Observer*>::iterator it;

    for (it = observers.begin(); it != observers.end(); it++) {
        if (*it == observer) {
            observers.erase(it);
        }
    }
}

/********************************************************
* @brief    notifyObservers
* @details  This method notifies to all observes in the 
*           list about new updated data.
* @param    None
* @return   None
********************************************************/
void DashboardController::notifyObservers() const {
    for (auto observer : observers) {
        observer->update();
    }
}