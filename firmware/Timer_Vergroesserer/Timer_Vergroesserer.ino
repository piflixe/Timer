/* 
 *  
 *  This is Arduino Code for a Timer module with 7segment
 *  display and encoder knob
 *  
 *  Author: Felix Piela
 *  Date: Feb 2018
 *  LICENSE: GPL
 *  
 *  it was developed to run on a teensy LC
 *  https://www.pjrc.com/teensy/teensyLC.html
 *  but it might run on other arduino / teensy boards as well
 *  
 *  As Display, a 7 segment 8 digit display is used
 *  Include the HCMAX7219 and SPI library 
 * http://blog.hobbycomponents.com/?p=325
 * https://github.com/HobbyComponents/HCMAX7219/blob/master/Examples/HCMODU0082_Serial_7_Segment_Module_Example1/HCMODU0082_Serial_7_Segment_Module_Example1.ino
 * Since the display has 8 digits, two different countdowns can be used. 
 * This can be practical when processing test-stripes while storing the total time on the other timer
 * 
 * for the rotary encoder knob, the ClickEncoder library is used
 * it can be downloaded / cloned from
 * https://github.com/0xPIT/encoder
 * also needs to be included in the arduino library folder
 * 
 * USAGE
 * ==========
 * Turn knob: set time for countdown
 * press button: start / stop  countdown
 * double-press button: set relay always on
 * long-press button: switch between two countdowns
*/

// libraries for display
#include <HCMAX7219.h>
#include "SPI.h"

// libraries for button
#include <ClickEncoder.h>
#include <TimerOne.h>

// #define ENC_DECODER (1 << 2)
// #define ENC_HALFSTEP 1


/* Set the LOAD (CS) digital pin number*/
const int PIN_CS = 14;

// Pin to which the indicator LED is connected
const int PIN_INDICATOR = 15;
/* 
 *  other PINs:
 *  [LED Module] - [Teensy]
 *  DIN          - Pin 11 (MOSI0)
 *  CLK          - Pin 13 (SCK0)
 */

// Pin for Relay
const int PIN_RELAY = 9;

ClickEncoder *encoder;
int16_t last, value;
void timerIsr() {
  encoder->service();
}

HCMAX7219 HCMAX7219(PIN_CS);

IntervalTimer countEvent;

// declare and init variables
boolean LR = 1; // left or right display
boolean runCountdown = false; // running or pausing
boolean alwaysOn = false; // stat to have lamp always on (for setup)
volatile int currentTime0 = 0; // time while running 
int totalTime0 = 0;
volatile int currentTime1 = 0; // time while running 
int totalTime1 = 0;
long lastSwitch = 0; // for software debouncing in addition to Click Encoder library

void setup() 
{  
  // initialise encoder      
  encoder = new ClickEncoder(18, 19, 20, 2, LOW);
  encoder->setAccelerationEnabled(false);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  last = -1;

  // initialise ISR for countdown to run every 0,1 sec
  countEvent.begin(countdown, 100000); 
  
  pinMode(PIN_RELAY,OUTPUT);
  pinMode(PIN_INDICATOR,OUTPUT);
  digitalWrite(PIN_INDICATOR,LOW); // turn indicator LED off on startup
  digitalWrite(PIN_RELAY,HIGH); // SolidState Relay uses negative logic!

  //Serial.begin(9600); // for debugging only
}

/* Main program */
void loop() 
{
  // write encoder input on total time
  if(LR == 1){
    totalTime1 += encoder->getValue();
    if (totalTime1 != last) {
      last = totalTime1;
    }
    if(totalTime1 <= 0){
      totalTime1 = 0;    
    }
  }
  else{
    totalTime0 += encoder->getValue();
    if (totalTime0 != last) {
      last = totalTime0;
    } 
    if( totalTime0 <= 0 ) {
      totalTime0 = 0;
    }
  }

  // check for button
  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    switch (b) {
      case ClickEncoder::Pressed:
        break;
      case ClickEncoder::Held: // switch to other timer
        if(millis() - lastSwitch > 3000) { // additional software debouncding seemed necessary
          lastSwitch = millis();
          LR = !LR;
          print7seg(8888,8888);
          delay(300);
          print7seg(totalTime1,totalTime0);
        }
        break;
      case ClickEncoder::Released:
        break;
      case ClickEncoder::Clicked: // start / stop timer on click
        if(runCountdown == false && alwaysOn == false) {
          if(LR == 1){
            currentTime1 = totalTime1;
          }
          else{
            currentTime0 = totalTime0;
          }
          runCountdown = true;
        }
        else{
          runCountdown = false;  
        }
        
        if(alwaysOn == true) { // turn relay off if it was on
          alwaysOn = false;
          digitalWrite(PIN_RELAY,HIGH); // turn lamp OFF
          digitalWrite(PIN_INDICATOR,LOW); // turn indicator LED off
        }
        break;
      case ClickEncoder::DoubleClicked: // turn relay on
        alwaysOn = !alwaysOn; // toggle state
        if(alwaysOn == true){
          digitalWrite(PIN_RELAY,LOW); // turn lamp on
          digitalWrite(PIN_INDICATOR,HIGH); // turn indicator LED on
        }
        else {
          digitalWrite(PIN_RELAY,HIGH); // turn lamp off
          digitalWrite(PIN_INDICATOR,LOW); // turn indicator LED off
        }  
        break;
      case ClickEncoder::Closed:
        break;
      default: // nothing
        break;
    }
  } 

  // update display
  if(runCountdown == false){
    print7seg(totalTime1,totalTime0);
  }
  else {
    if(LR == 1){
      print7seg(currentTime1,totalTime0);
    }
    else{
      print7seg(totalTime1,currentTime0);
    }
  }
}
