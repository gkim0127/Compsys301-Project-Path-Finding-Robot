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
#include <stdio.h>
#include <project.h>
#include <string.h>


int16 count1=0;
int16 count2 = 0;
int speedresult = 0;

double countsPerSec = 0;
double currrentDistance = 0;

int result1= 0;
int flag=0;
int distance =50;

int getDistance(int count){
    currrentDistance = 20.42*count/228;
    int result = (int) currrentDistance;
    return result;
}

void stopTheMotor(){
    PWM_leftmotor_WriteCompare1(127);
    PWM_leftmotor_WriteCompare2(127);
    
    PWM_rightmotor_WriteCompare1(127);
    PWM_rightmotor_WriteCompare2(127);

}



CY_ISR(TC){
    
    
    Timer_1_ReadStatusRegister(); 
    flag =1;
    count2 = QuadDec_2_GetCounter() - count1;
    count1= QuadDec_2_GetCounter();
    
    result1 = getDistance(count1);
    if(result1 >distance ){
        stopTheMotor();
    }

    
    countsPerSec = count2 *20;
    countsPerSec = 20.42*countsPerSec /228;
    speedresult = (int)countsPerSec;
    
    
    
}



void usbPutString(char *s)
{
// !! Assumes that *s is a string with allocated space >=64 chars     
//  Since USB implementation retricts data packets to 64 chars, this function truncates the
//  length to 62 char (63rd char is a '!')
    
    while (USBUART_1_CDCIsReady() == 0);
    s[63]='\0';
    s[62]='!';
    USBUART_1_PutData((uint8*)s,strlen(s));
}




int main(void)
{
    
    isr_TC_StartEx(TC);
    CyGlobalIntEnable; /* Enable global interrupts. */

    USBUART_1_Start(0,USBUART_1_5V_OPERATION);
    Timer_1_Start();
    QuadDec_1_Start();
    QuadDec_2_Start();
    QuadDec_2_SetCounter(0);
    
    //while(USBUART_1_GetConfiguration() == 0){}

    
 
    //leftmotor moving backward
    PWM_leftmotor_Start();
    
    //rightmotor moving forward
    PWM_rightmotor_Start();
    
    PWM_leftmotor_WriteCompare1(0);
    PWM_leftmotor_WriteCompare2(127);
    
    PWM_rightmotor_WriteCompare1(127);
    PWM_rightmotor_WriteCompare2(0);
    
    

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        /*
        int result=  522;
        char send[100];
        sprintf(send,"%d\r\n",result);
        usbPutString(send);
        CyDelay(100);
        */
        
        if(flag == 1){
            flag = 0;
            char send[100];
            sprintf(send,"%d",result1);
            usbPutString(send);
            usbPutString("cm/s");
            usbPutString("\r\n");
          
        }   
    }
}

/* [] END OF FILE */
