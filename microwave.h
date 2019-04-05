#include "bb_cnt.h"
/* Logical input port for microwave sensors */
#define DOOR_SWITCH			 PTT_PTT0
#define TIMER_SWITCH_1		 PTT_PTT1
#define TIMER_SWITCH_2		 PTT_PTT2

/* Logical output port for microwave */
#define LIGHT_OUTPUT	PTS_PTS7
#define POWER_TUBE		PTS_PTS0

/* states and events for uwave*/
#define NUM_OF_UWAVE_STATES  4
#define NUM_OF_UWAVE_EVENTS	5

/*States*/
#define DOOR_CLOSED 0
#define DOOR_OPEN	1
#define POWER_OFF	2
#define POWER_ON	3

/*Events*/
#define SET_TIMER 0
#define TIMER_EXPIRE 1
#define TIMER_CLEAR 2
#define DOOR_OPENING 3
#define DOOR_CLOSING  4

/*OBJECTS*/
#define DOOR 0
#define LIGHT 1
#define SWITCH_1 2
#define SWITCH_2 3
#define POWER	4

#define IGN 250

/*microwave state and event definitions*/
void door_action(void);
void power_action(void);
void switch_1_action(void);
void switch_2_action(void);

/*Event handler*/
void microwave_event_handler(U8 event_name);
