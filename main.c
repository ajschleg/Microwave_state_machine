#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "bb_cnt.h"
#include "hc12_hal.h"
#include "microwave.h"

/*A counter is defined in cnt_test.c.  The counter definition includes
(1) the variables for counter flag, counter current value, counter terminate value, and callback function, and
(2) a counter structure that points to all the counter related variables and callback function.
*/

#define FACTOR 1
#define ON   0xFF
#define OFF  0x00

int edgeCount;
int led_enable;
unsigned int start_time;
unsigned int stop_time;
unsigned int period;
unsigned int cmpVal;


U8		counter_expired;   //stored in RAM
U16     counter_value;
U16		counter_terminate_value=FACTOR;
void 	counter_callback(void);

Counter_Type 	counter =                   //stored in ROM
{
 	(U8*)    &counter_expired, 
	(U16 *) &counter_value, 
	(U16 *) &counter_terminate_value,
	&counter_callback
};

void initTimerIC(void); 
void initTimerOC(void);

interrupt void TIM1_CH4_ISR(void);


/*The counter test program initializes the counter, reset the counter and service the counter 30,000 times.  
The counter should expire after being serviced 30,000 times and hence calls the callback function.

The LED in channel PA0 is turned on and off alternatively each time after the counter is expired.

If we call BB_Service_Counter in real-time timer interrupt service routine, the counter can be a timer. 
*/
void main(void) {
      int    i = 0;
		edgeCount = 0;
		led_enable = 0;


      DIO_CHAN_ENB(CHAN1);  /* Enable PS0 as I/O port */
      DIO_CHAN_OUT(CHAN1);  	/* Set PA0 as a output port */
      
      BB_Initialize_Counter(&counter);
      BB_Reset_Counter(&counter);
      initTimerOC();
      
      EnableInterrupts;
      
      while ( 1 ) 
      { 
            //BB_Service_Counter(&counter); 
      }
}


void counter_callback()  {
      static int i;
      BB_Reset_Counter(&counter);
      if (i != 0 )  
      {  
            DIO_CHAN_HI(CHAN1);  
            i = 0;
      }
      else  
      {  
            DIO_CHAN_LO(CHAN1);    
            i = 1;    
      }  
}

interrupt void TIM1_CH4_ISR(void) //Vector 36
{
	/*Flash LEDs while enabled*/
    BB_Service_Counter(&counter); 
	
	/*Clear timer interrupt flag*/
	TIM1_TFLG1_C4F = 1;		
}
   
void initTimerOC(void)
{
	/*set timer 1 to output compare*/
	TIM1_TIOS = 0x10;
	
	/*Enable timer 1*/
	TIM1_TSCR1 = 0x80;
	
	/*Frequency of the prescalar*/
	TIM1_TSCR2 = 0x06;
	
	/*Enable fast flag*/
	//TIM1_TSCR1_TFFCA = 1;
	
	/*Enable timer 1 interrupt, channel 4*/
	TIM1_TIE_C4I = 1;
	
	/*Set value to compare to*/
	TIM1_TC4 = FACTOR;
}





