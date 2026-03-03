/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END

#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include "system_config.h"
#include "system_definitions.h"
#include "Apex_Lcd_Typedef.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 

#define KEEP              __attribute__ ((keep)) __attribute__((address(DRV_NVM_MEDIA_START_ADDRESS)))
/* The size of the media used for this demo. */
#define APP_NVM_MEMORY_AREA_SIZE (DRV_NVM_MEDIA_SIZE * 1024)
    
#define TS_CALIBRATED     0x01
    
// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

/* Enumeration of the Read, write and erase region geometry indices */
typedef enum {

    /* Read region index */
    APP_NVM_READ_REGION_INDEX = 0,

    /* Write region index */
    APP_NVM_WRITE_REGION_INDEX,
    
    /* Erase region index */
    APP_NVM_ERASE_REGION_INDEX

} APP_NVM_REGION_INDEX;

/* Enumeration listing the read operation sub-states */
typedef enum {
            
    /* Issue Read command */
    APP_STATE_RD_CMD = 0,

    /* Check if the Read command operation is complete */
    APP_STATE_RD_CMD_STATUS,
            
    /* Use the read data to calibrate touch screen */
    APP_STATE_RD_CALIBRATE,

    /* Read and Calibration operation completed */
    APP_STATE_RD_CMPLT

} APP_READ_STATES;

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE_INIT=0,
    APP_STATE_TOUCH_CALIB,        
	APP_STATE_SERVICE_TASKS,
    APP_STATE_TASKS,

	/* TODO: Define states used by the application state machine. */

} APP_STATES;

#define Header_Color                0x2E385E

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;

    /* TODO: Define any additional data used by the application. */
    DRV_HANDLE  tmrHandle;
    /* NVM Driver Handle */
    DRV_HANDLE                  nvmHandle;
    /* NVM Command Handles */
    DRV_NVM_COMMAND_HANDLE      nvmCommandHandle;
    /* Read operation's current state */
    APP_READ_STATES             readState;
    
    /* Counter to track the number of successful command 
    complete events */
    uint8_t                     eventCount;

    /* Counter to track the number of unsuccessful command 
    complete events */
    uint8_t                     errorEventCount;
    
    bool tmrIntTriggered;

} APP_DATA;


/* Generic Macros */
#define SPI_RETRY_COUNT                         3

#if OVERRIDE_FW_VERSION == 1
#warning FW Version Override in Use
#define DISPLAY_FW_VERSION	                    FW_VERSION_OVERRIDE
#else
#if _BID_PRODUCTION_TEST_BUILD_ == 1
#define DISPLAY_FW_VERSION                      (0x04820000 | GIT_REVISION)
#elif LOGO_DEKA == 1
#define DISPLAY_FW_VERSION                      (0x05020000 | GIT_REVISION)
#else
#define DISPLAY_FW_VERSION                      (0x04020000 | GIT_REVISION)
#endif
#endif

#define FW_VERSION_ADDR                         0x9D1FBFF0

/* Macro to Convert Temperature Formats (?C/?F) */
#define CELSIUS(X)                              (t_FL_32)(((X - 32) * 5) / 9)
#define FAHRENHEIT(X)                           (((t_FL_32)((X * 9) / 5)) + 32)

/* Macro to Convert Time Parameters */
#define MIN_IN_HRS                              60
#define SEC_IN_MINS                             60
#define SEC_IN_HRS                              (60 * SEC_IN_MINS)

#define TIME_HRS(X)                             (X / SEC_IN_HRS)
#define TIME_MINS(X)                            ((X % SEC_IN_HRS) / SEC_IN_MINS)
#define TIME_SECS(X)                            ((X % SEC_IN_HRS) % SEC_IN_MINS)

#define MIN_MONTH                               1
#define MAX_MONTH                               12

#define MIN_DATE                                1
#define MAX_DATE                                31

#define MAX_VALID_YR                            2100
#define MIN_VALID_YR                            1970

#define MAX_EVENT_LOG_SIZE                      25
#define HOME_BACK_BTN_XSIZE                     100
#define MAX_GENERIC_MSG_SIZE                    12

#if ENABLE_96V == 1
#define MAX_BATTERY_VOLT_COUNT                  6
#else
#define MAX_BATTERY_VOLT_COUNT                  5
#endif

/* Macro for Lithium Battery Related Operations */
#define C4_DSG                                  (DSG == ChargeCurveType)
#define C9_LIFEPO                               (LIFEPO == ChargeCurveType)
#define C9_NOT_LIFEPO                           (LIFEPO != ChargeCurveType)
#define C10_LI_BMS                              (LIBMS == ChargeCurveType)
#define C10_NOT_LI_BMS                          (LIBMS != ChargeCurveType)
#define LI_NOT_BOTH                             (C9_NOT_LIFEPO && C10_NOT_LI_BMS)
#define C12_GEL_80                              (GEL80 == ChargeCurveType)
#define C12_NOT_GEL_80                          (GEL80 != ChargeCurveType)
#define C13_GEL_100                             (GEL100 == ChargeCurveType)
#define C13_NOT_GEL_100                         (GEL100 != ChargeCurveType)


