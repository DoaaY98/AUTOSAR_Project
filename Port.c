 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"
#include "tm4c123gh6pm_registers.h"

/************************************************************************
************Det Error Detection**********************************
*/

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and PORT Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif
   /*Variables to be used throughout the functions*/
STATIC const Port_ConfigPin * Port_PinPTR = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;  
STATIC uint8 Port_no=0;
STATIC uint8 Pin_no=0;


/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/

void Port_Init( const Port_ConfigType* ConfigPtr ){
  

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{
		/*
		 * point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		
		Port_PinPTR = ConfigPtr->Pins; /* address of the first pin structure --> pin[0]*/
	


//PIN_17,PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_Changeable,Mode_Changeable,PORT_PIN_MODE_DIO
         volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
         volatile uint32 delay = 0;
    
        uint8 i =0; /*Iteration*/
        /*Set the Pin No and Port No */
        for(i=0;i<PORT_CONFIGURED_CHANNELS;i++){
        
          if( Port_PinPTR[i].pin_num >=0 && Port_PinPTR[i].pin_num <8 ){
          /*PORT A*/
           Port_no=0; 
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
           Pin_no=(Port_PinPTR[i].pin_num)-A_SHIFT; /*PIN OF PORT A IS 0,1,2,3,4,5,6,7*/
          }
          
          else if( Port_PinPTR[i].pin_num >=8 && Port_PinPTR[i].pin_num <16){
          /*PORT B*/
            Port_no=1; 
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
           Pin_no=(Port_PinPTR[i].pin_num)-B_SHIFT; /*PIN OF PORT B IS 8,9,10,11,12,13,14,15*/
          }
          
          else if( Port_PinPTR[i].pin_num >=16 && Port_PinPTR[i].pin_num <24){
          /*PORT C*/
            continue;
            /*J-TAG PORT*/
           //Port_no=2;  
           //PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
           //Pin_no=(Port_PinPTR[i].pin_num)-C_SHIFT; /*PIN OF PORT C IS 16,17,18,19,20,21,22,23*/
          }
          
          else if( Port_PinPTR[i].pin_num >=24 && Port_PinPTR[i].pin_num <32){
          /*PORT D*/
           Port_no=3;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
           Pin_no=(Port_PinPTR[i].pin_num)-D_SHIFT; /*PIN OF PORT D IS 24,25,26,27,28,29,30,31*/
          }
          
          else if( Port_PinPTR[i].pin_num >=32 && Port_PinPTR[i].pin_num <38){
          /*PORT E*/
           Port_no=4;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
           Pin_no=(Port_PinPTR[i].pin_num)-E_SHIFT; /*PIN OF PORT E IS 32,33,34,35,36,37*/
          }
          
          else if( Port_PinPTR[i].pin_num >=38 && Port_PinPTR[i].pin_num <43){
          /*PORT F*/
           Port_no=5;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
           Pin_no=(Port_PinPTR[i].pin_num)-F_SHIFT; /*PIN OF PORT F IS 38,39,40,41,42*/
          }
        
          else{
                /*Do Nothing*/
          }
          
          /* Enable clock for PORT and allow time for clock to start*/
          
          SYSCTL_REGCGC2_REG |= (1<<Port_no);
          delay = SYSCTL_REGCGC2_REG;
        
          if( ((Port_no== 3) && (Pin_no == 7)) || ((Port_no == 5) && (Pin_no == 0)) ) /* PD7 or PF0 */
              {
                  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Pin_no);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
              }
          else if( (Port_no == 2) && (Pin_no <= 3) ) /* PC0 to PC3 */
              {
                  /* Do Nothing ...  this is the JTAG pins */
                  return;
              }
          else
              {
                /* Do Nothing ... No need to unlock the commit register for this pin */
              }
    
  //PORT_PIN_IN,PULL_UP,INITIAL_LOW,Dir_Changeable,Mode_Changeable,PORT_PIN_MODE_DIO      
        
          /*Set Pin Direction */
           if(Port_PinPTR[i].direction== PORT_PIN_OUT)
              {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Pin_no);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
                if(Port_PinPTR[i].initial_value == STD_HIGH)
                    {
                      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) ,Pin_no);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                    }
                else
                    {
                      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Pin_no);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                    }
              }
          else if(Port_PinPTR[i].direction== PORT_PIN_IN)
              {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,Pin_no);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
                if(Port_PinPTR[i].resistor == PULL_UP)
                    {
                      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) ,Pin_no);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                    }
                else if(Port_PinPTR[i].resistor == PULL_DOWN)
                    {
                      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Pin_no);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                    }
                else
                    {
                      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Pin_no);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) ,Pin_no);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                    }
              }
        else
            {
                    /* Do Nothing */
            }
       
       //Dir_Changeable,Mode_Changeable,PORT_PIN_MODE_DIO,DIGITAL
          
          /*Set Pin Analog or Digital Value*/
          
          if(Port_PinPTR[i].DigOrAna==DIGITAL){
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Pin_no);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Pin_no);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
          }
          else if(Port_PinPTR[i].DigOrAna==ANALOG){
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Pin_no);      /* SET the corresponding bit in the GPIOAMSEL register to ENABLE analog functionality on this pin */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Pin_no);        /* CLEAR the corresponding bit in the GPIODEN register to DISABLE digital functionality on this pin */
       
          
          }
          else{
           /*DO NOTHING*/
          }
       
          
          //Dir_Changeable,Mode_Changeable,PORT_PIN_MODE_DIO
          /*Set Mode of Pin*/
          if(Port_PinPTR[i].Mode==PORT_PIN_MODE_DIO){
          
                 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Pin_no);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin_no * 4));     /* Clear the PMCx bits for this pin */
    
          
          }
          
          else{
              
                 SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Pin_no);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |=( (0x00000000)+(Port_PinPTR[i].Mode) )<< (Pin_no * 4);     /* SET the PMCx bits for this pin */
    
          
          
          }
          
           //Dir_Changeable,Mode_Changeable
          
          
          
          
          
       /*End of for loop*/
        }




 /*Set the module state to initialized*/
      Port_Status       = PORT_INITIALIZED;
        }
}


