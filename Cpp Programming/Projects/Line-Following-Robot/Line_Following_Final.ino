// Include necessary libraries
#include <Arduino.h>

// Define pin numbers for TCRT5000 sensors
const int tcrtPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};

// Define motor control pins
const int leftMotorPWM = 9;   // PWM pin for speed control
const int leftMotorDir1 = 7;  // Digital pin for direction control 1
const int leftMotorDir2 = 8;  // Digital pin for direction control 2

const int rightMotorPWM = 10;  // PWM pin for speed control
const int rightMotorDir1 = 12; // Digital pin for direction control 1
const int rightMotorDir2 = 11; // Digital pin for direction control 2

//Define temp_array
int temparray[] = {0,0,0,0,0,0,0,0};

// Define constants for PID control
const float Kp = 1;  // Proportional gain
const float Ki = 0.1;  // Integral gain
const float Kd = 0.5;  // Derivative gain

// Define variables for PID control
float lastError = 0;
float integral = 0;

// Function to initialize pins and motors
void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize TCRT5000 sensor pins
  for (int i = 0; i < 8; i++) {
    pinMode(tcrtPins[i], INPUT); 
  }

  // Initialize motor control pins
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(leftMotorDir1, OUTPUT);
  pinMode(leftMotorDir2, OUTPUT);

  pinMode(rightMotorPWM, OUTPUT);
  pinMode(rightMotorDir1, OUTPUT);
  pinMode(rightMotorDir2, OUTPUT);
}

// Function to read sensor values
void readSensors(int sensorValues[],int pureAnalogSensorReadings[]) {
  for (int i = 0; i < 8; i++) {
    pureAnalogSensorReadings[i] = analogRead(tcrtPins[i]);
    if(pureAnalogSensorReadings[i]>150){
      sensorValues[i] = 1;
    }
    else{
      sensorValues[i] = 0;
    }
  }
}

//Function to turn 90 degrees
void turn90degright(sensorValues[3],sensorValues[4]){
  int leftSpeed=0;
  int rightSpeed=0;
 // delay(500);

  while (sensorValues[3]!=1 && sensorValues[4]!=1){
  int leftSpeed = +60 ;
  int rightSpeed = -60 ;
  //delay(500);
  }
  else {
  int leftSpeed=90;
  int rightSpeed=90;   
  }
}

void turn90degleft(sensorValues[3],sensorValues[4]){
  int leftSpeed=0;
  int rightSpeed=0;
 // delay(500);

  while (sensorValues[3]!=1 && sensorValues[4]!=1){
  int leftSpeed = -60;
  int rightSpeed = +60;
  else {
  int leftSpeed=90;
  int rightSpeed=90;   
  }
 // delay(500);
  }
}

// Function to calculate PID control
int pidControl(int sensorValues[]) {
  // Calculate error
  float error = 0;
  error = (-40) * sensorValues[0] + (-30) * sensorValues[1] + (-20) * sensorValues[2] + (0) * sensorValues[3] + (0) * sensorValues[4] + (+20) * sensorValues[5] + (+30) * sensorValues[6] + (+40) * sensorValues[7];
  
  // Calculate integral
  integral += error;

  // Calculate derivative
  float derivative = error - lastError;

  // Calculate PID control
  float pidOutput = Kp * error + Kd * derivative;
  //float pidOutput = Kp * error + Ki * integral + Kd * derivative;

  // Update last error
  lastError = error;

  return pidOutput;
}

// Function to control motors based on PID output
void controlMotors(int pidOutput) {
  int scaledPidOut = 4 * pidOutput;
  // Set motor speeds based on PID output
  int leftSpeed = 90 - scaledPidOut;
  int rightSpeed = 90 + scaledPidOut;

  // Clip motor speeds to valid range (0-255)
  leftSpeed = constrain(leftSpeed, 0, 180);
  rightSpeed = constrain(rightSpeed, 0, 180);

  // Control motor direction
  digitalWrite(leftMotorDir1, HIGH);
  digitalWrite(leftMotorDir2, LOW);
  
  digitalWrite(rightMotorDir1, HIGH);
  digitalWrite(rightMotorDir2, LOW);

  // Control motors
  Serial.println(leftSpeed);
  Serial.println(rightSpeed);
  analogWrite(leftMotorPWM, leftSpeed);
  analogWrite(rightMotorPWM, rightSpeed);
}

// Main loop
void loop() {
  // Array to store sensor values
  int sensorValues[8];
  int pureAnalogSensorReadings[8];

  // Read sensor values
  readSensors(sensorValues,pureAnalogSensorReadings);

  bool areArraysEqual = true;

  for (int i = 0; i < 8; i++) {
    if (sensorValues[i] != 0) {
        areArraysEqual = false;
        break;  // No need to continue checking if a non-zero value is found
    }
  }
    if (areArraysEqual) {
    // The arrays are equal to {0, 0, 0, 0, 0, 0, 0, 0}
    if (temparray[0] == 1 && temparray[1] == 1) {
      turn90degright();
  }
    
    if (temparray[6] == 1 && temparray[7] == 1) {
     turn90degleft();
  }
}
         
  // Calculate PID control
  int pidOutput = pidControl(sensorValues);
  // Control motors based on PID output
  controlMotors(pidOutput);

  // Print sensor values and PID output (for debugging)
  Serial.print("Sensor Values: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(sensorValues[i]);
    Serial.print(" ");
    Serial.print(pureAnalogSensorReadings[i]);
    Serial.print(" ");
  }
  Serial.print("PID Output: ");
  Serial.println(pidOutput);

  // Delay to control the loop frequency
  delay(10);
  for (int i = 0; i < 8; i++) {
    temparray[i] = sensorValues[i];
}
  
}