/* Macros for Power Module Related Operations */
#define MODULE_COUNT                            8
#define MOD_FLAG_SIZE                           (MODULE_COUNT * sizeof(t_UI_16))
#define MOD_FLAG_COMPARE(X, Y)                  (memcmp(X, Y, MOD_FLAG_SIZE))

/* Macro for Warning Flags */
#define WARN_CHARGER_OVER_TEMP_WARNING       0x00000001
#define WARN_MODULE_WARNING                  0x00000002
#define WARN_CHARGER_OUTPUT_LIMITED          0x00000004
#define WARN_LOW_BATTERY_REJECT              0x00000008
#define WARN_SETUP_ERROR                     0x00000010
#define WARN_BID_COMM_FAILED                 0x00000020
#define WARN_ARCLESS_SUBSYSTEM_FAULT         0x00000040
#define WARN_CABLE_WARN                      0x00000080
#define WARN_STORAGE                         0x00000100
#define WARN_END                             0x00000200

/* Macro for Information Flags */
#define INFO_START_MODE_INHIBIT_TODS         0x00000001
#define INFO_START_MODE_INHIBIT_DELAY        0x00000002
#define INFO_START_MODE_INHIBIT_TODB         0x00000004
#define INFO_START_MODE_INHIBIT_TIMER        0x00000008
#define INFO_BATTERY_CYCLE_DELAY             0x00000010
#define INFO_NO_GASSING_INHIBIT_TIME         0x00000020
#define INFO_NO_GASSING_INHIBIT_BLOCK        0x00000040
#define INFO_REFRESH_NOTIFICATION            0x00000080
#define INFO_EQUALIZE_NOTIFICATION           0x00000100
#define INFO_BATTERY_WATERING_NOTIFY         0x00000200
#define INFO_MANUAL_STOP                     0x00000400
#define INFO_BID_COMM_ACTIVE_DETECT          0x00000800
#define INFO_BID_COMM_ACTIVE_SYNC            0x00001000
#define INFO_BID_COMM_ACTIVE_REFRESH         0x00002000
#define INFO_BID_COMM_ACTIVE_WRITE           0x00004000
#define INFO_CHARGE_COMPLETE                 0x00008000
#define INFO_POWER_DELAY                     0x00010000
#define INFO_POWER_FAIL_RECOVER              0x00020000
#define INFO_FW_FILE_COPY                    0x00040000
#define INFO_DETECT_MODULE                   0x00080000
#define INFO_PERSONALITY_FILE_CHECK			 0x00100000
#define INFO_PERSONALITY_CHECK_PASS			 0x00200000
#define INFO_PERSONALITY_CHECK_FAIL			 0x00400000
#define INFO_PERSONALITY_CHECK_VER			 0x00800000
#define INFO_PERSONALITY_CHECK_CSN			 0x01000000
#define INFO_USB_UPDATE_NOT_PERFORMED        0x02000000
#define INFO_WAITING_FOR_BMS                 0x04000000
#define INFO_WAITING_FOR_BATTERY_READY       0x08000000
#define INFO_WAITING_FOR_CABLE_CONNECTIONS   0x10000000
#define INFO_SENTRY_CC_80                    0x20000000
#define INFO_SENTRY_CC_TRICKLE               0x40000000
#define INFO_SENTRY_CC_EQUALIZE              0x80000000
#define INFO_SENTRY_CC_100					 0x00000002

//NOTE: Update as additional info messages are added
#define INFO_2_EOL                           0x00000002

/* Macro for Module Warning Flags */
#define MOD_WARN_01_IGBT_TEMP_WARN              0x0001
#define MOD_WARN_02_IGBT_TEMP_SHUT_DOWN         0x0002
#define MOD_WARN_03_PHASE_LOSS                  0x0004
#define MOD_WARN_04_BRIDGE_OVER_CURRENT         0x0008
#define MOD_WARN_05_MODULE_OFFLINE              0x0010
#define MOD_WARN_06_THERMISTOR_ERROR			0x0020
#define MOD_WARN_07_DIODE_TEMP_WARN             0x0040
#define MOD_WARN_08_LOST_CURRENT_CONTROL		0x0080
#define MOD_WARN_09_XFRMR_TEMP_WARN             0x0100
#define MOD_WARN_10_POWER_STABILITY             0x0200
#define MOD_WARN_END                         	0x0400

