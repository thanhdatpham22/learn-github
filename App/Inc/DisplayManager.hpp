/********************************************************
* @file     DisplayManager.hpp
* @brief    Declare methods and classes related to display 
*           management
* @details  This file contains class and methods declaration
*           related to display management, update data from
*           DashboardController and display data.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#ifndef DISPLAY_MANAGER_HPP
#define DISPLAY_MANAGER_HPP

#include <iostream>
#include "DashboardController.hpp"

using namespace std;

/********************************************************
* @class DisplayManager
* @brief Class includes methods display data, its object 
*        is the observer that must register to list of 
*        observers
********************************************************/
class DisplayManager : public Observer {
private:
    /********************************************************
    * @brief Pointer to DashboardController to get data
    ********************************************************/
    DashboardController* dashboardController;

public:
    /********************************************************
    * @brief Constructor 
    ********************************************************/
    DisplayManager(DashboardController* dashboardController);

    /********************************************************
    * @brief Destructor 
    ********************************************************/
    ~DisplayManager();

    /********************************************************
    * @brief  Display updated data 
    * @param  None
    * @return None
    ********************************************************/
    void updateDisplay();

    /********************************************************
    * @brief  Display speed 
    * @param  None
    * @return None
    ********************************************************/
    void showSpeed();     

    /********************************************************
    * @brief  Display drive mode 
    * @param  None
    * @return None
    ********************************************************/
    void showDriveMode();  

    /********************************************************
    * @brief  Display battery level 
    * @param  None
    * @return None
    ********************************************************/
    void showBatteryStatus();   

    /********************************************************
    * @brief  Display AC temperature 
    * @param  None
    * @return None
    ********************************************************/
    void showClimateStatus();  

    /********************************************************
    * @brief  Display wind level 
    * @param  None
    * @return None
    ********************************************************/
    void showWindLevel();     
    
    /********************************************************
    * @brief  Display remaining range 
    * @param  None
    * @return None
    ********************************************************/
    void showRemainingRange();  
    
    /********************************************************
    * @brief  Update data 
    * @param  None
    * @return None
    ********************************************************/
    void update();
};

#endif  /* DISPLAY_MANAGER_HPP */