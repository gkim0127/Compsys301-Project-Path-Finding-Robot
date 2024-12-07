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

#define LIGHT_CMP_VALUE 200

int flag=0;
int flag2=0;
int flag3=0;
int flag4=0;
int flag5=0;
int flag6=0;

int turnLock =0;

int count1 =0;
int count2 =0;
int count3 = 0;
int count4 = 0;
int count5 = 0;
int count6 = 0;


int array[10] ={0};
int array2[10] ={0};
int array3[10] ={0};
int array4[10] ={0};
int array5[10] ={0};
int array6[10] ={0};


int motor1 = 0;
int motor2 = 0;
int motor3 = 0;
int motor4 = 0;
int motor5 = 0;
int motor6 = 0;



int speed=0;
int flag33=0;

int offset = 5;

int startDuty = 90;
int leftDuty = 97;
int rightDuty = 0;


int leftTurn = 0;  //0  means no turns 
int rightTurn = 0;
int finishTurn = 0; // 0 means turn not finished

enum States {left_turn, right_turn, straight, stop, straight_left_adjust, straight_right_adjust};



int findMaximum(int array[10]){
int maximum = 0;
    for(int i = 0; i < 10; i ++){
        if (array[i]> maximum){
         maximum = array[i];
        }  
    }
    return maximum;
}

int findMinimum(int array[10]){
int minimum = 10000;
    for(int i = 0; i < 10; i ++){
        if (array[i] < minimum){
         minimum = array[i];
        }  
    }
    return minimum;
}   

int getSensor(int result){            
    // Using as a comparator / trigger
   
                    if(result < 200){
                        return 1;
                    }
                    else{
                        return 0;
                    }
            
                    count1 = 0;
                    memset(array,0,sizeof(array));
                    flag = 0;
}


