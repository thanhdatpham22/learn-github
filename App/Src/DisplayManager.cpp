/********************************************************
* @file     DisplayManager.cpp
* @brief    Define methods related to display management
* @details  This file contains methods definition related
*           to display management includes update data from
*           DashboardController and display data.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#include "DisplayManager.hpp"

using namespace std;

/********************************************************
* @brief Constructor
* @param dashboardController  Pointer to dashboard controller
*                             to get update data and display    
********************************************************/
DisplayManager::DisplayManager(DashboardController* dashboardController) 
    : dashboardController(dashboardController) {}

/********************************************************
* @brief Destructor
********************************************************/
DisplayManager::~DisplayManager() {}

/********************************************************
* @brief    updateDisplay
* @details  This method displays updated data, include
*           drive mode, speed, battery level, AC temperature,
*           wind level, remaining range. 
* @param    None
* @return   None
********************************************************/
void DisplayManager::updateDisplay() {
    showDriveMode();
    showSpeed();
    showBatteryStatus();
    showClimateStatus();
    showWindLevel();
    showRemainingRange();
    cout << endl;
}

/********************************************************
* @brief    showSpeed
* @details  This methods displays speed data.
* @param    None
* @return   None
********************************************************/
void DisplayManager::showSpeed() {
    cout << "Speed: " << dashboardController->getSpeed() << " km/h" << endl;
}

/********************************************************
* @brief    showDriveMode
* @details  This methods displays drive mode.
* @param    None
* @return   None
********************************************************/
void DisplayManager::showDriveMode() {
    cout << "Drive mode: " << (dashboardController->getDriveMode() == ECO ? "ECO" : "SPORT") << endl;
}

/********************************************************
* @brief    showBatteryStatus
* @details  This methods displays battery level.
* @param    None
* @return   None
********************************************************/
void DisplayManager::showBatteryStatus() {
    cout << "Battery level: " << dashboardController->getBatteryLevel() << " %" << endl;
}

/********************************************************
* @brief    showClimateStatus
* @details  This methods displays AC temperature.
* @param    None
* @return   None
********************************************************/
void DisplayManager::showClimateStatus() {
    cout << "A/C temperature: " << dashboardController->getAcTemp() << " °C" << endl;
}

/********************************************************
* @brief    showWindLevel
* @details  This methods displays wind level.
* @param    None
* @return   None
********************************************************/
void DisplayManager::showWindLevel() {
    cout << "Wind level: " << dashboardController->getWindLevel() << endl;
}

/********************************************************
* @brief    showRemainingRange
* @details  This methods displays remaining range.
* @param    None
* @return   None
********************************************************/
void DisplayManager::showRemainingRange() {
    cout << "Remaining range: " << dashboardController->getRemainingRange() << " km" << endl;
}

/********************************************************
* @brief    update
* @details  This method will be called when Dashboard
*           Controller update data and notify to observer  
*           Display Manager.
* @param    None
* @return   None
********************************************************/
void DisplayManager::update() {
    updateDisplay();
}