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
 int flag=0;
int flag2=0;
int count =0;
int count2 =0;
int array[100] ={0};
int array2[100] ={0};
/*
CY_ISR(tc_sample){
LED_Write(~LED_Read());

ADC_SAR_1_StartConvert();

isr_TC_ClearPending();
Timer_1_ReadStatusRegister();
}
*/

CY_ISR(eoc2){
if(count2 < 99){
        int  val2= ADC_SAR_2_GetResult16();
        int mVolts2 = ADC_SAR_2_CountsTo_mVolts(val2);
        array2[count2] = mVolts2;
        count2++;
        }
    else{
        Timer_2_Stop();
        flag2 = 1;
    }
}


CY_ISR(eoc){
    if(count < 99){
        int  val= ADC_SAR_1_GetResult16();
        int mVolts = ADC_SAR_1_CountsTo_mVolts(val);
        array[count] = mVolts;
        count++;
        }
    else{
        Timer_1_Stop();
        flag = 1;
    }
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

int findMaximum(int array[100]){
int maximum = 0;
    for(int i = 0; i < 100; i ++){
        if (array[i]> maximum){
         maximum = array[i];
        }  
    }
    return maximum;
}

int findMinimum(int array[100]){
int minimum = 10000;
    for(int i = 0; i < 100; i ++){
        if (array[i] < minimum){
         minimum = array[i];
        }  
    }
    return minimum;
}


int main(void)

{   //isr_TC_StartEx(tc_sample);
    isr_EOC_StartEx(eoc);
    isr_EOC2_StartEx(eoc2);


    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //USBUART_1_Start(0,USBUART_1_5V_OPERATION);
    //while(USBUART_1_GetConfiguration() == 0){}
    ADC_SAR_1_Start();
    Timer_1_Start();
    ADC_SAR_2_Start();
    Timer_2_Start();
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
  
    for(;;)
    {
        
        
        /* Place your application code here. */
        if(flag == 1){
                     
            
             int result=  findMaximum(array) -findMinimum(array);
             //char send[100];
              //sprintf(send,"%d\r\n",result);
             // usbPutString(send);
           
                    if(result < 400){
                        LED_Write(1);
                    }
                    else{
                        LED_Write(0);
                    }
            
                    count = 0;
                    memset(array,0,sizeof(array));
                    flag = 0;
                    Timer_1_Start();
    }
        
        
      if(flag2 == 1){
                     
            
                 int result2=  findMaximum(array2) -findMinimum(array2);
                // char send[100];
                 //sprintf(send,"%d\r\n",result2);
                 //usbPutString(send);
               
                        if(result2 < 400){
                            LED_1_Write(1);
                        }
                        else{
                            LED_1_Write(0);
                        }
                
                        count2 = 0;
                        memset(array,0,sizeof(array2));
                        flag2 = 0;
                        Timer_2_Start();


    
            CyDelay(1);      
    }
}

}


/* [] END OF FILE */
