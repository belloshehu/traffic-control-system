#include "TrafficLane.h"

// North lane:
#define northRedLEDPin 0
#define northGreenLEDPin 0
#define northOrangeLEDPin 0
#define northSensorPin 0
#define northCLKPin 0 
#define northDIO 0

TM1637Display northDisplay(northCLKPin, northDIO);
TrafficLane northLane(northRedLEDPin, northGreenLEDPin, northOrangeLEDPin, northDisplay, northSensorPin, "go");

// South lane:
#define southRedLEDPin 0
#define southGreenLEDPin 0
#define southOrangeLEDPin 0
#define southSensorPin 0
#define southCLKPin 0 
#define southDIO 0
TM1637Display southDisplay(southCLKPin, southDIO);
TrafficLane southLane(southRedLEDPin, southGreenLEDPin, southOrangeLEDPin, southDisplay, southSensorPin, "ready");

// West lane:
#define westRedLEDPin 0
#define westGreenLEDPin 0
#define westOrangeLEDPin 0
#define westSensorPin 0
#define westCLKPin 0 
#define westDIO 0
TM1637Display westDisplay(westCLKPin, westDIO);
TrafficLane westLane(westRedLEDPin, westGreenLEDPin, westOrangeLEDPin, westDisplay, westSensorPin, "stop");

// East lane:
#define eastRedLEDPin 0
#define eastGreenLEDPin 0
#define eastOrangeLEDPin 0
#define eastSensorPin 0
#define eastCLKPin 0 
#define eastDIO 0
TM1637Display eastDisplay(eastCLKPin, eastDIO);
TrafficLane eastLane(eastRedLEDPin, eastGreenLEDPin, eastOrangeLEDPin, eastDisplay, eastSensorPin, "stop");

unsigned long timeDelay = 1000; // time for updating the counter
unsigned long lastTime = 0;

void setup() {
  // put your setup code here, to run once:
  eastLane.configurePins();
  northLane.configurePins();
  westLane.configurePins();
  southLane.configurePins();
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