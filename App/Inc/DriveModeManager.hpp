/********************************************************
* @file     DriveModeManager.hpp
* @brief    Declare methods and classes related to drive 
*           mode management
* @details  This file contains classes and methods declaration
*           related to drive mode management, include Eco 
*           and Sport mode, power output, limit speed. 
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#ifndef DRIVE_MODE_MANAGER_HPP
#define DRIVE_MODE_MANAGER_HPP

#include <string>
#include "DashboardController.hpp"

using namespace std;

/********************************************************
* @class DriveModeManager
* @brief Class manages drive mode (Eco or Sport) and its
*        power output, speed limit
********************************************************/
class DriveModeManager {
private:
    DriveMode currentDriveMode; /* Current drive mode */
    int powerOutputSport;       /* Output power for Sport mode */
    int powerOutputEco;         /* Output power for Eco mode */
    int maxEcoSpeed;            /* Maximum speed for Eco mode */
    
public:
    /********************************************************
    * @brief Constructor 
    ********************************************************/
    DriveModeManager();

    /********************************************************
    * @brief Destructor 
    ********************************************************/
    ~DriveModeManager();

    /********************************************************
    * @brief  Set drive mode
    * @param  mode    Mode that want to set drive mode
    * @return None
    ********************************************************/
    void setDriveMode(DriveMode mode);

    /********************************************************
    * @brief  Get power output base on mode
    * @param  None
    * @return int     Power output of Eco or Sport mode
    ********************************************************/
    int getPowerOutput() const;

    /********************************************************
    * @brief  Limit speed for Eco mode
    * @param  currentSpeed    Current speed
    * @return int     Return current speed or max Eco speed
    ********************************************************/
    int limitSpeedForEcoMode(int currentSpeed) const;

    /********************************************************
    * @brief  Get current drive mode
    * @param  None
    * @return DriveMode   Return drive mode(ECO or SPORT)
    ********************************************************/
    DriveMode getCurrentDriveMode() const;
};

#endif  /* DRIVE_MODE_MANAGER_HPP */