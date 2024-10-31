#include "TrafficLane.h"
#include <TM1637Display.h>

// LED pins with 20 as value are not actually connected to any microcontroller pin directly. Hence, the numbering is selected arbitrarily to avoid error.

// North lane:
#define northRedLEDPin 13
#define northGreenLEDPin 10
#define northOrangeLEDPin 9
#define northInSensorPin 7
#define northOutSensorPin 6
// #define northCLKPin 21
// #define northDIO 20

//TM1637Display northDisplay(northCLKPin, northDIO);
TrafficLane northLane(northRedLEDPin, northGreenLEDPin, northOrangeLEDPin, northInSensorPin, northOutSensorPin, "go");

// South lane:
#define southRedLEDPin 12
#define southGreenLEDPin 14 // A0
#define southOrangeLEDPin 15 // A1
#define southInSensorPin 5
#define southOutSensorPin 4
// #define southCLKPin 19 
// #define southDIO 18
//TM1637Display southDisplay(southCLKPin, southDIO);
TrafficLane southLane(southRedLEDPin, southGreenLEDPin, southOrangeLEDPin, southInSensorPin, southOutSensorPin, "ready");

// West lane:
#define westRedLEDPin 16 // A2
#define westGreenLEDPin 17 // A3
#define westOrangeLEDPin 18 // A4
#define westInSensorPin 3
#define westOutSensorPin 2
// #define westCLKPin 15 
// #define westDIO 14
//TM1637Display westDisplay(westCLKPin, westDIO);
TrafficLane westLane(westRedLEDPin, westGreenLEDPin, westOrangeLEDPin, westInSensorPin, westOutSensorPin, "stop");

// East lane:
#define eastRedLEDPin 19 // A5
#define eastGreenLEDPin 20 // A6
#define eastOrangeLEDPin 21 // A7
#define eastInSensorPin 1
#define eastOutSensorPin 0
// #define eastCLKPin 16 
// #define eastDIO 17
TrafficLane eastLane(eastRedLEDPin, eastGreenLEDPin, eastOrangeLEDPin, eastInSensorPin, eastOutSensorPin, "stop");

unsigned long timeDelay = 1000; // time for updating the counter
unsigned long lastTime, blinkLastTime = 0;

byte laneIndex = 0; //  
TrafficLane lanes[4] = {eastLane, southLane, westLane, northLane};
unsigned long waitCount = 10; // min seconds

void setup() {
  // put your setup code here, to run once:
  eastLane.configurePins();
  northLane.configurePins();
  westLane.configurePins();
  southLane.configurePins();

  // blink all LEDs
  eastLane.blinkLEDs(100, 100, 2);
  northLane.blinkLEDs(100, 100, 2);
  southLane.blinkLEDs(100, 100, 2);
  westLane.blinkLEDs(100, 100, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  process();
  test();
}

void test(){
  northLane.testSensors();
  southLane.testSensors();
  westLane.testSensors();
  eastLane.testSensors();
}

void process(){
  if(millis() - lastTime < waitCount * lanes[laneIndex].getVehicleCount()){
    lanes[laneIndex].setState("go");
    for(byte index = 0; index < 4; index++){ // set next lane to "ready" state and all other two to "wait"
      if(index != laneIndex){
        if(laneIndex < 3 ){
          lanes[laneIndex + 1].setState("ready");
        }else{
          lanes[laneIndex].setState("wait");
        }
      }
    }
  }else{
    if(laneIndex >= 4){
      laneIndex = 0;
    }else{
      laneIndex +=1;
    }
    lastTime = millis();
  }

  northLane.countVehicles();
  southLane.countVehicles();
  westLane.countVehicles();
  eastLane.countVehicles();

  if(millis() - blinkLastTime >= timeDelay){
    // descrement 7 segments accordingly for lane that is in "go" state
    // northLane.updateDelayCount();
    // southLane.updateDelayCount();
    // westLane.updateDelayCount();
    // eastLane.updateDelayCount();
    lanes[laneIndex].turnOnLED();
    blinkLastTime = millis();
  }else{
    lanes[laneIndex].turnOffLED();
  }
}