/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Port Pin ID number , Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API==STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ){

    boolean error = FALSE;
 
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status )
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/*check if entered port pin is incorrect */
	if (PORT_CONFIGURED_CHANNELS <= Pin)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
  


        if(FALSE==error){
          
         
            #if (PORT_DEV_ERROR_DETECT == STD_ON)
                   if(Port_PinPTR[Pin].Port_PinDirectionChangeable==Dir_NotChangeable){
                    /*Port is not direction changeable*/
                             Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
                   }
                   else  
            #endif
                   {
                          
                    
        
            
          /*Pin Direction is changeable*/
             volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
              if( Port_PinPTR[Pin].pin_num >=0 && Port_PinPTR[Pin].pin_num <8 ){
          /*PORT A*/
           Port_no=0; 
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
           Pin_no=(Port_PinPTR[Pin].pin_num)-A_SHIFT; /*PIN OF PORT A IS 0,1,2,3,4,5,6,7*/
          }
          
          else if( Port_PinPTR[Pin].pin_num >=8 && Port_PinPTR[Pin].pin_num <16){
          /*PORT B*/
            Port_no=1; 
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
           Pin_no=(Port_PinPTR[Pin].pin_num)-B_SHIFT; /*PIN OF PORT B IS 8,9,10,11,12,13,14,15*/
          }
          
          else if( Port_PinPTR[Pin].pin_num >=16 && Port_PinPTR[Pin].pin_num <24){
          /*PORT C*/
            
            /*J-TAG PORT*/
           //Port_no=2;  
           //PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
           //Pin_no=(Port_PinPTR[i].pin_num)-C_SHIFT; /*PIN OF PORT C IS 16,17,18,19,20,21,22,23*/
          }
          
          else if( Port_PinPTR[Pin].pin_num >=24 && Port_PinPTR[Pin].pin_num <32){
          /*PORT D*/
           Port_no=3;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
           Pin_no=(Port_PinPTR[Pin].pin_num)-D_SHIFT; /*PIN OF PORT D IS 24,25,26,27,28,29,30,31*/
          }
          
          else if( Port_PinPTR[Pin].pin_num >=32 && Port_PinPTR[Pin].pin_num <38){
          /*PORT E*/
           Port_no=4;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
           Pin_no=(Port_PinPTR[Pin].pin_num)-E_SHIFT; /*PIN OF PORT E IS 32,33,34,35,36,37*/
          }
          
          else if( Port_PinPTR[Pin].pin_num >=38 && Port_PinPTR[Pin].pin_num <43){
          /*PORT F*/
           Port_no=5;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
           Pin_no=(Port_PinPTR[Pin].pin_num)-F_SHIFT; /*PIN OF PORT F IS 38,39,40,41,42*/
          }
        
          else{
                /*Do Nothing*/
          }
          
            if(Direction== PORT_PIN_OUT)
              {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Pin_no);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
              }
          else if(Direction== PORT_PIN_IN)
              {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,Pin_no);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
              }
        else
            {
                    /* Do Nothing */
            }
            
          
            
            } /*End of else of DET Error PORT_E_DIRECTION_UNCHANGEABLE code*/ 
            
          } /*End of If(FALSE=ERROR) Condition*/
          
       
       /*TRUE=ERROR*/ 
        else{
        
        
        /*Do Nothing*/
        }