CY_ISR(eoc1){
    
//    for(int i = 0; i < 5; i++) { // 5 is max ADC Channel
//        int16 val = ADC_SAR_Seq_1_GetResult16(i);
//        
//        array[i] = ADC_SAR_Seq_1_CountsTo_mVolts(val);
//    }
// 
    
    
    if(count1 < 9){
        int  val= ADC_SAR_Seq_1_GetResult16(0);
        
        int mVolts = ADC_SAR_Seq_1_CountsTo_mVolts(val);
        array[count1] = mVolts;
        count1++;
        }
    else{
        //Timer_1_Stop();
        count1 = 0;
    }
    
    if(count2 < 9){
        int  val2=ADC_SAR_Seq_1_GetResult16(1);
        int mVolts2 = ADC_SAR_Seq_1_CountsTo_mVolts(val2);
        
        array2[count2] = mVolts2;
        count2++;
        }
    else{
        //Timer_2_Stop();
        count2 = 0;
    }
    
    if(count3 < 9){
        int  val3=ADC_SAR_Seq_1_GetResult16(2);
        int mVolts3 = ADC_SAR_Seq_1_CountsTo_mVolts(val3);
        
        array3[count3] = mVolts3;
        count3++;
        }
    else{
        //Timer_2_Stop();
        count3 = 0;
    }
    if(count4 < 9){
        int  val4=ADC_SAR_Seq_1_GetResult16(3);
        int mVolts4 = ADC_SAR_Seq_1_CountsTo_mVolts(val4);
        
        array4[count4] = mVolts4;
        count4++;
        }
    else{
        //Timer_2_Stop();
        count4 = 0;
    }
    
    if(count5 < 9){
        int  val5=ADC_SAR_Seq_1_GetResult16(4);
        int mVolts5 = ADC_SAR_Seq_1_CountsTo_mVolts(val5);
        
        array5[count5] = mVolts5;
        count5++;
        }
    else{
        //Timer_2_Stop();
        count5 = 0;
    }
    
    if(count6 < 9){
        int  val6=ADC_SAR_Seq_1_GetResult16(5);
        int mVolts6 = ADC_SAR_Seq_1_CountsTo_mVolts(val6);
        
        array6[count6] = mVolts6;
        count6++;
        }
    else{
        //Timer_2_Stop();
        count6 = 0;
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


void DoLeftTurn(){
    PWM_leftmotor_Start();
    PWM_rightmotor_Start();
    
    //PWM_leftmotor_WriteCompare1(80);
    PWM_leftmotor_WriteCompare1(180);
    PWM_leftmotor_WriteCompare2(0);
    
    //PWM_rightmotor_WriteCompare1(60);
    PWM_rightmotor_WriteCompare1(180);      // prev value = 120
    PWM_rightmotor_WriteCompare2(0);
}

//void DoRightTurn(int rightTurn){ // COULD MODIFY TO TAKE INPUT PARAMETERS
  void DoRightTurn() {
    PWM_leftmotor_Start();
    PWM_rightmotor_Start();
    
    // initiate right turn
    // right turn; left motor forward
    PWM_leftmotor_WriteCompare1(0);
    //PWM_leftmotor_WriteCompare2(60);
    PWM_leftmotor_WriteCompare2(200);       // going forward -> 140 works 
        
    // right turn; right motor reverse
    PWM_rightmotor_WriteCompare1(0);
    PWM_rightmotor_WriteCompare2(200);    // reverse
}

void GoStraight(){
    PWM_leftmotor_Start();
    PWM_rightmotor_Start();
    PWM_leftmotor_WriteCompare1(0);
    PWM_leftmotor_WriteCompare2(97);

    PWM_rightmotor_WriteCompare1(90);
    PWM_rightmotor_WriteCompare2(0);
}
void Stop(){
    PWM_leftmotor_WriteCompare1(140);
    PWM_leftmotor_WriteCompare2(140);

    PWM_rightmotor_WriteCompare1(140);
    PWM_rightmotor_WriteCompare2(140);
}

void ArrangeToLeft(){
    PWM_leftmotor_Start();
    PWM_rightmotor_Start();
    PWM_leftmotor_WriteCompare1(0);
    
    leftDuty = leftDuty+ offset;
    PWM_leftmotor_WriteCompare2(leftDuty);
    
    PWM_rightmotor_WriteCompare1(startDuty);
    
    rightDuty = rightDuty+ offset;
    PWM_rightmotor_WriteCompare2(rightDuty);
}

void ArrangeToRight(){
    PWM_leftmotor_Start();
    PWM_rightmotor_Start();
    PWM_leftmotor_WriteCompare1(0+offset);
    PWM_leftmotor_WriteCompare2(startDuty);

    PWM_rightmotor_WriteCompare1(startDuty+offset);
    PWM_rightmotor_WriteCompare2(0);
}

void updateMotorSpeed_Right(int speed) {    
    PWM_rightmotor_WriteCompare1(255 - speed);
    PWM_rightmotor_WriteCompare2(255-(255-speed));
}

void updateMotorSpeed_Left(int speed) {    
    PWM_leftmotor_WriteCompare2(255 - speed);
    PWM_leftmotor_WriteCompare1(255-(255-speed));
}

void updateMotorSpeed(int speed) {
    updateMotorSpeed_Right(speed);
    updateMotorSpeed_Left(speed);   
}

int main(void) 
{
    isr_EOC_3_StartEx(eoc1);
    CyGlobalIntEnable; /* Enable global interrupts. */

    USBUART_1_Start(0,USBUART_1_5V_OPERATION);
    ADC_SAR_Seq_1_Start();
    Timer_2_Start();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    enum States FSM;

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
        
        /*
        if(flag == 1){
            flag = 0;`
            char send[100];
            sprintf(send,"%d\r\n",speed);
            usbPutString(send);
        }
        */        

        int front = findMaximum(array);
        int left = findMaximum(array2);
        int right = findMaximum(array3);
        int far_left = findMaximum(array4);
        int far_right = findMaximum(array5);
        int back = findMaximum(array6);
        
        int cmp_val = 500;
        
//        char temp[100];
//    
//        sprintf(temp, "Array %d = %d \n", 1, front);
//        usbPutString(temp);
//        
//        sprintf(temp, "Array %d = %d \n", 2, left);
//        usbPutString(temp);
//
//        
//        sprintf(temp, "Array %d = %d \n", 3, right);
//        usbPutString(temp);
//
//        
//        sprintf(temp, "Array %d = %d \n", 4, far_left);
//        usbPutString(temp);
//
//        
//        sprintf(temp, "Array %d = %d \n", 5, far_right);
//        usbPutString(temp);
//
//        
//        sprintf(temp, "Array %d = %d \n", 6, back);
//        usbPutString(temp);
        

        /**
        *   x < cmp_val means that sensor x is INSIDE the projector path
        *
        *   x > cmp_val means that sensor x is OUTSIDE the projector path
        */

        
        // GO LEFT PRIORITY 1
        //if( (far_left < cmp_val) && (left<cmp_val) && (right<cmp_val)) { 
        //if( (far_left < cmp_val) && (right < cmp_val)   ) { 
        if (far_left < cmp_val) {
            leftTurn = 1;
            FSM = left_turn;
        
        // GO RIGHT PRIORITY 2
        //} else if( (far_right < cmp_val) && (left<cmp_val) && (right<cmp_val) && (back<cmp_val)) {  
        //} else if( (far_right < cmp_val) && (back < cmp_val)) {
        } else if (far_right < cmp_val) {  
            rightTurn = 1;
            FSM = right_turn;
        
            
        // Go Foward PRIORITY 3 - 2, 3, 6 are in path
        } else if ((left < cmp_val) && (right < cmp_val) && (back<cmp_val)   ) {
            //rightTurn = 0;
            //leftTurn = 0;
            FSM = straight; // go straight only
        
                                  
        // STRAIGHT lEFT ADJUSTMENT - left sensor is out of path
        //}   else if (   ((left > cmp_val) && (right < cmp_val) && (back<cmp_val)) || ((left > cmp_val) && (right<cmp_val)) || ((left > cmp_val) && (back<cmp_val))) {
        }  else if (   ((left > cmp_val) && (right < cmp_val) && (back<cmp_val)) || ((left > cmp_val) && (right<cmp_val))) {
            FSM = straight_left_adjust;
            
            
        // STRAIGHT RIGHT ADJUSTMENT - right sensor is out of path
        //} else if (((left < cmp_val) && (right > cmp_val) && (back<cmp_val))|| ((left < cmp_val) && (right>cmp_val)) || ((back < cmp_val) && (right>cmp_val)) ) {
        }else if (((left < cmp_val) && (right > cmp_val) && (back<cmp_val))|| ((left < cmp_val) && (right>cmp_val))) {
            FSM = straight_right_adjust;
            
            
        // check for INCOMPLETE LEFT turn    
        //} else if ((leftTurn == 1)&&(back<cmp_val)) {
        } else if ( (leftTurn == 1) && ((left<cmp_val) || (right<cmp_val) || (back<cmp_val)) ) {
          //} else if (leftTurn == 1) {
            // continue left turn
            //if ((left<cmp_val) || (right<cmp_val) || (back<cmp_val)) {
                FSM = left_turn;             
            //}
            
        // check for INCOMPLETE RIGHT turn  
        //} else if ( (rightTurn == 1) && ((left<cmp_val) || (right<cmp_val) || (back<cmp_val)) ) {
         } else if (rightTurn == 1) {
            
            if ((left<cmp_val) || (right<cmp_val) || (back<cmp_val)) {
            // continue right turn
            FSM = right_turn;
            
            }
            
        // if no sensors are inside path, check which turn flag is currently high and adjust
        } else if ( (far_left && left && right && far_right && front && back) > cmp_val  ) {
            
            if (leftTurn == 1) {
                FSM = left_turn;   
            } else if (rightTurn == 1) {
                FSM = right_turn;
            } else {
                FSM = straight;
            }
                       
            
        //} else if ( (front < cmp_val) && (left<cmp_val) && (right<cmp_val)) { //  CHECK IF TURN COMPLETE
        } else if ( (front < cmp_val)  && (  (left<cmp_val) || (right<cmp_val)   )) {    // TRY THIS FIRST!!!
        //} else if (front < cmp_val) {
            
            // turn is complete set both flags to 0
            rightTurn = 0;
            leftTurn = 0;
            FSM = straight;
            
           

        } else {// LOWEST PRIORITY (IDK STATE)
            //FSM = stop;
            
            
            if (leftTurn == 1) {
                FSM = left_turn;   
            } else if (rightTurn == 1) {
                FSM = right_turn;
            } else {
                FSM = stop;
            }
        }
        

        
        // FSM switch cases
        switch(FSM) {
            
            // go straight only
            case straight:
                GoStraight();
                break;
                
                
            // adjust when left sensor is out of path
            case straight_left_adjust:
                ArrangeToLeft();
                break;
                
                
            // adjust when right sensor is out of path
            case straight_right_adjust:
                ArrangeToRight();
                break;
                
            // left turn
            case left_turn:
                if (leftTurn == 1) {
                    DoLeftTurn();
                } else {
                    GoStraight();   
                }
                break;
                
            // right turn
            case right_turn:
                if (rightTurn == 1) {
                    DoRightTurn();
                } else {
                    GoStraight();
                }
                break;
                
            // stop movement
            case stop:
                Stop();
                break;
        }
        

//     if(flag == 1){
//                     
//            
//             int result=  findMaximum(array) -findMinimum(array);
//             //char send[100];
//              //sprintf(send,"%d\r\n",result);
//             // usbPutString(send);
//           
//                    if(result < 200){
//
//                        motor1 = 1;
//                        finishTurn = 1; // turn has completed
//                    }
//                    else{
//
//                         motor1 = 0;
//                    }
//            
//                    count1 = 0;
//                    memset(array,0,sizeof(array));
//                    flag = 0;
//                    //Timer_1_Start();
//    }
//        
//        
//      if(flag2 == 1){
//                 int result2=  findMaximum(array2) -findMinimum(array2);
//               
//                        if(result2 < 200){
//
//                            motor2 = 1;
//                        }
//                        else{
//                            motor2 = 0;
//                        }     
//                        count2 = 0;
//                        memset(array,0,sizeof(array2));
//                        flag2 = 0;      
//    }
//     if(flag3 == 1){
//                 int result3=  findMaximum(array3) -findMinimum(array3);
//               
//                        if(result3 < 200){
//
//                            motor3 = 1;
//                        }
//                        else{
//
//                            motor3 = 0;
//                        }     
//                        count3 = 0;
//                        memset(array,0,sizeof(array3));
//                        flag3 = 0;      
//    }
//    
//    
//    // sensor 4 to detect LEFT TURN
//     if(flag4 == 1){
//                 int result4=  findMaximum(array4) -findMinimum(array4);
//               
//                        if(result4 < 200){
//                            motor4 = 1;
//                            
//                        }
//                        else{
//                            motor4 = 0;
//                        }     
//                        count4 = 0;
//                        memset(array,0,sizeof(array4));
//                        flag4 = 0;      
//    }
//    
//    if(flag5 == 1){
//                 int result5=  findMaximum(array5) -findMinimum(array5);
//               
//                        if(result5 < 200){
//                            motor5 = 1;
//                            rightTurn = 1; // 1 means there is a turn
//                            LED_1_Write(1);
//                        }
//                        else{
//                            motor5 = 0;
//                        }     
//                        count5 = 0;
//                        memset(array,0,sizeof(array5));
//                        flag5 = 0;      
//    }
//    
//    
//    if(flag6 == 1){
//                 int result6=  findMaximum(array6) -findMinimum(array6);
//               
//                        if(result6 < 200){
//                            motor6 = 1;
//                        }
//                        else{
//                            motor6 = 0;
//                        }     
//                        count6 = 0;
//                        memset(array,0,sizeof(array6));
//                        flag6 = 0;      
//    }
//        }
        
        
        
        }
        return 0;
    
}

/* [] END OF FILE */
