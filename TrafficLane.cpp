#include "TrafficLane.h"
#include <TM1637Display.h>

TrafficLane::TrafficLane(byte redLEDPin, byte greenLEDPin, byte orangeLEDPin, TM1637Display &sevenSegmentDisplay, 
  byte sensorPin, String state){
  this->redLEDPin = redLEDPin;
  this->greenLEDPin = greenLEDPin;
  this->orangeLEDPin = orangeLEDPin;
  this->sevenSegmentDisplay = &sevenSegmentDisplay;
  this->sensorPin = sensorPin;
  this->state = state;
}

void TrafficLane::configurePins(){
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(orangePin, OUTPUT);
  pinMode(sensorPin, INPUT);
  }

uint16_t TrafficLane:: getVehicleCount(){
  return this->count;
  }

uint16_t TrafficLane:: incrementVehicleCount(){
  return this->count + 1;
  }

bool TrafficLane:: readSensor(){
  return digitalRead(this->pinSensor);
}

void TrafficLane:: resetVehicleCount(){
  this->count = 0;
  }

uint16_t TrafficLane:: getState(){
  return this->state;
  }

uint16_t TrafficLane:: setState(String state){
  return this->state = state;
  }
  
