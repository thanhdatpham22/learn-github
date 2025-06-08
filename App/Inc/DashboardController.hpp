/********************************************************
* @file     DashboardController.hpp
* @brief    Declare methods and classes related to dashboard 
*           controller
* @details  This file contains classes and methods declaration
*           related to dashboard controller, stores system 
*           parameters, use observe pattern to update data
*           to other classes.
* @version  1.0
* @date     2024-11-10
* @author   Tran Quang Khai
********************************************************/
#ifndef DASHBOARD_CONTROLLER_HPP
#define DASHBOARD_CONTROLLER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

/********************************************************
* The database path to CSV file that stores system information
********************************************************/
#define DATABASE_PATH   ".\\Data\\Database.csv"

/********************************************************
* @enum  DriveMode
* @brief This enum contains 2 drive mode (ECO and SPORT)
********************************************************/
typedef enum {
    SPORT,      /* Sport Mode */
    ECO         /* Eco Mode */
} DriveMode;

/********************************************************
* @class Observer
* @brief Interface for observes
********************************************************/
class Observer {
public:
    /********************************************************
    * @brief Virtual function use for objects 
    ********************************************************/
    virtual void update() = 0;
};

/********************************************************
* @class DashboardController
* @brief Class includes system parameters, is the subject
*        that keep the list of registered observers
********************************************************/
class DashboardController {
private:
    int speed;              /* Current speed (km/h) */
    DriveMode driveMode;    /* Drive mode (ECO or SPORT) */
    int batteryLevel;       /* Battery level (0 - 100 %) */
    double remainingRange;  /* Ramaining range (km) */
    int acTemp;             /* Air Conditioner temperature (16 - 30 °C) */
    int windLevel;          /* Wind level (1 - 5) */

    /* List of observers */ 
    vector<Observer*> observers;

public:
    /********************************************************
    * @brief Constructor 
    ********************************************************/
    DashboardController();

    /********************************************************
    * @brief Destructor 
    ********************************************************/
    ~DashboardController();

    /********************************************************
    * @brief  Get current speed
    * @param  None
    * @return int     Return current speed
    ********************************************************/
    int getSpeed() const;

    /********************************************************
    * @brief  Get current drive mode
    * @param  None
    * @return DriveMode     Return current drive mode
    ********************************************************/
    DriveMode getDriveMode() const;

    /********************************************************
    * @brief  Get current battery level
    * @param  None
    * @return int     Return current battery level
    ********************************************************/
    int getBatteryLevel() const;

    /********************************************************
    * @brief  Get current remaining range
    * @param  None
    * @return double  Return current remaining range
    ********************************************************/
    double getRemainingRange() const;

    /********************************************************
    * @brief  Get current AC temperature
    * @param  None
    * @return int     Return current AC temperature
    ********************************************************/
    int getAcTemp() const;

    /********************************************************
    * @brief  Get current wind level
    * @param  None
    * @return int     Return current wind level
    ********************************************************/
    int getWindLevel() const;
    
    /********************************************************
    * @brief  Set speed
    * @param  newSpeed    Value to set new speed  
    * @return None
    ********************************************************/
    void setSpeed(int newSpeed);

    /********************************************************
    * @brief  Set drive mode
    * @param  newDriveMode    Mode to set new drive mode  
    * @return None
    ********************************************************/
    void setDriveMode(DriveMode newDriveMode);

    /********************************************************
    * @brief  Set battery level
    * @param  newLevel    Value to set new battery level  
    * @return None
    ********************************************************/
    void setBatteryLevel(int newLevel);

    /********************************************************
    * @brief  Set remaining range
    * @param  newRemainingRange   Value to set remaining range  
    * @return None
    ********************************************************/
    void setRemainingRange(double newRemainingRange);

    /********************************************************
    * @brief  Set new AC temperature
    * @param  newTemp    Value to set new AC temperature  
    * @return None
    ********************************************************/
    void setAcTemp(int newTemp);

    /********************************************************
    * @brief  Set new wind level
    * @param  newLevel    Value to set new new wind level  
    * @return None
    ********************************************************/
    void setWindLevel(int newLevel);

    /********************************************************
    * @brief  updateData
    * @param  None  
    * @return None
    ********************************************************/
    void updateData();

    /********************************************************
    * @brief  Register observer to the list of observes
    * @param  observer  Pointer to object to register observer  
    * @return None
    ********************************************************/
    void registerObserver(Observer* observer); 

    /********************************************************
    * @brief  Remove observer from the list of observes
    * @param  observer  Pointer to object to remove observer  
    * @return None
    ********************************************************/   
    void removeObserver(Observer* observer);

    /********************************************************
    * @brief  Notify to all observes in the list about new 
    *         updated data
    * @param  None  
    * @return None
    ********************************************************/
    void notifyObservers() const;
};

#endif  /* DASHBOARD_CONTROLLER_HPP */