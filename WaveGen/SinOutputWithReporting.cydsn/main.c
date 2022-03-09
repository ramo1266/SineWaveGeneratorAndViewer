/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif

#define TRUE 1
#define FALSE 0
#define EP_OUT_BULK 2
#define EP_IN_BULK 1
#define EP_IN_ISOC 3
#define BUFFERSIZE 64

// explicit Declaration 
_Bool ProcessCommand(uint8* Command, uint8* response);
_Bool StartAnalogOut();
_Bool StopAnalogOut();
_Bool SetFreq(uint8); 
int16 ReadVoltage();

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

   // uint8 const BufferSize = 64;
    uint8 OUTBuffer[BUFFERSIZE]; // Host writes OUT to device, HOST --> Device
    uint16 OUTBufferCount = 0;
    uint8 INBuffer[BUFFERSIZE];  // Host Read In from Device, HOST <--- Device

    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    USBCOMM_Start(0,USBCOMM_5V_OPERATION);
    while( 0 == USBCOMM_GetConfiguration()) // make sure the USB is Conf
        {
         
            
        }
      USBCOMM_EnableOutEP(EP_OUT_BULK);
       
    for(;;)
    {
        /* Place your application code here. */
        /* checks for Clear-ON-read Conf
        Clear on read means that when the host processor 
        reads the data from your peripheral, the registers 
        should reset themselves to zero. */
        
        if( 0 != USBCOMM_IsConfigurationChanged()) 
            if(0 != USBCOMM_GetConfiguration())
            {
              USBCOMM_EnableOutEP(EP_OUT_BULK); 
               
            }
       
        if( 0 != USBCOMM_GetConfiguration()) // make sure the CDC is Conf
        {
            if( USBCOMM_OUT_BUFFER_FULL == USBCOMM_GetEPState(EP_OUT_BULK))
            {
                OUTBufferCount = USBCOMM_GetEPCount(EP_OUT_BULK);
                if( OUTBufferCount != 0)
                {
                    // Discriptor set up as Manual Mode
                    // Does not need to wait for DMA to copy
                    USBCOMM_ReadOutEP(EP_OUT_BULK,OUTBuffer,OUTBufferCount);
                    USBCOMM_EnableOutEP(EP_OUT_BULK); 
                    ProcessCommand(OUTBuffer, INBuffer);
                 
                    while (USBCOMM_IN_BUFFER_EMPTY != USBCOMM_GetEPState(EP_IN_BULK))
                    {
                    }
                    USBCOMM_LoadInEP(EP_IN_BULK,INBuffer,BUFFERSIZE);   
                }
                   
            }
        }
        
        
        
        
        
    }
}


_Bool ProcessCommand(uint8 Command[BUFFERSIZE], uint8 response[BUFFERSIZE])
{
    /*  Avaiable commands 
        
        SA : starts the Analog Out
        STA : Stop the Analog Out
        F## : sets the Freq ## 
                01 set to 1 hertz 
        RV : reads Voltage
        
        Response
        SA
        STA
        F## : 1 to 10 
        response with OK
        otherwise with NG
    
        RV
        with votage
        
    
    */
   
    char cmdstring[BUFFERSIZE] ;
    sprintf(cmdstring,(const char*)Command); 
    
    if ( 0 == strncmp (cmdstring,"SA",2))   
    {
        StartAnalogOut(); 
       
        sprintf((char*)response,"OK");
        
        return TRUE;
    }
    if ( 0 == strncmp (cmdstring,"STP",3))   
    {
        StopAnalogOut();
       
        sprintf((char*)response,"OK");
        return TRUE;
    }
    if ( 0 == strncmp (cmdstring,"RV",2))   
    {
        int16 Volt = 0;
        float test = 3.1413;
        int test1 = 3421;
        char VoltChar[16];
        Volt = ReadVoltage();
        
       // sprintf(VoltChar,"%1.3F", Volt);
        sprintf(VoltChar,"%f", test);
        sprintf(VoltChar,"%d", test1);
        
        sprintf((char *)response,"%d", Volt);
      //  sprintf((char *)response,"%d", Volt);
       
        Volt = ReadVoltage();
        
        return TRUE;
    }
    if ( 0 == strncmp (cmdstring,"F",1))   
    {
        
        char frq_char[3];
        uint8 freq = 0;
       
        frq_char[0] = cmdstring[1];
        frq_char[1] = cmdstring[2];
         frq_char[2] = '\0';
        
        freq = atoi(frq_char);
        
        if( freq >= 1 && freq <= 10)
        {
            
            SetFreq(freq); 
            sprintf((char*)response,"OK");
            return TRUE;
        }
        else
        {
            sprintf((char*)response,"NG");
        }
        return TRUE;
    }
    else
    {
        // Error the invalid command
       sprintf((char*)response,"NG");
        return TRUE;
    }
    
    
}

_Bool StartAnalogOut()
{
    WaveGen_Start();
    AnalogClock_Start();
    WaveFormReader_Start();
    WaveFormReader_StartConvert();
    
    return TRUE;    
}

_Bool StopAnalogOut()
{
       WaveGen_Stop();
    return TRUE;    
}
_Bool SetFreq(uint8 freq)
{
    // should put error checking in this function .... MR
    uint16 SourceFreq = 24000; // the value is in Khz
    uint16 ClkDiv = (uint16) (SourceFreq/freq);
    AnalogClock_SetDividerValue(ClkDiv); // unknown behavior if clock is running or not.
    return TRUE;
}
int16 ReadVoltage()
{
    WaveFormReader_IsEndConversion(WaveFormReader_WAIT_FOR_RESULT);
    int16 res = WaveFormReader_GetResult16();
    int16 f =  WaveFormReader_CountsTo_mVolts(res);
    return f;
}
/* [] END OF FILE */
