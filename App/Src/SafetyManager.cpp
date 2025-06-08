/********************************************************
* @file     SafetyManager.cpp
* @brief    Define methods related to safety management
* @details  This file contains methods definition related
*           to safety management includes check brake state,
*           calculate speed when brake is applied.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#include "SafetyManager.hpp"

using namespace std;

/********************************************************
* @brief Constructor 
********************************************************/
SafetyManager::SafetyManager() 
    : brakeApplied(false), brakeIntensity(0), currentSpeed(0) {}

/********************************************************
* @brief Destructor
********************************************************/
SafetyManager::~SafetyManager() {}

/********************************************************
* @brief    checkBrakeAndAccelerator
* @details  This method checks accelerator and brake state.
* @param    isAccelerating  Accelerator state
* @param    isBraking       Brake state
* @return   bool    Return true if accelerator and brake 
*                   are pressed at the same time, else 
*                   return false
********************************************************/
bool SafetyManager::checkBrakeAndAccelerator(bool isAccelerating, bool isBraking) {
    return isAccelerating & isBraking;
}

/********************************************************
* @brief    applyBrake
* @details  This method applies brake and calculate speed
*           after brake is applied.
* @param    None
* @return   None
********************************************************/
void SafetyManager::applyBrake() {
    if (brakeApplied) {
        currentSpeed -= brakeIntensity * 1; 
    }
}

/********************************************************
* @brief    releaseBrake
* @details  This method releases brake.
* @param    None
* @return   None
********************************************************/
void SafetyManager::releaseBrake() {
    brakeApplied = false;
}

/********************************************************
* @brief    isBrakeApplied
* @details  This method checks if brake is applied.
* @param    None
* @return   bool    Return true if brake is applied
*                   Return false if brake is not applied
********************************************************/
bool SafetyManager::isBrakeApplied() const {
    return brakeApplied;
}

/********************************************************
* @brief    delay_ms
* @details  This function creates delay time by milliseconds.
* @param    milliseconds    Delay time by milliseconds
* @return   None
********************************************************/
void delay_ms(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}