#define ERR_STR_HIGH_BATT_VOLTAGE		"High Battery Reject\nUnable to Charge"
#define ERROR_STR_BATT_OVER_TEMP		"Battery Over Temperature Detected\nCooling Down"
#define ERROR_STR_SLOPE                 "Charge Curve Error\nMinimum charge Slope not Met"
#define ERROR_STR_CV                    "Charge Curve Error\nUnable to Reach Target CV"
#define ERROR_STR_LOW_CURRENT 			"Charge Curve Error\nLow Current"
#define ERROR_STR_OVER_CURRENT			"Charge Curve Error\nOver Current"
#define ERROR_STR_SESSION_TIMEOUT		"Charge Session Timeout"
#define ERROR_STR_OVER_AH               "Charge Error\nOver AH Returned"
#define ERROR_STR_OVER_TEMP 			"Charger Over Temperature Error\n"
#define ERROR_STR_DIDT                  "Charge Curve Error\nDI/DT"
#define ERROR_STR_ENGINE_ERROR			"Charge Engine Error"
#define ERROR_STR_MODULE1_TEMP 			"Power Module 1\nTransformer Temperature Error"
#define ERROR_STR_MODULE2_TEMP 			"Power Module 2\nTransformer Temperature Error"
#define ERROR_STR_MODULE3_TEMP 			"Power Module 3\nTransformer Temperature Error"
#define ERROR_STR_MODULE4_TEMP 			"Power Module 4\nTransformer Temperature Error"
#define ERROR_STR_MODULE5_TEMP 			"Power Module 5\nTransformer Temperature Error"
#define ERROR_STR_MODULE6_TEMP 			"Power Module 6\nTransformer Temperature Error"
#define ERROR_STR_MODULE7_TEMP 			"Power Module 7\nTransformer Temperature Error"
#define ERROR_STR_BID_BATTERY_REJECT	"BID Battery Reject"
#define ERROR_STR_ARCLESS_ERROR			"Arcless Subsystem Error"
#define ERROR_STR_MODULE8_TEMP 			"Power Module 8\nTransformer Temperature Error"
#define ERROR_STR_MODULE1_HW_MISMATCH 	"Power Module 1\nHardware Mismatch Detected"
#define ERROR_STR_MODULE2_HW_MISMATCH 	"Power Module 2\nHardware Mismatch Detected"
#define ERROR_STR_MODULE3_HW_MISMATCH 	"Power Module 3\nHardware Mismatch Detected"
#define ERROR_STR_MODULE4_HW_MISMATCH 	"Power Module 4\nHardware Mismatch Detected"
#define ERROR_STR_MODULE5_HW_MISMATCH 	"Power Module 5\nHardware Mismatch Detected"
#define ERROR_STR_MODULE6_HW_MISMATCH	"Power Module 6\nHardware Mismatch Detected"
#define ERROR_STR_MODULE7_HW_MISMATCH	"Power Module 7\nHardware Mismatch Detected"
#define ERROR_STR_MODULE8_HW_MISMATCH	"Power Module 8\nHardware Mismatch Detected"
#define ERROR_STR_PERSONALITY			"Invalid System Configuration\nPlease Call Prestolite Power Service\n1-800-367-2002 for Assistance"
#define ERROR_STR_BATTERY_COMMS			"Battery Communication Failed"
#define ERROR_STR_BATTERY_FAULT			"Battery Fault"
#define ERROR_STR_BATTERY_SERVICE		"Charging Not Allowed\nBattery Service Required"
#define ERROR_STR_HOT_DISCONNECT        "Hot Disconnect"
#define ERROR_STR_ARCLESS_DISCONNECT    "Arcless Disconnect"
#define ERROR_STR_CLIFF_TIMER           "80%->Finish Timer Expired"

#define WARN_STR_CHARGER_TEMP		"Charger Temperature Warning"
#define WARN_STR_POWER_MODULE		"Power Module"
#define WARN_STR_OUTPUT_LIMITED 		"Available Power Less Than\nRequired by Charge Curve"
#define WARN_STR_VERY_LOW_BATT		"Very Low Battery Voltage Detected"
#define WARN_STR_SYSTEM_MISMATCH	"System Settings Mismatch Detected\nPlease Contact Prestolite Power Technical\nSupport"
#define WARN_STR_BID_COMM_ERROR		"BID Communication Error\nConnection Lost"
#define WARN_STR_ARCLESS_WARN		"Arcless Subsystem \nIssue Detected"
#define WARN_STR_CHECK_CABLE		"Check Cable Connections"
#define WARN_STR_STORAGE            "Data Storage Warning\nArchive and FW Updates Disabled"
#define WARN_STR_GENERAL_WARNING	"General Warning"

