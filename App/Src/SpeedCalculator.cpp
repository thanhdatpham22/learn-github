/********************************************************
* @file     SpeedCalculator.cpp
* @brief    Define methods related to speed calculation
* @details  This file contains methods definition related
*           to speed calculation, include calculate speed
*           and adjust speed.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#include "SpeedCalculator.hpp"

using namespace std;

/********************************************************
* @brief Constructor
********************************************************/
SpeedCalculator::SpeedCalculator() 
    : currentSpeed(0), maxSpeedSport(200), maxSpeedEco(150) {}

/********************************************************
* @brief Destructor
********************************************************/
SpeedCalculator::~SpeedCalculator() {}

/********************************************************
* @brief    calculateSpeed
* @details  This method calculates speed base on brake 
*           and accelerator state.
* @param    isAccelerating  Accelerator state
* @param    isBraking       Brake state
* @return   int     Return speed after check accelerator
*                   and brake state
********************************************************/
int SpeedCalculator::calculateSpeed(bool isAccelerating, bool isBraking) {
    if (isAccelerating && !isBraking) {
        currentSpeed += 2;
    }

    if (isBraking && !isAccelerating) {
        currentSpeed -= 2;
    }

    if (!isBraking && !isAccelerating) {
        currentSpeed -= 1;
    }

    if (currentSpeed < 0) {
        currentSpeed = 0;
    }
    
    return currentSpeed;
}

/********************************************************
* @brief    getMaxSpeed
* @details  This method gets max speed base on drive mode.
* @param    driveMode   Drive mode to get max speed
* @return   int     Max speed
********************************************************/
int SpeedCalculator::getMaxSpeed(const DriveMode driveMode) const {
    if (driveMode == ECO) {
        return maxSpeedEco;
    } 
    return maxSpeedSport;
}

/********************************************************
* @brief    adjustSpeedForDriveMode
* @details  This method adjusts speed base on drive mode.
* @param    driveMode   Drive mode to adjust speed
* @return   int     Speed after adjust 
********************************************************/
void SpeedCalculator::adjustSpeedForDriveMode(const DriveMode driveMode) {
    if (driveMode == ECO) {
        if (currentSpeed > maxSpeedEco) {
            currentSpeed = maxSpeedEco;
        }
    }

    if (driveMode == SPORT) {
        if (currentSpeed > maxSpeedSport) {
            currentSpeed = maxSpeedSport;
        }
    }
}

/********************************************************
* @brief    getCurrentSpeed
* @details  This method gets current speed
* @param    None
* @return   int     Return current speed
********************************************************/
int SpeedCalculator::getCurrentSpeed() const {
    return currentSpeed;
}

/********************************************************
* @brief    setCurrentSpeed
* @details  This method sets speed.
* @param    newSpeed    Value to set speed
* @return   None
********************************************************/
void SpeedCalculator::setCurrentSpeed(int newSpeed) {
    currentSpeed = newSpeed;
}