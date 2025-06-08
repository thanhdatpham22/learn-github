/********************************************************
* @file     BatteryManager.cpp
* @brief    Define methods and classes related to battery 
*           management
* @details  This file contains methods definition related 
*           to battery management, includes calculate drain,
*           calculate remaining range, update battery level.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#include "BatteryManager.hpp"

using namespace std;

/********************************************************
* @brief Constructor
********************************************************/
BatteryManager::BatteryManager() : batteryLevel(100), batteryCapacity(90), drainPerKm(0.2) {}

/********************************************************
* @brief Destructor
********************************************************/
BatteryManager::~BatteryManager() {}

/********************************************************
* @brief    calculateBatteryDrain
* @details  This method calculates battery drain per 1 second   
*           base on speed, AC temperature, wind level.
* @param    speed       Current speed
* @param    acLevel     Current AC temperature
* @param    windLevel   Current wind level
* @return   double  Total drain per 1 second
********************************************************/
double BatteryManager::calculateBatteryDrain(int speed, int acLevel, int windLevel) {
    // Basic drain
    double baseDrain = drainPerKm; 

    // Drain related to speed
    double speedFactor = 1.0 + (speed / 100.0); 

     // Drain related to AC, increase 5% if increase AC temperature 1 °C
    double acFactor = 1.0 + ((acLevel - 15) * 0.05);    

    // Drain related to wind level, increase 2% if  increase wind 1 level  
    double windFactor = 1.0 + (windLevel * 0.02);   

    // Total drain per 1 second
    return baseDrain * speedFactor * acFactor * windFactor;
}

/********************************************************
* @brief    calculateRamainingRange
* @details  This method predicts ramaining range base on
*           battery level and battery drain.
* @param    None
* @return   double  Predicted remaining range 
********************************************************/
double BatteryManager::calculateRamainingRange() const {
    if (drainPerKm <= 0) {
        return 0.0;
    } 

    return (batteryLevel / 100.0) * (batteryCapacity / drainPerKm);
}

/********************************************************
* @brief    updateBatteryLevel
* @details  This method updates battery level base on speed, 
*           AC temperature, wind level.
* @param    speed       Current speed
* @param    acLevel     Current AC temperature
* @param    windLevel   Current wind level
* @return   None
********************************************************/
void BatteryManager::updateBatteryLevel(int speed, int acLevel, int windLevel) {
    double drainPerSecond = calculateBatteryDrain(speed, acLevel, windLevel);

    // Decrease battery level per 100 ms, battery level alway >= 0
    batteryLevel = max(0.0, batteryLevel - drainPerSecond * 0.1);   
}

/********************************************************
* @brief    getBatteryLevel
* @details  This method gets current battery level.
* @param    None
* @return   int     Return current battery level
********************************************************/
int BatteryManager::getBatteryLevel() const {
    return batteryLevel;
}