#define WARN_MOD_STR_IGBT_TEMP_WARN		"\nIGBT Temperature Warning"
#define WARN_MOD_STR_IGBT_TEMP_ERROR		"\nIGBT Temperature Shutdown Warning"
#define WARN_MOD_STR_PHASE_LOSS			"\nPhase Loss Warning"
#define WARN_MOD_STR_BRIDGE_OVERCURRENT		"\nBridge Overcurrent"
#define WARN_MOD_STR_MODULE_OFFLINE		"\nOffline"
#define WARN_MOD_STR_TEMP_SENSOR		"\nTemperature Sensor Warning"
#define WARN_MOD_STR_DIODE_OVER_TEMP		"\nDiode Temperature Warning"
#define WARN_MOD_STR_LOST_CURRENT_CONTROL	"\nLost Current Control"
#define WARN_MOD_STR_TRANSFORMER_TEMP		"\nTransformer Temperature Warning"
#define WARN_MOD_STR_POWER_STABILITY		"\nPower Stability Warning"
#define WARN_MOD_STR_POWER_LIMIT            "\nPower Limit"
#define WARN_MOD_STR_SHORT_CIRCUIT          "\nShort Circuit Detected"

const char *ErrorMsg[] = 
{
	ERR_STR_HIGH_BATT_VOLTAGE,      /* Error 01 */
	ERROR_STR_BATT_OVER_TEMP,       /* Error 02 */
	ERROR_STR_SLOPE,                /* Error 03 */
	ERROR_STR_CV,                   /* Error 04 */
	ERROR_STR_LOW_CURRENT,          /* Error 05 */
	ERROR_STR_OVER_CURRENT,         /* Error 06 */
	ERROR_STR_SESSION_TIMEOUT,      /* Error 07 */
	ERROR_STR_OVER_AH,              /* Error 08 */
	ERROR_STR_OVER_TEMP,            /* Error 09 */
	ERROR_STR_DIDT,                 /* Error 10 */
	ERROR_STR_ENGINE_ERROR,         /* Error 11 */
	ERROR_STR_MODULE1_TEMP,         /* Error 12 */
	ERROR_STR_MODULE2_TEMP,         /* Error 13 */
	ERROR_STR_MODULE3_TEMP,         /* Error 14 */
	ERROR_STR_MODULE4_TEMP,         /* Error 15 */
	ERROR_STR_MODULE5_TEMP,         /* Error 16 */
	ERROR_STR_MODULE6_TEMP,         /* Error 17 */
	ERROR_STR_MODULE7_TEMP,         /* Error 18 */
	ERROR_STR_BID_BATTERY_REJECT,	/* Error 19 */
	ERROR_STR_ARCLESS_ERROR,        /* Error 20 */
	ERROR_STR_MODULE8_TEMP,         /* Error 21 */
	ERROR_STR_MODULE1_HW_MISMATCH,	/* Error 22 */
	ERROR_STR_MODULE2_HW_MISMATCH,	/* Error 23 */
	ERROR_STR_MODULE3_HW_MISMATCH,	/* Error 24 */
	ERROR_STR_MODULE4_HW_MISMATCH,	/* Error 25 */
	ERROR_STR_MODULE5_HW_MISMATCH,	/* Error 26 */
	ERROR_STR_MODULE6_HW_MISMATCH,	/* Error 27 */
	ERROR_STR_MODULE7_HW_MISMATCH,	/* Error 28 */
	ERROR_STR_MODULE8_HW_MISMATCH,	/* Error 29 */
	ERROR_STR_PERSONALITY,          /* Error 30 */
	ERROR_STR_BATTERY_COMMS,        /* Error 31 */
	ERROR_STR_BATTERY_FAULT,        /* Error 32 */
	ERROR_STR_BATTERY_SERVICE,      /* Error 33 */
    ERROR_STR_CLIFF_TIMER           /* Error 34 */
};

const char *WarningMsg[] = 
{
	WARN_STR_CHARGER_TEMP,		/* Warn 01 */
	WARN_STR_POWER_MODULE,		/* Warn 02 */
	WARN_STR_OUTPUT_LIMITED,		/* Warn 03 */
	WARN_STR_VERY_LOW_BATT,		/* Warn 04 */
	WARN_STR_SYSTEM_MISMATCH,	/* Warn 05 */
	WARN_STR_BID_COMM_ERROR,	/* Warn 06 */
	WARN_STR_ARCLESS_WARN,		/* Warn 07 */
	WARN_STR_CHECK_CABLE,		/* Warn 08 */
    WARN_STR_STORAGE,           /* Warn 09 */
	WARN_STR_GENERAL_WARNING,	/* Warn 10 */
};

const char *ModuleMsg[] = 
{
	WARN_MOD_STR_IGBT_TEMP_WARN,		/* ModW 01 */
	WARN_MOD_STR_IGBT_TEMP_ERROR,		/* ModW 02 */
	WARN_MOD_STR_PHASE_LOSS,		/* ModW 03 */
	WARN_MOD_STR_BRIDGE_OVERCURRENT,	/* ModW 04 */
	WARN_MOD_STR_MODULE_OFFLINE,		/* ModW 05 */
	WARN_MOD_STR_TEMP_SENSOR,		/* ModW 06 */
	WARN_MOD_STR_DIODE_OVER_TEMP,		/* ModW 07 */
	WARN_MOD_STR_LOST_CURRENT_CONTROL,	/* ModW 08 */
	WARN_MOD_STR_TRANSFORMER_TEMP,		/* ModW 09 */
	WARN_MOD_STR_POWER_STABILITY,		/* ModW 10 */
};

