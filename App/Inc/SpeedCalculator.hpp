/********************************************************
* @file     SpeedCalculator.hpp
* @brief    Declare methods and classes related to speed 
*           calculation
* @details  This file contains class and methods declaration
*           related to speed calculation, include calculate 
*           speed and adjust speed.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#ifndef SPEED_CALCULATOR_HPP
#define SPEED_CALCULATOR_HPP

#include "DriveModeManager.hpp"
#include <string>

using namespace std;

/********************************************************
* @class SpeedCalculator
* @brief Class includes current speed, calculate speed
*        and adjust speed.
********************************************************/
class SpeedCalculator {
private:
    int currentSpeed;   /* Vehicle's current speed */
    int maxSpeedSport;  /* Maximum speed for Sport mode */
    int maxSpeedEco;    /* Maximum speed for Eco mode */

public:
    /********************************************************
    * @brief Constructor 
    ********************************************************/
    SpeedCalculator();

    /********************************************************
    * @brief Destructor 
    ********************************************************/
    ~SpeedCalculator();

    /********************************************************
    * @brief  Calculate speed base on brake and accelerator state
    * @param  isAccelerating  Accelerator state
    * @param  isBraking       Brake state
    * @return int     Return speed after check accelerator
    *                 and brake state
    ********************************************************/
    int calculateSpeed(bool isAccelerating, bool isBraking);

    /********************************************************
    * @brief  Get max speed base on drive mode
    * @param  driveMode   Drive mode to get max speed
    * @return int     Max speed
    ********************************************************/
    int getMaxSpeed(const DriveMode driveMode) const;

    /********************************************************
    * @brief  Adjust speed base on drive mode
    * @param  driveMode   Drive mode to adjust speed
    * @return int     Speed after adjust 
    ********************************************************/
    void adjustSpeedForDriveMode(const DriveMode driveMode);

    /********************************************************
    * @brief  Get current speed
    * @param  None
    * @return int     Return current speed
    ********************************************************/
    int getCurrentSpeed() const; 

    /********************************************************
    * @brief  Set current speed
    * @param  newSpeed    Value to set speed
    * @return None
    ********************************************************/
    void setCurrentSpeed(int newSpeed);  
};

#endif  /* SPEED_CALCULATOR_HPP */