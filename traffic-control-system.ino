#include "TrafficLane.h"
#include <TM1637Display.h>

// Serial register pins
#define latchPin = 8;      // Latch pin of 74HC595 is connected to Digital pin 5
#define clockPin = 12;      // Clock pin of 74HC595 is connected to Digital pin 6
#define dataPin 11;       // Data pin of 74HC595 is connected to Digital pin 4

// LED pins with 20 as value are not actually connected to any microcontroller pin directly. Hence, the numbering is selected arbitrarily to avoid error.

// North lane:
#define northRedLEDPin 13
#define northGreenLEDPin 10
#define northOrangeLEDPin 9
#define northSensorPin 4
#define northCLKPin 21
#define northDIO 20

TM1637Display northDisplay(northCLKPin, northDIO);
TrafficLane northLane(northRedLEDPin, northGreenLEDPin, northOrangeLEDPin, northDisplay, northSensorPin, "go");

// South lane:
#define southRedLEDPin 20
#define southGreenLEDPin 20
#define southOrangeLEDPin 200
#define southSensorPin 5
#define southCLKPin 19 
#define southDIO 18
TM1637Display southDisplay(southCLKPin, southDIO);
TrafficLane southLane(southRedLEDPin, southGreenLEDPin, southOrangeLEDPin, southDisplay, southSensorPin, "ready");

// West lane:
#define westRedLEDPin 20
#define westGreenLEDPin 20
#define westOrangeLEDPin 20
#define westSensorPin 6
#define westCLKPin 15 
#define westDIO 14
TM1637Display westDisplay(westCLKPin, westDIO);
TrafficLane westLane(westRedLEDPin, westGreenLEDPin, westOrangeLEDPin, westDisplay, westSensorPin, "stop");

// East lane:
#define eastRedLEDPin 20
#define eastGreenLEDPin 20
#define eastOrangeLEDPin 20
#define eastSensorPin 3
#define eastCLKPin 16 
#define eastDIO 17
TM1637Display eastDisplay(eastCLKPin, eastDIO);
TrafficLane eastLane(eastRedLEDPin, eastGreenLEDPin, eastOrangeLEDPin, eastDisplay, eastSensorPin, "stop");

unsigned long timeDelay = 1000; // time for updating the counter
unsigned long lastTime = 0;
byte leds = 0;
byte ledStates[] = {}

void setup() {
  // put your setup code here, to run once:
  eastLane.configurePins();
  northLane.configurePins();
  westLane.configurePins();
  southLane.configurePins();

  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  process();

}

void process(){
  northLane.setSensorState(); // read sensor and increment if a vehicle is detected in the north lane
  southLane.setSensorState(); // read sensor and increment if a vehicle is detected in the south lane
  westLane.setSensorState();  // read sensor and increment if a vehicle is detected in the west lane
  eastLane.setSensorState();  // read sensor and increment if a vehicle is detected in the east lane

  if(millis() - lastTime >= timeDelay){
    // descrement 7 segments accordingly for lane that is in "go" state
    northLane.updateDelayCount();
    southLane.updateDelayCount();
    westLane.updateDelayCount();
    eastLane.updateDelayCount();
  }
}

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}