const char *InfoMsg[] =
{
    "Charge will start at: ",                               /* Info 01 */
    "Charge will start at: ",                               /* Info 02 */
    "Charge will resume at: ",                              /* Info 03 */
    "Charge will stop at: ",                                /* Info 04 */
    "Multi-Cell Cycle Delay \nActive",                      /* Info 05 */
    "No Gassing Delay ",                                    /* Info 06 */
    "No Gassing Delay Until ",                              /* Info 07 */
    "Battery Refresh Imminent",                             /* Info 08 */
    "Equalize in Progress",                                 /* Info 09 */
    "Battery Watering in Progress",                         /* Info 10 */
    "Manual Stop",                                          /* Info 11 */
    "Detecting BID Device",                                 /* Info 12 */
    "Syncing BID Device Data",                              /* Info 13 */
    "Refreshing BID Device Data",                           /* Info 14 */
    "Writing BID Device Data",                              /* Info 15 */
    "Charge Complete",                                      /* Info 16 */
    "Delayed Start Due to Power Failure",                   /* Info 17 */
    "Power Failure Detected\nUnit will Restart Shortly",    /* Info 18 */
    "Charging Disabled\nFW Update in Progress",             /* Info 19 */
    "Detecting Module...",                                  /* Info 20 */
    "Personality Update File\nValidation in Progress",      /* Info 21 */
    "Personality Update Successful\nPlease Remove USB Stick\nSystem Reboot Initiated...",   /* Info 22 */
    "Personality Update Failed\nPlease Remove USB Stick",                                   /* Info 23 */
    "Personality Update Failed\nInvalid Version\nPlease Remove USB Stick",                  /* Info 24 */
    "Personality Update Failed\nCharger Incompatible\nPlease Remove USB Stick",             /* Info 25 */
    "USB Update Check Complete\nPlease Remove USB Stick",   /* Info 26 */
    "Waiting for BMS...",                                   /* Info 27 */
    "Waiting for Battery Ready...",                         /* Info 28 */
    "Waiting for Cable\\Arcless Connection",                /* Info 29 */
    "80% Charge Complete\nBattery Ready for Use",           /* Info 30 */
    "Trickle Charge Complete\nBattery Ready for Use",       /* Info 31 */
    "Equalize Complete\nBattery Ready for Use",             /* Info 32 */
    "Full ChargeComplete\nBattery Ready for Use",           /* Info 33 */
    "Waiting for Sentry Command",                           /* Info 34 */
};

#define NO_ACTIVITY_TIME_COUNTER	            2*60  	//~60 Sec (window update timer - 500ms)
#define NO_ACTIVITY_STATUS_COUNTER              2*30      //~30 Sec
//#warning NON_STANDARD_POWERSAVE_MODE_IN_USE
#define LCD_BACKLIGHT_TIMEOUT                   2*3*60  //~3 mins
//#define LCD_BACKLIGHT_TIMEOUT                   60  //~30 seconds

    #define Text_Color_for_Boot_up              0x2E385E

/* Macros for Logo Mapping */
#if LOGO_DEKA == 1
    #define LOGO_SPLASH                         _acImage_Deka_Logo
    #define LOGO_FOOTER                         _acImage_Footer_Deka_Logo
    #define LOGO_SPLASH_SIZE_X                  455
    #define LOGO_SPLASH_SIZE_Y                  169
    #define LOGO_SPLASH_POS_X                   172
    #define LOGO_SPLASH_POS_Y                   115
    #define LOGO_BOOT_VER_POS_X                 235
    #define LOGO_BG_COLOR                       0x00231F20
    #define LOGO_VER_TEXT_COLOR                 0xFFFFFF
    #define LOGO_FOOTER_X_OFFSET                -10
    #define LOGO_FOOTER_Y_OFFSET                -10
#else
    #define LOGO_SPLASH                         _acImage_AMETEK_Logo
    #define LOGO_FOOTER                         _acImage_Footer_Ametek_Logo
    #define LOGO_SPLASH_SIZE_X                  546
    #define LOGO_SPLASH_SIZE_Y                  127
    #define LOGO_SPLASH_POS_X                   127
    #define LOGO_SPLASH_POS_Y                   156
    #define LOGO_BOOT_VER_POS_X                 200
    #define LOGO_BG_COLOR                       0x00FFFFFF
    #define LOGO_VER_TEXT_COLOR                 Text_Color_for_Boot_up
    #define LOGO_FOOTER_X_OFFSET                0
    #define LOGO_FOOTER_Y_OFFSET                0
#endif


