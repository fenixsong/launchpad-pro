#ifndef state_h
#define state_h

#include "app.h"

//The concept of the whole app is simpler and yet more direct and adaptive:
/*
There is now an improved master state of the app: A State Machine, fully plumbed,
Also key to this program:
An Array of 100 (?98?) Pointers to Functions & An Array of 100 (98?) Colors !!! YES!! Clean! Perfection!
(surface.c)

Separate States may become less important (still important!) as Every State will be the same type of thing
...basically an open area where all the functions are available
Some actions may change just 1 rowset or areaset instead of the whole Page

Before building it as the music system it will be, build it as a game where Pads do functions on Press:
1. Change the Pad
2. Change other Pad(s).. possibly sets of row, column, all, random, one, (above, below, right, left IF exists logic)
3. Trigger Animation of Pads (be able to set tempo or at least have default BPM so animation runs based on tempo) (how to run it on it's own without needing a thread?? Callback on timer function~~~)
4. Change state

Maybe tie color to the type of function it performs

Next tie a music function to these actions.

Then build out real system.
*/

/// Enum representing the different program states.
typedef enum
{
    LP_PLAY_STATE,
    LP_OFF_STATE,
    LP_OVERLAY_STATE,
    LP_SETUP_STATE,
    LP_SCALEARP_STATE,
    LP_MASTERCONTROL_STATE,
    LP_CIRCUITPAD_STATE,
    LP_KEYSCALE_STATE,
    LP_DIGITONEPAD_STATE,
    LP_NUM_STATES
} LpState;

typedef enum
{
    EVENT_ENTER,
    EVENT_EXIT,
    EVENT_INPUT,
    EVENT_CLOCK,
    EVENT_PRESSURE,
    EVENT_REDRAW,
    EVENT_MSG_COUNT
} StateEvent;

//state machines (some sample ones)
void state_play(StateEvent msg, u8 index, u8 value);
void state_off(StateEvent msg, u8 index, u8 value);
void state_overlay(StateEvent msg, u8 index, u8 value);
void state_transit(StateEvent msg, u8 index, u8 value);

// main switch function to Transition state
void StateFunc(LpState setting, u8 index, u8 value);

// State External Pointer Funtions
void StatePlay(u8 index, u8 value);
void StateOff(u8 index, u8 value);
void StateScaleArp(u8 index, u8 value);
void StateMastercontrol(u8 index, u8 value);
void StateCircuitpad(u8 index, u8 value);
void StateKeyscale(u8 index, u8 value);
void StateDigitonepad(u8 index, u8 value);

extern LpState current_state; // What State the program is in (the one not saved to memory but often the same as that)

extern void (*stateMachine)(StateEvent, u8, u8);

extern u8 tempCount;

// quite a useful method. We pass in the function (pointer) for State Change, then tell it a state to change to
// I think we will also add substate to tell it what Instrument to change to but maybe the function will say
void transition_state(void (*funcIn)(StateEvent, u8, u8));

#endif /* state_h */
