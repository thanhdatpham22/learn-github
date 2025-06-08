/********************************************************
* @file     BatteryManager.hpp
* @brief    Declare methods and classes related to battery 
*           management
* @details  This file contains class and methods declaration
*           related to battery management, stores parameters 
*           related to battery.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#ifndef BATTERY_MANAGER_HPP
#define BATTERY_MANAGER_HPP

#include <iostream>

using namespace std;

/********************************************************
* @class BatteryManager
* @brief Class includes and calculate parameters related  
*        to battery
********************************************************/
class BatteryManager {
private:
    int batteryLevel;       /* Current battery level (%) */
    double batteryCapacity; /* Maximum battery capacity (kWh) */
    double drainPerKm;      /* Battery consumption per kilometer (kWh/km) */
    
public:
    /********************************************************
    * @brief Constructor 
    ********************************************************/
    BatteryManager();

    /********************************************************
    * @brief Destructor 
    ********************************************************/
    ~BatteryManager();

    /********************************************************
    * @brief  Calculate battery drain per 1 second  
    * @param  speed       Current speed
    * @param  acLevel     Current AC temperature
    * @param  windLevel   Current wind level
    * @return double  Total drain per 1 second
    ********************************************************/
    double calculateBatteryDrain(int speed, int acLevel, int windLevel);

    /********************************************************
    * @brief   Predict ramaining range
    * @param   None
    * @return  double  Predicted remaining range 
    ********************************************************/
    double calculateRamainingRange() const;

    /********************************************************
    * @brief  Update battery level
    * @param  speed       Current speed
    * @param  acLevel     Current AC temperature
    * @param  windLevel   Current wind level
    * @return None
    ********************************************************/
    void updateBatteryLevel(int speed, int acLevel, int windLevel);

    /********************************************************
    * @brief  Get current battery level 
    * @param  None
    * @return int     Return current battery level
    ********************************************************/
    int getBatteryLevel() const;
};

#endif  /* BATTERY_MANAGER_HPP */ 