/* Enumeration type for Command Index */
typedef enum
{
	POWER_ON_VARIABLES_INDEX = 0,
	HEART_BEAT_INDEX,
	CHARGE_STATISTICS_INDEX,
	GENERAL_SETTINGS_INDEX,
	START_MODE_INDEX,
	CHARGE_CURVE_INDEX,
	BID_SETTINGS_INDEX,
	BMS_SETTINGS_INDEX,
	EQUALIZE_INDEX,
	REFRESH_INDEX,
	NO_GASSING_INDEX,
	RELAY_PROFILE_INDEX,
	CURVE_PARAM_INDEX,
    OVERRIDE_STATUS_INDEX,
    MODULE_FW_VERSION_INDEX,
    SET_DATE_TIME_INDEX,
    GET_ARCHIVE_LIST_INDEX,
    GET_ARCHIVE_REC_INDEX,
    GET_FACTORY_SETUP_INDEX,
    NOTIFY_COMMAND_INDEX,
    GET_CURRENT_ELOG_INDEX,
    GET_ARCHIVE_ELOG_INDEX,
	HOME_SCREEN_INDEX,
    ARCHIVE_INDEX,
    SETTINGS_INDEX,
	GENERAL_SETTINGS_2_INDEX,
    DATE_TIME_INDEX,
    TOUCH_CALIB_INDEX,
	CHARGE_STATISTICS_2_INDEX,
    CHARGE_STATISTICS_3_INDEX,
    CHARGE_STATISTICS_SENTRY_INDEX,
    LIFETIME_STATISTICS_INDEX,
    BOOT_SCREEN_INDEX,
    VERSION_SCREEN_INDEX,
    NETWORK_SETTINGS_INDEX,
    LISTVIEW_INDEX,
    MODULE_FIND_INDEX,
    BATTINTRFC_SETTINGS_INDEX
} CMD_INDEX_VAL;

/* Enumeration type for Battery/BID Connection Status */
typedef enum {
    BATTERY_NOT_CONNECTED   = 0X00,
    BATTERY_CONNECTED       = 0X01,
    BID_CONNECTED           = 0X02,
	BID_COMMUNICATION       = 0x03,
    BMS_CONNECTED           = 0X04,
	BMS_COMMUNICATION       = 0x05
} BATTERY_BID_STATUS_t;

/* Enumeration type for ZIGBEE Connectivity Status */
typedef enum {
    ZIGBEE_NOT_CONNECTED   = 0x00,
    ZIGBEE_CONNECTED       = 0x01,
    ZIGBEE_COMMUNICATION   = 0x02
} ZIGBEE_CONNECT_STATUS_t;

/* Enumeration type for USB Connectivity Status */
typedef enum {
    K64_USB_NOT_CONNECTED	= 0x00,
	K64_USB_CONNECTED		= 0x01,
	K64_USB_FILE_COPY		= 0x02
} K64_USB_CONNECT_STATUS_t;

/* Enumeration type for Delay Status */
typedef enum {
    DELAY_OFF               = 0x00,
    DELAY_ON                = 0x01,
    DELAY_ONOFF             = 0x02
} DELAY_STATUS_t;

/* Enumeration type for Charger Type */
typedef enum {
    CH_CONVENTIONAL         = 0X00,
    CH_FAST                 = 0X01,
    CH_PLUS                 = 0X02
} CHARGER_TYPE_t;

/* Enumeration type for VPC/AMP Status */
typedef enum {
    STATUS_BAD              = 0x00,
    STATUS_MARGINAL         = 0x01,
    STATUS_GOOD             = 0x02
} VPC_AMP_STATUS_t;

/* Enumeration type for Archive Record Type */
typedef enum {
    ALL_RECORDS_TYPE            = 0x00,
    CHARGE_COMPLETE_TYPE        = 0x01,
    EQUALIZE_TYPE               = 0x02,
	BATTERY_WATERING_TYPE       = 0x03,
    MANUAL_STOP_TYPE            = 0x04,
    HOT_DISCONNECT_TYPE         = 0x05,
    HAS_WARNINGS_TYPE           = 0x06,
    REFRESH_CYCLE_TYPE          = 0x07,
    NO_BATTERY_DEVICE_TYPE      = 0x08,
    WITH_BATTERY_DEVICE_TYPE    = 0x09
} ARCHIVE_REC_TYPE_t;

typedef enum
{
    PASSWORD_DISABLED   = 0,
    PASSWORD_ENABLED    = 1,
    PASSWORD_UNLOCKED   = 2
}PASSWORD_TYPE_t;

/* Enumeration type for Charge Curves */
typedef enum {
	FLD, CTM, YGR, SLR, DSG, SLE, DAG, CDR,
	MAX, LIFEPO, LIBMS, DESULF, GEL80, GEL100, 
    TRICKLE, CHARGE_CURVE_TOT
} t_CHARGE_CURVE;

/* Enumeration type for Charger Family */
typedef enum
{
    SHARED_CHARGER_FAMILY_UNKNOWN,
    SHARED_CHARGER_FAMILY_EVOLUTION,
    SHARED_CHARGER_FAMILY_ATLAS
}SHARED_CHARGER_FAMILY_t;

