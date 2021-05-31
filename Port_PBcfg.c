/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Doaa Yehia
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */

const Port_ConfigType Port_Configuration =/*3arafy hena el 50 alf pin elly mawgodeen :(*/
{
  /*PORT A PINS*/
PIN_17,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PA0
PIN_18,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PA1
PIN_19,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PA2
PIN_20,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL,//PA3
PIN_21,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PA4
PIN_22,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PA5
PIN_23,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PA6
PIN_24,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PA7

/*PORT B PINS*/
PIN_45,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PB0
PIN_46,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PB1
PIN_47,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PB2
PIN_48,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PB3
PIN_58,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PB4
PIN_57,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PB5
PIN_1,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL,  //PB6
PIN_4,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PB7

/*PORT C PINS*/
PIN_52,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PC0
PIN_51,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL,//PC1
PIN_50,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PC2
PIN_49,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PC3
PIN_16,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PC4
PIN_15,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PC5
PIN_14,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PC6
PIN_13,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PC7

/*PORT D PINS*/
PIN_61,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PD0
PIN_62,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PD1
PIN_63,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PD2
PIN_64,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PD3
PIN_43,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PD4
PIN_44,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PD5
PIN_53,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PD6
PIN_10,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PD7

/*PORT E PINS*/
PIN_9,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PE0
PIN_8,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL,  //PE1
PIN_7,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PE2
PIN_6,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PE3
PIN_59,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PE4
PIN_60,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL,//PE5

/*PORT F PINS*/
PIN_28,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL,  //PF0

PIN_29,PORT_PIN_OUT,OFF,INITIAL_LOW,Dir_Changeable,Mode_Changeable,PORT_PIN_MODE_DIO,DIGITAL,//PF1  (LED)

PIN_30,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL,  //PF2
PIN_31,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_NotChangeable,Mode_NotChangeable,PORT_PIN_MODE_DIO,DIGITAL, //PF3

PIN_5,PORT_PIN_IN,PULL_UP,INITIAL_HIGH,Dir_Changeable,Mode_Changeable,PORT_PIN_MODE_DIO ,DIGITAL //PF4  (BUTTON)





};



