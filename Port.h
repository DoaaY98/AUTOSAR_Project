 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H


/* Id for the company in the AUTOSAR
 * for example  ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)



#include "Common_Macros.h"
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

  /*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
  /*Det Code to report Invalid Port Pin ID requested              */ 
#define PORT_E_PARAM_PIN  (uint8)0x0A
   
  /*Det Code to report Port Pin not configured as changeable      */ 
#define PORT_E_DIRECTION_UNCHANGEABLE (uint8)0x0B
   
   /*Det Code to report API Port_Init service called with wrong parameter.*/
#define PORT_E_PARAM_CONFIG (uint8)0x0C
   
   /*Det Code to report API Port_SetPinMode service called when mode is unchangeable.*/
#define PORT_E_PARAM_INVALID_MODE (uint8)0x0D

#define PORT_E_MODE_UNCHANGEABLE (uint8)0x0E

   /*Det Code to report API service called without module initialization*/

#define PORT_E_UNINIT (uint8)0x0F
   
   /*Det Code to report APIs called with a Null Pointer*/
#define PORT_E_PARAM_POINTER (uint8)0x10   
   

   /******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
  /* Service ID for PORT INIT function*/
#define PORT_INIT_SID (uint8)0x00  
   
   /*Service ID for Port_SetPinDirection*/
#define PORT_SET_PIN_DIRECTION_SID (uint8)0x01
   
   /*Service ID for Port_RefreshPortDirection*/
#define PORT_REFRESH_PORT_DIRECTION_SID (uint8)0x02
  
   /*Service ID for Port_GetVersionInfo*/
#define PORT_GET_VERSION_INFO_SID (uint8)0x03

    /*Service ID for Port_SetPinMode*/
#define PORT_SET_PIN_MODE_SID (uint8)0x04

    
   
   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* typedef for port pintype chosen*/
typedef uint8 Port_PinType;

/* typedef for port mode type chosen */
typedef uint8 Port_PinModeType;
/*typedef for port mode type*/
typedef uint8 Port_PortType;

/*typedef for initial value of the port*/
typedef enum {
INITIAL_LOW,INITIAL_HIGH
}Port_InitialValue;
/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
        5. initial value of the pin (high or low) 
        6. is the port pin direction changeable? (std_on or std_off)
        7. is the port pin mode changeable? (std_on or std_off)
        8. the mode of the configured pin 
*/
typedef struct 
{
    //Port_PortType port_num; /**/
    Port_PinType pin_num; /*Pin Id of the port pin. This value will be assigned to the symbolic name derived from the port pin container short name.*/
    Port_PinDirectionType direction; /**/
    Port_InternalResistor resistor;  /**/
    Port_InitialValue initial_value; /*Port Pin Level value from Port pin list.*/
    uint8 Port_PinDirectionChangeable; /*Parameter to indicate if the direction is changeable on a port pin during runtime. true: Port Pin direction changeable enabled. false: Port Pin direction changeable disabled.*/
    uint8 Port_PinModeChangeable;  /*Parameter to indicate if the mode is changeable on a port pin during runtime.*/
    Port_PinModeType Mode; /*Port pin mode from mode list.*/
    uint8 DigOrAna; /*Port Pin is Analog or Digital*/
    
}Port_ConfigPin;

typedef struct{
  Port_ConfigPin Pins[PORT_CONFIGURED_CHANNELS];
}Port_ConfigType;

//PIN_17,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_Changeable,Mode_Changeable,PORT_PIN_MODE_DIO



/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_SetupGpioPin
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
//void Port_SetupGpioPin(const Port_ConfigType *ConfigPtr );

/*Function that Initializes the Port Driver module. */

void Port_Init( const Port_ConfigType* ConfigPtr );

/*Function that Sets the port pin direction*/
#if (PORT_SET_PIN_DIRECTION_API==STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif
/*Function that Refreshes port direction.*/
void Port_RefreshPortDirection( void );

/*Function that Returns the version information of this module.*/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif

/*Function that Sets the port pin mode.*/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

/******************************************************************************
**************************PORT PINS Definitions********************************
******************************************************************************/

#define PIN_17        (uint8)0      //PA0 
#define PIN_18        (uint8)1    //PA1 
#define PIN_19        (uint8)2   //PA2 
#define PIN_20        (uint8)3    //PA3 
#define PIN_21        (uint8)4   //PA4 
#define PIN_22        (uint8)5             //PA5 
#define PIN_23        (uint8)6             //PA6 
#define PIN_24        (uint8)7             //PA7 


#define PIN_45        (uint8)8             //PB0 
#define PIN_46        (uint8)9             //PB1 
#define PIN_47        (uint8)10             //PB2 
#define PIN_48        (uint8)11            //PB3 
#define PIN_58        (uint8)12            //PB4 
#define PIN_57        (uint8)13           //PB5 
#define PIN_1         (uint8)14          //PB6 
#define PIN_4         (uint8)15         //PB7 


#define PIN_52        (uint8)16          //PC0 
#define PIN_51        (uint8)17         //PC1 
#define PIN_50        (uint8)18          //PC2 
#define PIN_49        (uint8)19         //PC3 
#define PIN_16        (uint8)20          //PC4 
#define PIN_15        (uint8)21          //PC5 
#define PIN_14        (uint8)22          //PC6 
#define PIN_13        (uint8)23          //PC7 


#define PIN_61        (uint8)24          //PD0 
#define PIN_62        (uint8)25         //PD1 
#define PIN_63        (uint8)26          //PD2 
#define PIN_64        (uint8)27          //PD3 
#define PIN_43        (uint8)28          //PD4 
#define PIN_44        (uint8)29          //PD5 
#define PIN_53        (uint8)30          //PD6 
#define PIN_10        (uint8)31          //PD7 

#define PIN_9         (uint8)32          //PE0 
#define PIN_8         (uint8)33          //PE1 
#define PIN_7         (uint8)34          //PE2 
#define PIN_6         (uint8)35          //PE3 
#define PIN_59        (uint8)36          //PE4 
#define PIN_60        (uint8)37         //PE5 

#define PIN_28        (uint8)38          //PF0 
#define PIN_29        (uint8)39          //PF1 
#define PIN_30        (uint8)40          //PF2 
#define PIN_31        (uint8)41         //PF3 
#define PIN_5         (uint8)42         //PF4 

#define A_SHIFT (uint8)0
#define B_SHIFT (uint8)8
#define C_SHIFT (uint8)16
#define D_SHIFT (uint8)24
#define E_SHIFT (uint8)32
#define F_SHIFT (uint8)38





#endif /* PORT_H */