/* Enumeration type for BMS Mode */
typedef enum {
	BMS_DISABLED    = 0,
	BMS_OPTIONAL    = 1,
	BMS_REQUIRED    = 2
}BMS_MODE_t;

/* Enumeration type for BMS Battery Type */
typedef enum {
	BMS_BATTERY_MFR_NAVITAS 	= 0x0,
	BMS_BATTERY_MFR_GREENCUBE 	= 0x1
}BATTERY_BMS_MFR;

/* Structure for APEX LCD Date & Time */    
typedef struct __attribute__((packed))
{
    t_UI_8 m_Day;
    t_UI_8 m_Month;
    t_UI_16 m_Year;
    t_UI_8 m_Hour;
    t_UI_8 m_Minute;
    t_UI_8 m_Second;
    t_UI_8 m_Week_Day;
}date_time_t;

/* Structure for APEX LCD System Info */    
typedef struct __attribute__((packed))
{
    date_time_t m_Date_Time;
    t_UI_32 m_Info1_Flag;
    t_UI_32 m_Info2_Flag;
    t_UI_32 m_Warn_Flag;
    t_UI_32 m_Error1_Flag;
    t_UI_32 m_Error2_Flag;
    t_UI_16 m_Module_Warn[MODULE_COUNT];
    t_UI_8  m_Battery_Connect_Status :3;
    t_UI_8  m_Charging_In_Progress   :1;
    t_UI_8  m_Zigbee_Connect_Status  :2;
    t_UI_8  m_Add_GenericMsg         :1;
    t_UI_8  m_Equalize_Active        :1;
    t_UI_8  m_Delay_Icon             :2;
    t_UI_8  m_USB_Connect_Status	 :2;
    t_UI_8  m_VPC_Status             :2;
    t_UI_8  m_AMP_Status             :2;
    t_UI_8  m_GenericMsg[MAX_GENERIC_MSG_SIZE];
}system_info_t;

/* Structure for APEX LCD Screen Saver */
typedef struct __attribute__((packed))
{
    t_UI_32  m_NoActivityCnt;
    bool     m_IsEnabled;
    bool     m_IsLCDON;
    bool     m_IsLCDTouched;
}LCD_ScreenSaver_t;

/* Union for Bye - Bit Access */
typedef union
{
    t_UI_8 byte;
    struct
    {
        t_UI_8 bit0:1;
        t_UI_8 bit1:1;
        t_UI_8 bit2:1;
        t_UI_8 bit3:1;
        t_UI_8 bit4:1;
        t_UI_8 bit5:1;
        t_UI_8 bit6:1;
        t_UI_8 bit7:1;
    };
}BYTE;

/* Union for Double Word - Byte Access  */   
typedef union {
  t_UI_32 DWord;
  t_UI_16 Word[2];
  t_UI_8  Byte[4];
}DWORD;

extern bool PopUpAcked;
extern bool PopUpActive;
extern U8 ChargeCurveType;
extern bool Value_Changed;
extern bool gScreenChange;
extern bool gDisableSettings;
extern void (*cb_EditVal)(void);
extern bool Close_Button_Status;
extern system_info_t g_Rx_System_Info;

/* Global Array for Logos */
#if LOGO_DEKA == 1    
    extern const U8  _acImage_Deka_Logo[24336UL + 1];
    extern const U8 _acImage_Footer_Deka_Logo[19733UL + 1]; 
#else
    extern const U8 _acImage_AMETEK_Logo[20283];
    extern const U8 _acImage_Footer_Ametek_Logo[5056];
#endif

extern I32 Min_Value;
extern I32 Max_Value;
extern APP_DATA appData;
extern t_FL_32 Min_Float;
extern t_FL_32 Max_Float;
extern U8 ubyNoTouchCounter;
extern bool StatusPopUpActive;
extern PASSWORD_TYPE_t Password_Status;
extern LCD_ScreenSaver_t vstLCDScreenSaver;


extern const U8 _acImage_Header_Background[1630];
extern const U8 _acImage_Zigbee_status_Connected[2922UL + 1];
//extern const U8 _acImage_Zigbee_Not_Connected[2470UL + 1]; 
//extern const U8 _acImage_Zigbee_Net_Failure[3164UL + 1]; 
extern const U8 _acImage_No_BID_Icon_headder[1998UL + 1];
extern const U8 _acImage_BID_Icon_headder[2542UL + 1];
extern const U8 _acImage_BMS_Icon_header[2548UL + 1];
extern const U8 _acImage_Menu_Icon[2451UL + 1];
extern const U8 _acImage_Back_Arrow[1826UL + 1];
extern const U8 _acImage_Help_Unfilled[1327UL + 1];
extern const U8 _acImage_Help_Filled[1781UL + 1];
extern const U8 _acImage_Information_Icon[2777];
extern const U8 _acImage_Info_Filled[2491];
extern const U8 _acEQSOC[3647UL + 1];
extern const U8 _acImage_Unlockg_Symbol[1763];
extern const U8 _acImage_Lock_Symbol[1905];
extern const U8 _acImage_Delay_Clock_Icon[3155UL + 1];
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/
	
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the 
    application in its initial state and prepares it to run so that its 
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

