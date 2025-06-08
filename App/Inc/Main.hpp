/********************************************************
* @file     Main.hpp
* @brief    Declare all files and functions for the main program
* @details  This file contains necessary component for the
*           main program, include DashboardController, 
*           DisplayManager, BatteryManager, DriveModeManager,
*           SpeedCalculator, SafetyManager and functions that 
*           create thread for multithreading. 
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include "DashboardController.hpp"
#include "DisplayManager.hpp"
#include "BatteryManager.hpp"
#include "DriveModeManager.hpp"
#include "SpeedCalculator.hpp"
#include "SafetyManager.hpp"
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <future>
#include <unordered_map>
#include <windows.h>

/********************************************************
* @brief  readCSV
* @param  dashboardController Pointer to DashboardController 
*                             object that receive updated data
* @return None 
********************************************************/
void readCSV(DashboardController* dashboardController);

/********************************************************
* @brief  keyboardInputHandler
* @param  dashboardController Pointer to DashboardController object
* @param  speedCalculator     Pointer to SpeedCalculator object    
* @param  driveMode           Pointer to DriveModeManager object
* @param  safetyManager       Pointer to SafetyManager object    
* @param  batteryManager      Pointer to BatteryManager object
* @return None
********************************************************/
void keyboardInputHandler(DashboardController* dashboardController, SpeedCalculator* speedCalculator,
    DriveModeManager* driveMode, SafetyManager* safetyManager, BatteryManager* batteryManager);

/********************************************************
* @brief  display 
* @param  dashboardController Pointer to DashboardController 
*                             object to display updated data
* @return None
********************************************************/
void display(DashboardController* dashboardController);

/********************************************************
* @brief  saveToCSV
* @param  dashboardController Pointer to DashboardController 
*                             object to read and save data
* @return None
********************************************************/
void saveToCSV(DashboardController* dashboardController);

#endif  /* MAIN_HPP */