/*End of set_pin_Direction_fn*/
}
#endif


/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Refreshes port direction.
************************************************************************************/

void Port_RefreshPortDirection( void ){
  
  boolean error = FALSE;
  
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status )
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	
#endif

        if(FALSE==error){
        
        uint8 i =0; /*Iteration*/
        /*Set the Pin No and Port No */
        for(i=0;i<PORT_CONFIGURED_CHANNELS;i++){
          
          
          if(Port_PinPTR[i].Port_PinDirectionChangeable==Dir_Changeable){
            /*If port pin is changeable skip */
              continue;
          }
          else {
          /* Do Nothing*/
          }
           volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
           if( Port_PinPTR[i].pin_num >=0 && Port_PinPTR[i].pin_num <8 ){
          /*PORT A*/
           Port_no=0; 
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
           Pin_no=(Port_PinPTR[i].pin_num)-A_SHIFT; /*PIN OF PORT A IS 0,1,2,3,4,5,6,7*/
          }
          
          else if( Port_PinPTR[i].pin_num >=8 && Port_PinPTR[i].pin_num <16){
          /*PORT B*/
            Port_no=1; 
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
           Pin_no=(Port_PinPTR[i].pin_num)-B_SHIFT; /*PIN OF PORT B IS 8,9,10,11,12,13,14,15*/
          }
          
          else if( Port_PinPTR[i].pin_num >=16 && Port_PinPTR[i].pin_num <24){
          /*PORT C*/
            continue;
            /*J-TAG PORT*/
           //Port_no=2;  
           //PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
           //Pin_no=(Port_PinPTR[i].pin_num)-C_SHIFT; /*PIN OF PORT C IS 16,17,18,19,20,21,22,23*/
          }
          
          else if( Port_PinPTR[i].pin_num >=24 && Port_PinPTR[i].pin_num <32){
          /*PORT D*/
           Port_no=3;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
           Pin_no=(Port_PinPTR[i].pin_num)-D_SHIFT; /*PIN OF PORT D IS 24,25,26,27,28,29,30,31*/
          }
          
          else if( Port_PinPTR[i].pin_num >=32 && Port_PinPTR[i].pin_num <38){
          /*PORT E*/
           Port_no=4;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
           Pin_no=(Port_PinPTR[i].pin_num)-E_SHIFT; /*PIN OF PORT E IS 32,33,34,35,36,37*/
          }
          
          else if( Port_PinPTR[i].pin_num >=38 && Port_PinPTR[i].pin_num <43){
          /*PORT F*/
           Port_no=5;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
           Pin_no=(Port_PinPTR[i].pin_num)-F_SHIFT; /*PIN OF PORT F IS 38,39,40,41,42*/
          }
        
          else{
                /*Do Nothing*/
          }
          
          /* Refresh the direction of the Pin*/
          
          
          /*Set Pin Direction */
           if(Port_PinPTR[i].direction== PORT_PIN_OUT)
              {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Pin_no);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
               
              }
          else if(Port_PinPTR[i].direction== PORT_PIN_IN)
              {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,Pin_no);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
                
              }
        else
            {
                    /* Do Nothing */
            }
          
          
          
          
          
          
        
        }
        /*End of for loop*/
        }
        
        
        else
	{
		/* No Action Required */
	}

}