extern void APP_Initialize (void);
extern WM_HWIN CreateBootWindow(void);
extern WM_HWIN CreateDashboardWindow(void);
extern WM_HWIN CreateBootFWWindow(void);
extern WM_HWIN CreateHomeJPEGWindow(void);
extern WM_HWIN CreateSettingsWindow(void);
extern WM_HWIN EqualizeMode(void);
extern WM_HWIN CreateBIDSettingsWindow(void);
extern WM_HWIN PopupListScreen(void);
extern void DeletePopupList(void);
extern WM_HWIN ArchiveScreen(void);
extern WM_HWIN ArchiveScreenResume(void);
extern WM_HWIN CalenderScreen(void);
extern WM_HWIN LifetimeStatistics(void);
extern WM_HWIN CreateStatistics1(void);
extern WM_HWIN CreateStatistics2(void);
extern WM_HWIN CreateStatistics3(void);
extern WM_HWIN CreateStatistics4(void);
extern WM_HWIN CreateStatisticsSentry(void);
extern WM_HWIN PopupScreen(void);
extern WM_HWIN PopupScreen1(void);
extern WM_HWIN PopupScreen2(void);
extern WM_HWIN GeneralSettings1(void);
extern WM_HWIN GeneralSettings2(void);
extern WM_HWIN FindModule(void);
extern WM_HWIN NetworkSettings(void);
extern WM_HWIN BIDSettings(void);
extern WM_HWIN BMSSettings(void);
extern WM_HWIN BID_BMS_Settings(void);
extern WM_HWIN ChargeCurveParameters(void);
extern WM_HWIN TimeDateSettings(void);
extern WM_HWIN TouchScreenCalibration(void);
extern WM_HWIN RelayProfile(void);
extern WM_HWIN GassingScreen(void);
extern WM_HWIN Refresh_Screen(void);
extern WM_HWIN Start_Mode(void);
extern WM_HWIN CreateListViewScreen(void);
extern WM_HWIN Keypad_Down(void);
extern WM_HWIN CalenderScreen1(void);
extern WM_HWIN CreateKeyPad_Numeric(WM_HWIN hParent);
extern void UpdateTime_Zone( void );
extern void UpdateGeneralSetting1( void );
//WM_HWIN GeneralSettings1ReadMode(void);
extern WM_HWIN Popup_Screen_1(void);
extern void CalibrateTouchScreen(void);

extern void AutoSwitchScreen(WM_HWIN);
extern void DisplayListView(void);
extern void UpdateBootScreen(void);
extern void DisplayFWVersion(void);
extern void SysStatusHandler(void);
extern void DisplayHomeScreen(void);
extern void GetSetStatistics1(void);
extern void GetSetStatistics2(void);
extern void GetSetStatistics3(void);
extern void GetSetStatistics4(void);
extern void ClearPopUpScreens(void);
extern void DisplayVersionInfo(void);
extern void GetSetLifeTimeStat(void);
extern void UpdateCCSystemInfo(void);
extern void UpdateEMSystemInfo(void);
extern void UpdateRelayProfileSysInfo(void);
extern void UpdateDashboardData(void);
extern void DisplaySystemStatus(void);
extern void UpdateHomeSystemInfo(void);
extern void UpdateArchive1SysInfo(void);
extern void UpdateArchive2SysInfo(void);
extern void UpdateArchive3SysInfo(void);
extern void UpdateArchive4SysInfo(void);
extern void UpdateModuleInfoSysInfo(void);
extern void UpdateArchiveSystemInfo(void);
extern void UpdateRefreshSystemInfo(void);
extern void UpdateFindModSystemInfo(void);
extern void UpdateSettingsSystemInfo(void);
extern void UpdateTimeDateSystemInfo(void);
extern void UpdateStartModeSystemInfo(void);
extern void UpdateNoGassingSystemInfo(void);
extern void UpdateGenSetting1SystemInfo(void);
extern void UpdateGenSetting2SystemInfo(void);
extern void UpdateBIDSettingsSystemInfo(void);
extern void UpdateBMSSettingsSystemInfo(void);
extern void UpdateLifeTimeArchiveSysInfo(void);
extern void LCDScreenSaverHandler(void);
extern void Time_AtoI(t_UI_8 Time[], t_UI_8 *Hrs, t_UI_8 *Mins);
extern void CompareDate(date_time_t *lStart_Date, date_time_t *lEnd_Date);

extern bool IsLeap(int); 
extern bool IsValidDate(date_time_t *); 
extern void DisableSettings(void);
/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

extern void APP_Tasks( void );

extern void SetCurrentScreenIndex(CMD_INDEX_VAL lScreenIndex);


#endif /* _APP_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

