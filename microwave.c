#include <stdio.h>
#include "microwave.h"

U8 timer1_switch;
U8 timer2_swtich;

/*uwave variable and initialization*/
const U8 microwave_next_state_table[NUM_OF_UWAVE_STATES][NUM_OF_UWAVE_EVENTS] = 
{	IGN,IGN,IGN,IGN,DOOR_CLOSED,
	POWER_ON,POWER_OFF,IGN,DOOR_OPEN,IGN,
	POWER_ON,IGN,IGN,IGN.IGN,
	IGN,IGN,POWER_OFF,IGN,IGN };

const action microwave_action_table[NUM_OF_UWAVE_STATES] = 
{
	&door_action, &power_action, &switch_1_action, &switch_2_action
};	 

U8 current_state = 0;

void microwave_event_handler(U8 event)
{
	U8 next_state;
	next_state = microwave_next_state_table[current_state][event];
	if(next_state == IGN)
	{
		
		//ignore
	}
	else
	{
		current_state = next_state;
		(microwave_action_table[current_state]());
	}
			
}

/* Check sensors*/
void check

