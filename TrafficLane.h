#include "arduino.h"
#include <TM1637Display.h>

#ifndef TRAFFICLANE_H
#define TRAFFICLANE_H


class TrafficLane{
  private:
    uint16_t delayCount; 
    String state;
    byte redLEDPin; // distilling temperature lower limit  
    byte greenLEDPin; // distilling temperature upper limit  
    byte orangeLEDPin; 
    byte outSensorPin; // IR sensor for vehicle detection
    byte inSensorPin;
    bool inSensorState;
    bool outSensorState;
    uint16_t vehicleCount;
  
  public:
   TrafficLane::TrafficLane( 
      byte redLEDPin, 
      byte greenLEDPin,
      byte orangeLEDPin,
      byte outSensorPin,
      byte inSensorPin,
      String state
     );
     
    void configurePins();
    uint16_t getVehicleCount();
    uint16_t incrementVehicleCount();
    uint16_t decrementVehicleCount();
    void resetVehicleCount();
    void setState(String state); // set state of a traffic lane: State could be "wait", "go" or "ready" 
    String getState();
    int readOutSensor();
    int readInSensor();
    bool getOutSensorState();
    bool setOutSensorState();
    bool getInSensorState();
    bool setInSensorState();
    void updateDelayCount();
    uint16_t getDelayCount();
    void blinkLEDs(unsigned long offDelay, unsigned long onDelay, byte count);
    void testSensors();
    void countVehicles();
    void turnOnLED();
    void turnOffLED();
  };

  
 #endif