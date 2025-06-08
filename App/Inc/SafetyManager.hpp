/********************************************************
* @file     SafetyManager.hpp
* @brief    Declare methods and classes related to safety 
*           management
* @details  This file contains class and methods declaration
*           related to safety management base on brake state.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#ifndef SAFETY_MANAGER_HPP
#define SAFETY_MANAGER_HPP

#include <chrono>
#include <thread>

using namespace std;

/********************************************************
* @class SafetyManager
* @brief Class manages safety base on brake state
********************************************************/
class SafetyManager {
private:
    bool brakeApplied;  /* Brake state */
    int brakeIntensity; /* Intensity of deceleration when braking (m/s^2) */
    int currentSpeed;   /* Vehicle's current speed (updated when braking) (km/h) */

public:
    /********************************************************
    * @brief Constructor 
    ********************************************************/
    SafetyManager();

    /********************************************************
    * @brief Destructor 
    ********************************************************/
    ~SafetyManager();

    /********************************************************
    * @brief  Check accelerator and brake state
    * @param  isAccelerating  Accelerator state
    * @param  isBraking       Brake state
    * @return bool    Return true if accelerator and brake 
    *                 are pressed at the same time, else 
    *                 return false
    ********************************************************/
    bool checkBrakeAndAccelerator(bool isAccelerating, bool isBraking);

    /********************************************************
    * @brief  Apply brake and calculate speed after brake is 
    *         applied
    * @param  None
    * @return None
    ********************************************************/
    void applyBrake();

    /********************************************************
    * @brief  Release brake
    * @param  None
    * @return None
    ********************************************************/
    void releaseBrake();

    /********************************************************
    * @brief  Check if brake is applied.
    * @param  None
    * @return bool    Return true if brake is applied
    *                   Return false if brake is not applied
    ********************************************************/
    bool isBrakeApplied() const;
};

/********************************************************
* @brief  Delay time by milliseconds
* @param  milliseconds    Delay time by milliseconds
* @return None
********************************************************/
void delay_ms(int milliseconds);

#endif  /* SAFETY_MANAGER_HPP */