/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): Pointer to where to store the version information of this module.
* Return value: None
* Description:Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo ){
//PORT_GET_VERSION_INFO_SID
  
  boolean error = FALSE;
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status )
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        /*Api called with a NULL Pointer Parameter*/
        if (NULL_PTR == versioninfo )
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        
	
#endif
        
        if(FALSE==error){
        
        
        /* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
        
        
        }
        
        else{
        
        /*No Action Required*/
        }


}
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Port Pin ID number, New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/


#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode ){
  boolean error=FALSE;
//PORT_SET_PIN_MODE_SID
   #if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status )
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        
        /*Check if pin passed is correct*/
        
        if (PORT_CONFIGURED_CHANNELS <= Pin)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
         /*Check if mode is correct*/
        if (PORT_MODE_CHECK <= Mode)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
		error = TRUE;
	}
	else
	{
	
          /* No Action Required */
	}    
    #endif    
  
        if(FALSE==error){
            
        
            #if (PORT_DEV_ERROR_DETECT == STD_ON)
                if(Port_PinPTR[Pin].Port_PinModeChangeable==Mode_NotChangeable){
                    /*Port is not Mode changeable*/
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
                }
        
        else
            #endif
         {
        
          /*CHANGE MODE OF PIN*/
           volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
          if( Port_PinPTR[Pin].pin_num >=0 && Port_PinPTR[Pin].pin_num <8 ){
          /*PORT A*/
           Port_no=0; 
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
           Pin_no=(Port_PinPTR[Pin].pin_num)-A_SHIFT; /*PIN OF PORT A IS 0,1,2,3,4,5,6,7*/
          }
          
          else if( Port_PinPTR[Pin].pin_num >=8 && Port_PinPTR[Pin].pin_num <16){
          /*PORT B*/
            Port_no=1; 
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
           Pin_no=(Port_PinPTR[Pin].pin_num)-B_SHIFT; /*PIN OF PORT B IS 8,9,10,11,12,13,14,15*/
          }
          
          else if( Port_PinPTR[Pin].pin_num >=16 && Port_PinPTR[Pin].pin_num <24){
         /*PORT C*/
            
            /*J-TAG PORT*/
           //Port_no=2;  
           //PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
           //Pin_no=(Port_PinPTR[i].pin_num)-C_SHIFT; /*PIN OF PORT C IS 16,17,18,19,20,21,22,23*/
          }
          
          else if( Port_PinPTR[Pin].pin_num >=24 && Port_PinPTR[Pin].pin_num <32){
          /*PORT D*/
           Port_no=3;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
           Pin_no=(Port_PinPTR[Pin].pin_num)-D_SHIFT; /*PIN OF PORT D IS 24,25,26,27,28,29,30,31*/
          }
          
          else if( Port_PinPTR[Pin].pin_num >=32 && Port_PinPTR[Pin].pin_num <38){
          /*PORT E*/
           Port_no=4;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
           Pin_no=(Port_PinPTR[Pin].pin_num)-E_SHIFT; /*PIN OF PORT E IS 32,33,34,35,36,37*/
          }
          
          else if( Port_PinPTR[Pin].pin_num >=38 && Port_PinPTR[Pin].pin_num <43){
          /*PORT F*/
           Port_no=5;  
           PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
           Pin_no=(Port_PinPTR[Pin].pin_num)-F_SHIFT; /*PIN OF PORT F IS 38,39,40,41,42*/
          }
        
          else{
                /*Do Nothing*/
          }
          
        /*Set Mode of Pin*/
          if(Port_PinPTR[Pin].Mode==PORT_PIN_MODE_DIO){
          
                 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Pin_no);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin_no * 4));     /* Clear the PMCx bits for this pin */
    
          
          }
          
          else{
              
                 SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Pin_no);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |=( (0x00000000)+(Mode) )<< (Pin_no * 4);     /* SET the PMCx bits for this pin */
    
          
          
          }
        
        }
          
          
        }
        
        else{
        
          /*Do Nothing */
        
        
        }


}
#endif










