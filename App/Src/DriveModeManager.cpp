/********************************************************
* @file     DashboardController.cpp
* @brief    Define methods related to drive mode management
* @details  This file contains methods definition related
*           to drive mode management, includes getters, setters,
*           limit speed.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#include "DriveModeManager.hpp"

using namespace std;

/********************************************************
* @brief Constructor
********************************************************/
DriveModeManager::DriveModeManager() : currentDriveMode(ECO), 
    powerOutputSport(300), powerOutputEco(220), maxEcoSpeed(150) {}

/********************************************************
* @brief Destructor
********************************************************/
DriveModeManager::~DriveModeManager() {}

/********************************************************
* @brief    setDriveMode
* @details  This method sets drive mode.
* @param    mode    Mode that want to set drive mode
* @return   None
********************************************************/
void DriveModeManager::setDriveMode(DriveMode mode) {
    currentDriveMode = mode;
}

/********************************************************
* @brief    getPowerOutput
* @details  This method gets power output base on mode.
* @param    None
* @return   int     Power output of Eco or Sport mode
********************************************************/
int DriveModeManager::getPowerOutput() const {
    if (currentDriveMode == ECO) {
        return powerOutputEco;
    }
    return powerOutputSport;
}

/********************************************************
* @brief    limitSpeedForEcoMode
* @details  This method limits speed for Eco mode, Eco mode
*           has power output lower than Sport mode so max
*           speed is lower than Sport mode.
* @param    currentSpeed    Current speed
* @return   int     Return current speed or max Eco speed
********************************************************/
int DriveModeManager::limitSpeedForEcoMode(int currentSpeed) const {
    if (currentSpeed > maxEcoSpeed) {
        currentSpeed = maxEcoSpeed;
    }
    return currentSpeed;
}

/********************************************************
* @brief    getCurrentDriveMode
* @details  This method gets current drive mode.
* @param    None
* @return   DriveMode   Return drive mode(ECO or SPORT)
********************************************************/
DriveMode DriveModeManager::getCurrentDriveMode() const {
    return currentDriveMode;
}