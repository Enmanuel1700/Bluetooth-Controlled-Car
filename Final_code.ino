#include <Servo.h>

// Pin definitions for motor driver
#define Lpwm_pin  6
#define Rpwm_pin  0
int pinLB = 8;
int pinLF = 9;
int pinRB = 4;
int pinRF = 2;

// Commands from the app
#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define STOP 'X'   // Use 'X' to stop
#define START 'A'
#define PAUSE 'P'

// Motor speed
#define DEFAULT_SPEED 150

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize motor control pins
  pinMode(pinLB, OUTPUT);
  pinMode(pinLF, OUTPUT);
  pinMode(pinRB, OUTPUT);
  pinMode(pinRF, OUTPUT);
  pinMode(Lpwm_pin, OUTPUT);
  pinMode(Rpwm_pin, OUTPUT);

  // Initial setup message
  Serial.println("Robot ready to receive commands.");
}

void loop() {
  // Check for incoming commands
  if (Serial.available()) {
    char command = Serial.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  switch (command) {
    case FORWARD:
      advance();
      Set_Speed(DEFAULT_SPEED);
      break;
    case BACKWARD:
      back();
      Set_Speed(DEFAULT_SPEED);
      break;
    case LEFT:
      turnL();
      Set_Speed(DEFAULT_SPEED);
      break;
    case RIGHT:
      turnR();
      Set_Speed(DEFAULT_SPEED);
      break;
    case STOP:
      stopp();
      break;
    case START:
      Serial.println("Robot started!");
      break;
    case PAUSE:
      stopp();
      Serial.println("Robot paused.");
      break;
    default:
      Serial.println("Invalid Command");
      break;
  }
}

void Set_Speed(unsigned char pwm) {
  analogWrite(Lpwm_pin, pwm);
  analogWrite(Rpwm_pin, pwm);
}

void advance() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
}

void turnR() {
  digitalWrite(pinRB, HIGH);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, LOW);
  digitalWrite(pinLF, HIGH);
}

void turnL() {
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinLF, LOW);
}

void stopp() {
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, LOW);
  digitalWrite(pinLB, LOW);
  digitalWrite(pinLF, LOW);
}

void back() {
  digitalWrite(pinRB, LOW);
  digitalWrite(pinRF, HIGH);
  digitalWrite(pinLB, LOW);
  digitalWrite(pinLF, HIGH);
}