#include "arduino.h"
#include <TM1637Display.h>

#ifndef TRAFFICLANE_H
#define TRAFFICLANE_H


class TrafficLane{
  private:
    uint16_t count; 
    String state;
    TM1637Display *sevenSegmentDisplay; // 7 segment module: TM1637 
    byte redLEDPin; // distilling temperature lower limit  
    byte greenLEDPin; // distilling temperature upper limit  
    byte orangeLEDPin; 
    byte pinSensor; // IR sensor for vehicle detection

  
  public:
   TrafficLane::TrafficLane( 
      byte redLEDPin, 
      byte greenLEDPin,
      byte orangeLEDPin,
      TM1637Display &sevenSegmentDisplay, 
      byte sensorPin;
      String state;
     );
     
    void configurePins();
    uint16_t getVehicleCount();
    uint16_t incrementVehicleCount();
    void resetVehicleCount();
    void setState(String state); // set state of a traffic lane: State could be "wait", "go" or "ready" 
    String getState();
  };

  
 #endif