#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);
Adafruit_DCMotor *mine_motor = AFMS.getMotor(3);
int right_motor_speed = 144;
int left_motor_speed = 150;
int turn_90 = 2156;
int moving_time = 2000;

// defines pins numbers
const int trigPin = 12;
const int echoPin = 11;
// defines variables
long duration;
int count = 0;
//int array1 = [0,0,0,0,0];
int average = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  //Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();
}

void loop() {

  mine_motor->setSpeed(100);
  mine_motor->run(FORWARD);
  
  //array1[0] = array1[1];
  //array1[1] = array1[2];
  //array1[2] = array1[3];
  //array1[3] = array1[4];
  //array1[4] = distance;
  //average = array1[0]+array1[1]+array1[2]+array1[3]+array1[4];
  //average = average / 5;

  int distance = 0;
  for (int i=0; i<5; i++){
    distance = distance + getdistance(); 
    Serial.print(" sum");
    Serial.println(distance);
    delay(10);}
  average = distance / 5;

  Serial.print("--------------- Average: ");
  Serial.println(average);
  
  if (average > 10) {
  move_straight(right_motor_speed, left_motor_speed, 3000);
  }
  
  if (average < 10) {
  stop_motor();
  }
}

void stop_motor(){
  right_motor->setSpeed(0);
  left_motor->setSpeed(0);
}


void move_straight(int right_motor_speed, int left_motor_speed, int moving_time) {
  //Serial.println("Adafruit moving straight.");
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motor_speed);
  left_motor->run(FORWARD);
  right_motor->run(BACKWARD);
}


void turn(int right_motor_speed, int left_motor_speed, int angle) {
  //Serial.println("Adafruit turn " + String(angle) + "angle!");
  right_motor->setSpeed(right_motor_speed);
  left_motor->setSpeed(left_motor_speed);
  if (angle < 0) {
      right_motor->run(BACKWARD);
      left_motor->run(BACKWARD);
      angle = -angle;
    }
  else{
      right_motor->run(FORWARD);
      left_motor->run(FORWARD);
    }
  moving_time = angle * ((turn_90) / 90);
  //Serial.println(String(moving_time));
}

int getdistance(){
  int distance1;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance1= duration*0.034/2;
  // Prints the distance on the Serial Monitor
//  
  Serial.print("Distance: ");
  Serial.println(distance1);
  
  return distance1;
}