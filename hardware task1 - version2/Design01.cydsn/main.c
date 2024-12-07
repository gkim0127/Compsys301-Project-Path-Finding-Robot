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
int count =0;
int array[1000] ={0};

/*
CY_ISR(tc_sample){
LED_Write(~LED_Read());

ADC_SAR_1_StartConvert();

isr_TC_ClearPending();
Timer_1_ReadStatusRegister();
}
*/

CY_ISR(eoc){
 

if(count < 999){
    int val = ADC_SAR_1_GetResult16();
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

int findMaximum(int array[1000]){
int maximum = 0;
    for(int i = 100; i < 1000-100; i ++){
        if (array[i]> maximum){
         maximum = array[i];
        }  
    }
    return maximum;
}


int main(void)

{   //isr_TC_StartEx(tc_sample);
    isr_EOC_StartEx(eoc);


    CyGlobalIntEnable; /* Enable global interrupts. */
    
    USBUART_1_Start(0,USBUART_1_5V_OPERATION);
    while(USBUART_1_GetConfiguration() == 0){}
    ADC_SAR_1_Start();
    Timer_1_Start();
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
  
    for(;;)
    {
        
        
        /* Place your application code here. */
        if(flag == 1){
           
            //int val = ADC_SAR_1_GetResult16();
            //int mVolts = ADC_SAR_1_CountsTo_mVolts(val);
            //int result = mVolts + 1024;
           int result=  findMaximum(array);
            char send[100];
                sprintf(send,"%d\r\n",result);
                usbPutString(send);
                flag = 0;
                if(result > 600){
                    LED_Write(1);
                }
                else{
                    LED_Write(0);
                }
                count = 0;
                memset(array,0,sizeof(array));
                Timer_1_Start();
                

        /*
            for(int i =100; i<count-100; i++){
                int result = array[i];
                char send[100];
                sprintf(send,"%d\r\n",result);
                usbPutString(send);
                
            }
            flag = 0;
            Timer_1_Start();
         */
        }
       
        CyDelay(1000);
    }
    
}




/* [] END OF FILE */
