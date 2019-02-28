/******************************************************************************

 Copyright (c) 2015, Focusrite Audio Engineering Ltd.
 All rights reserved.

 Copywrite (c) 2018 Fenix Song version: OpenLaunch

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 * Neither the name of Focusrite Audio Engineering Ltd., nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 *****************************************************************************/

//______________________________________________________________________________
//
// Headers
//______________________________________________________________________________

#include "app.h"
#include "environment/state.h"
#include "environment/timer.h"
#include "environment/surface.h"
#include "molecules/event.h"
#include "organisms/states/setup.h"
#include "atoms/function/mode_func.h"

//______________________________________________________________________________
//
// This is where the fun is!  Add your code to the callbacks below to define how
// your app behaves.
//
// In this example, we either render the raw ADC data as LED rainbows or store
// and recall the pad state from flash.
//______________________________________________________________________________

// store ADC frame pointer
//static const u16 *g_ADC = 0;

// buffer to store pad states for flash save


//u8 g_Buttons[BUTTON_COUNT] = {0};
u8 memory_store[30] = { 0,0,0,0,0,5,5,0,0,0,
                        0,1,2,3,4,5,6,7,8,9,
                        10,11,12,13,14,15,0,0,0,0,
                        };

u8 aft_cc_ones = 1;
u8 aft_cc_tens = 0;
u8 aft_cc_hundreds = 0;
/* 30 u8 slots to store only the important settings for recall of the last state of the OpenLaunch
0 = last state/mode
1 = Key
2 = Scale
3 = Offset Mode
4 = Scale Mode On/Off
5 = Octave 1....don't write to this all the time
6 = Octave 2....don't write to this all the time
7 = Velocity Curve
8 = Aftertouch (0 off, 1 channel, 2 poly, 100+ map to CC by subtract 100= CC#)
9 = last sub-mode
10 - 25 "Virtual Instrument" slots 1 thru 16 to assign midi channels
*/

//______________________________________________________________________________

void app_surface_event(u8 type, u8 index, u8 value)
{
    switch (type)
    {
        case  TYPEPAD:
        {
            //if ( value > 0 ) {
            (*stateMachine)(EVENT_INPUT, index, value);
            //}
            // toggle it and store it off, so we can save to flash if we want to
            // if (value)
            // {
            //     g_Buttons[index] = MAXLED * !g_Buttons[index];
            // }

            // example - light / extinguish pad LEDs
            //hal_plot_led(TYPEPAD, index, 0, 0, g_Buttons[index]);

            // example - send MIDI
            //hal_send_midi(DINMIDI, NOTEON | 0, index, value);

        }
        break;

        case TYPESETUP:
        {
            if (value)
            {
                // sample code: save button states to flash (reload them by power cycling the hardware!)
                //hal_write_flash(0, g_Buttons, BUTTON_COUNT);
                //hal_write_flash(0, memory_store, 20); // maybe smarter place to put this

                //TEMP... make better for toggle back to last state
                transition_state( state_setup );
            }
        }
        break;
    }
}

//______________________________________________________________________________

void app_midi_event(u8 port, u8 status, u8 d1, u8 d2)
{
    // example - MIDI interface functionality for USB "MIDI" port -> DIN port
    if (port == USBMIDI)
    {
        hal_send_midi(DINMIDI, status, d1, d2);
    }

    // // example -MIDI interface functionality for DIN -> USB "MIDI" port port
    if (port == DINMIDI)
    {
        hal_send_midi(USBMIDI, status, d1, d2);
    }
}

//______________________________________________________________________________

void app_sysex_event(u8 port, u8 * data, u16 count)
{
    // example - respond to UDI messages?
    event_sysex(port, count);  // ? how to deal with * data ? get it later
}

//______________________________________________________________________________

void app_aftertouch_event(u8 index, u8 value)
{
    event_aftertouch(index, value);
}

//______________________________________________________________________________

void app_cable_event(u8 type, u8 value)
{
    // example - light the Setup LED to indicate cable connections
    if (type == MIDI_IN_CABLE)
    {
        hal_plot_led(TYPESETUP, 0, 0, value, 0); // green
    }
    else if (type == MIDI_OUT_CABLE)
    {
        hal_plot_led(TYPESETUP, 0, value, 0, 0); // red
    }
}

//______________________________________________________________________________

void app_timer_event()
{
    core_clock();
}

//______________________________________________________________________________

void app_init(const u16 *adc_raw)
{
    memory_store[MEM_OCTAVE1] = 5;
    memory_store[MEM_OCTAVE2] = 5; // default octaves

    // load in the stored memory
    hal_read_flash(0, memory_store, 30);

    prep_surface();

    // load the memory_store into the appropriate variables
    // TODO... with enum making it clearer, these variables could go away I think
    current_state = memory_store[MEM_LAST_MODE];
    keyscale = memory_store[MEM_KEY];
    modal = memory_store[MEM_SCALE];
    scaleOffset = memory_store[MEM_OFFSET_MODE];
    hideNonscale = memory_store[MEM_SCALE_MODE_ACTIVE];
    velocityCurve = memory_store[MEM_VELOCITY];

    aft_cc_ones = memory_store[MEM_AFTERTOUCH] % 10;
    aft_cc_tens = (memory_store[MEM_AFTERTOUCH] % 100) / 10;
    aft_cc_hundreds = memory_store[MEM_AFTERTOUCH] / 100;

    ModeFunc(memory_store[MEM_LAST_MODE], 0, 0);

}
