
//main.c
//Toggles the Red LED of TM4C Launchpad when SW1(PF4) is pushed and held
//PF4 is negative logic,i.e 0 is on and non-zero is off
#include "stdint.h"
#include "stdbool.h"
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "timer.h"


unsigned long Led;

void Delay(void){unsigned long volatile time;
  time = 800000;
  while(time){
		time--;
  }
}

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}

int main(void){
  PortF_Init();
  TimerDisable(0,0);
  while(1){
   //if(PF4 == 0x0){
    Led = 0x02;            // reverse value of LED
    GPIO_PORTF_DATA_R = Led;   // write value to PORTF DATA register,toggle led
    Delay();
    Led = 0x04;            // reverse value of LED
    GPIO_PORTF_DATA_R = Led;   // write value to PORTF DATA register,toggle led
    Delay();
    Led = 0x08;            // reverse value of LED
    GPIO_PORTF_DATA_R = Led;   // write value to PORTF DATA register,toggle led
    Delay();
    /*Led = 0x0A;            // reverse value of LED
    GPIO_PORTF_DATA_R = Led;   // write value to PORTF DATA register,toggle led
    Delay();*/
   // }
  }
}

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06
