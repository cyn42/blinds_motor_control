#include <Arduino.h>


/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>


const int stepsPerRevolution =2038;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(stepsPerRevolution, 9,10,11,12);
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int windowHeightSteps = 8000;
int currentHeight = 0;

int incomingByte;
int openLED = 4;
int closeLED = 5;
int stopLED = 6;

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(10);
  // initialize the serial port:
  Serial.begin(9600);

  pinMode(openLED, OUTPUT);
  pinMode(closeLED, OUTPUT);
  pinMode(stopLED, OUTPUT);

  digitalWrite(openLED, HIGH);
  delay(500);
  digitalWrite(openLED, LOW);
  digitalWrite(closeLED, HIGH);
  delay(500);
  digitalWrite(closeLED, LOW);
  digitalWrite(stopLED, HIGH);
  delay(500);
  digitalWrite(stopLED, LOW);


}

void loop() {
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();

    if (incomingByte == 'H') {
      digitalWrite(openLED, HIGH);
      digitalWrite(closeLED, LOW);
      digitalWrite(stopLED, LOW);
      open();

    } else if (incomingByte == 'L') {
      digitalWrite(openLED, LOW);
      digitalWrite(closeLED, HIGH);
      digitalWrite(stopLED, LOW);
      close();

    } else {
      digitalWrite(openLED, LOW);
      digitalWrite(closeLED, LOW);
      digitalWrite(stopLED, LOW);
    }
  }
}

void open() {
  for ( ; currentHeight <= windowHeightSteps ; currentHeight += stepsPerRevolution ) {
    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      if (incomingByte == 'S') {
        digitalWrite(openLED, LOW);
        digitalWrite(closeLED, LOW);
        digitalWrite(stopLED, HIGH);
        break;
      }
    }
    myStepper.step(stepsPerRevolution/2);
  }
}

void close() {
  for ( ; currentHeight >= 0 ; currentHeight -= stepsPerRevolution ) {
    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      if (incomingByte == 'S') {
        digitalWrite(openLED, LOW);
        digitalWrite(closeLED, LOW);
        digitalWrite(stopLED, HIGH);
        break;
      }
    }
    myStepper.step(-stepsPerRevolution/2);
  }

}
