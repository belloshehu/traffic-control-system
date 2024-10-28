#include "TrafficLane.h"

// North lane:
#define northRedLEDPin 0
#define northGreenLEDPin 0
#define northOrangeLEDPin 0
#define northSensorPin 0
#define northCLKPin 0 
#define northDIO 0
TrafficLane northLane(northCLKPin, northDIO);
TM1637Display 7_segment(northRedLEDPin, northGreenLEDPin, northOrangeLEDPin, northLane, northSensorPin, 'go');

// South lane:
#define southRedLEDPin 0
#define southGreenLEDPin 0
#define southOrangeLEDPin 0
#define southSensorPin 0
#define southCLKPin 0 
#define southDIO 0
TrafficLane southLane(southCLKPin, southDIO);
TM1637Display 7_segment(southRedLEDPin, southGreenLEDPin, southOrangeLEDPin, southLane, southSensorPin, "ready");

// West lane:
#define westRedLEDPin 0
#define westGreenLEDPin 0
#define westOrangeLEDPin 0
#define westSensorPin 0
#define westCLKPin 0 
#define westDIO 0
TrafficLane westLane(westCLKPin, westDIO);
TM1637Display 7_segment(westRedLEDPin, westGreenLEDPin, westOrangeLEDPin, westLane, westSensorPin, "stop");

// East lane:
#define eastRedLEDPin 0
#define eastGreenLEDPin 0
#define eastOrangeLEDPin 0
#define eastSensorPin 0
#define eastCLKPin 0 
#define eastDIO 0
TrafficLane eastLane(eastCLKPin, eastDIO);
TM1637Display 7_segment(eastRedLEDPin, eastGreenLEDPin, eastOrangeLEDPin, eastLane, eastSensorPin, "stop");

unsigned long timeDelay = 0;

void setup() {
  // put your setup code here, to run once:
  eastLane.configurePins();
  northLane.configurePins();
  westLane.configurePins();
  southLane.configurePins();
}

void loop() {
  // put your main code here, to run repeatedly:
  

}

void process(){
  if(northLane.){}
}