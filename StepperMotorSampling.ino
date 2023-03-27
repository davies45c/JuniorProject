#include <Stepper.h>

const int stepsPerRevolution = 2038;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

float distance;
int steps;

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  
    Serial.println("Enter Distance (in cm): ");
  while(distance == 0){
    distance = Serial.parseFloat();
  }
  steps = (distance * 2038) / (2 * 3.14159 * 0.6);

  myStepper.setSpeed(15);
  myStepper.step(steps);
  distance = 0;
  delay(1000);

}