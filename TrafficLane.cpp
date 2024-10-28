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
  pinMode(orangeLEDPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  }

void TrafficLane::updateDelayCount(){
  if(this->delayCount > 0 && this->state == "go"){
      this->delayCount -= 1;
      this->sevenSegmentDisplay->showNumberDec(this->delayCount);
  }
}

uint16_t TrafficLane:: getDelayCount(){
  return this->delayCount;
}

uint16_t TrafficLane:: getVehicleCount(){
  return this->vehicleCount;
  }

uint16_t TrafficLane:: incrementVehicleCount(){
    if(this->sensorState == true){
     this->vehicleCount+=1;
    }
    return this->vehicleCount;
  }

bool TrafficLane:: setSensorState(){
  if(this->sensorState == false && readSensor() == HIGH){
    this->sensorState = true;
    incrementVehicleCount();
  }
  if(readSensor() == LOW){
    this->sensorState = false;
  }
  return this->sensorState;
}

bool TrafficLane:: getSensorState(){
  return this->sensorState;
}

int TrafficLane:: readSensor(){
  return digitalRead(this->sensorPin);
}

void TrafficLane:: resetVehicleCount(){
  this->vehicleCount = 0;
}

String TrafficLane:: getState(){
  return this->state;
}

void TrafficLane:: setState(String state){
  return this->state = state;
}
  
