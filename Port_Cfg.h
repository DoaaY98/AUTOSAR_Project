/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Doaa Yehia
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

   /* Pre-compile option for pin direction API */
#define PORT_SET_PIN_DIRECTION_API            (STD_ON)

   /* Pre-compile option for pin mode API */
#define   PORT_SET_PIN_MODE_API                (STD_ON)
   
/* Number of the configured PORT Channels */
   
#define PORT_CONFIGURED_CHANNELS              (43U)
   
        /* Modes of Port Pins*/
#define PORT_PIN_MODE_ADC       (uint8)1
#define PORT_PIN_MODE_CAN       (uint8)8
#define PORT_PIN_MODE_DIO       (uint8)0
#define PORT_PIN_MODE_DIO_GPT   (uint8)2
#define PORT_PIN_MODE_DIO_WDG   (uint8)3
#define PORT_PIN_MODE_FLEXRAY   (uint8)4
#define PORT_PIN_MODE_ICU       (uint8)5
#define PORT_PIN_MODE_LIN       (uint8)6
#define PORT_PIN_MODE_MEM       (uint8)7
#define PORT_PIN_MODE_PWM       (uint8)9
#define PORT_PIN_MODE_SPI       (uint8)10

#define PORT_MODE_CHECK (uint8)11   
   /*Mode and Direction Changeable by default*/
#define Dir_Changeable      (STD_ON)   
#define Dir_NotChangeable    (STD_OFF)   
#define Mode_Changeable     (STD_ON)   
#define Mode_NotChangeable   (STD_OFF)  
   
 /*Analog or Digital Definitions*/ 
#define ANALOG    (STD_OFF)  

#define DIGITAL   (STD_ON) 
   

/*Port used Channels in LED and Switch*/
   
#define PortConf_LED1_PIN_NUM     PIN_29
   
#define PortConf_SW1_PIN_NUM      PIN_5
   
#endif /* PORT_CFG_H */
