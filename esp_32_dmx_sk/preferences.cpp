#ifndef PRE_CPP
#define PRE_CPP 1

// SECTION SETUP
// Default DMX Address of the first channel (1 indexed) (If you want to change the Address)
#define DMX_START_ADDRESS 1
// Allow to change the Address? 1 Allows changing via a DMX procedure, 2 Allows changing it using two buttons, 3 Allows changing it using a DIP Switch Array (see Manual for both Options)
#define USE_INFIELD_ADDRESSING 1
// How many LEDs does the strip have in total?
#define LED_COUNT 324
// On which Pin should the strip data be outputted?
#define LED_PIN 4
// The DMX Serial Input Pin is pin 16 (to change use another UART2 RX enabled pin and edit dmx.cpp:3

// How large should the Deadzone on the Time-Slider be? 5 seems to be a good start...
#define T_DEADZONE_SIZE (10 / 2)

// SECTION SHAPE
// Assumes the Start is somewhere on the left side of the lower arm going counter-clockwise around the cross (from the front)
// LED count along the left and right side of the lower arm / stand
#define SHds 73
// LED count along the top and bottom of the left arm
#define SHls 25
// LED count along the left and right side of the top arm
#define SHts 25
// LED count along the top and bottom of the right arm
#define SHrs 25
// LED count along the outer sides of the arms
#define SHos  7
// LED offset of the start of the strip from the left/lower arm corner in counter-clockwise direction
#define SH_off 17

// SECTION ADVANCED
// Set the polltime (how long to wait between DMX-reception tries, in ms)
#define POLLRATE 30
// Set the updatetime (how long to wait between refreshes of the LED_strip data, in ms)
#define UPDATETIME 10
// SKIP todo set multiplier only
#define T_MAX (LED_COUNT * 64)
// SKIP How many color slot do you want to support? todo support anything aside from 4
#define COLOR_SLOT_COUNT 4

// SKIP Debug mode?
#define DEBUG 1

#endif
