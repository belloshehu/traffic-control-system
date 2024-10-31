#include "TrafficLane.h"
#include <TM1637Display.h>

TrafficLane::TrafficLane(byte redLEDPin, byte greenLEDPin, byte orangeLEDPin,
  byte inSensorPin, byte outSensorPin, String state){
  this->redLEDPin = redLEDPin;
  this->greenLEDPin = greenLEDPin;
  this->orangeLEDPin = orangeLEDPin;
  this->inSensorPin = inSensorPin;
  this->outSensorPin = outSensorPin;
  this->state = state;
}

void TrafficLane::blinkLEDs(unsigned long offDelay, unsigned long onDelay, byte count){
  for(byte index = 0; index < count; index++){
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(orangeLEDPin, HIGH);
    digitalWrite(greenLEDPin, HIGH);
    delay(onDelay);
    digitalWrite(redLEDPin, LOW);
    digitalWrite(orangeLEDPin, LOW);
    digitalWrite(greenLEDPin, LOW);
    delay(offDelay);
  }
}

void TrafficLane::testSensors(){
  if(this->getInSensorState()){
    digitalWrite(this->redLEDPin, HIGH);
  }
  if(this->getOutSensorState()){
    digitalWrite(this->greenLEDPin, HIGH);
  }
  delay(100);
  digitalWrite(this->redLEDPin, LOW);
  digitalWrite(this->greenLEDPin, LOW);   
}

void TrafficLane::configurePins(){
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(orangeLEDPin, OUTPUT);
  pinMode(inSensorPin, INPUT);
  pinMode(outSensorPin, INPUT);
}

void TrafficLane::updateDelayCount(){
  if(this->delayCount > 0 && this->state == "go"){
      this->delayCount -= 1;
  }
}

uint16_t TrafficLane:: getDelayCount(){
  return this->delayCount;
}

uint16_t TrafficLane:: getVehicleCount(){
  return this->vehicleCount;
  }

uint16_t TrafficLane:: incrementVehicleCount(){
    if(this->inSensorState == true){
     this->vehicleCount+=1;
    }
    return this->vehicleCount;
}

uint16_t TrafficLane:: decrementVehicleCount(){
    if(this->outSensorState == true){
     this->vehicleCount-=1;
    }
    return this->vehicleCount;
}

bool TrafficLane:: setOutSensorState(){
  if(this->outSensorState == false && readOutSensor() == HIGH){
    this->outSensorState = true;
    incrementVehicleCount();
  }
  if(readOutSensor() == LOW){
    this->outSensorState = false;
  }
  return this->outSensorState;
}

bool TrafficLane:: setInSensorState(){
  if(this->inSensorState == false && readInSensor() == HIGH){
    this->inSensorState = true;
    incrementVehicleCount();
  }
  if(readInSensor() == LOW){
    this->inSensorState = false;
  }
  return this->inSensorState;
}

bool TrafficLane:: getOutSensorState(){
  return this->outSensorState;
}

bool TrafficLane:: getInSensorState(){
  return this->inSensorState;
}

int TrafficLane:: readOutSensor(){
  return digitalRead(this->outSensorPin);
}

int TrafficLane:: readInSensor(){
  return digitalRead(this->inSensorPin);
}


void TrafficLane:: resetVehicleCount(){
  this->vehicleCount = 0;
}

String TrafficLane:: getState(){
  return this->state;
}

void TrafficLane:: setState(String state){ // state: "go",  "read", "ready"
  if(state == "go"){
    digitalWrite(this->greenLEDPin, HIGH);
    digitalWrite(this->redLEDPin, LOW);
    digitalWrite(this->orangeLEDPin, LOW);
  }
  else if(state == "wait"){
    digitalWrite(this->redLEDPin, HIGH);
    digitalWrite(this->greenLEDPin, LOW);
    digitalWrite(this->orangeLEDPin, LOW);
  }else{
    digitalWrite(this->orangeLEDPin, HIGH);
    digitalWrite(this->redLEDPin, LOW);
    digitalWrite(this->greenLEDPin, LOW);
  }
  return this->state = state;
}

void TrafficLane::countVehicles(){
  setOutSensorState();
  setInSensorState();
}

void TrafficLane::turnOnLED(){
  if(this->state == "go"){
     digitalWrite(this->greenLEDPin, HIGH);
  }
  else if(this->state == "wait"){
    digitalWrite(this->redLEDPin, HIGH);
  }else{
    digitalWrite(this->orangeLEDPin, HIGH);
  }
}

void TrafficLane::turnOffLED(){
  if(this->state == "go"){
     digitalWrite(this->greenLEDPin, LOW);
  }
  else if(this->state == "wait"){
    digitalWrite(this->redLEDPin, LOW);
  }else{
    digitalWrite(this->orangeLEDPin, LOW);
  }
}

