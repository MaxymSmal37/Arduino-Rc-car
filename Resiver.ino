

#include <Servo.h>
#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"

#define CE_PIN 9
#define CSN_PIN 10

#define INTERVAL_MS_SIGNAL_LOST 1000
#define INTERVAL_MS_SIGNAL_RETRY 250

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

//NRF24L01 buffer limit is 32 bytes (max struct size)
struct payload {
  int data1;
  int data2;
};

payload payload;

unsigned long lastSignalMillis = 0;

Servo myservo;  // create servo object to control a servo 
int valY;
int valX;
// Motor A connections
int enA = 6;
int in1 = 7;
int in2 = 4;
// Motor B connections
int enB = 5;
int in3 = 3;
int in4 = 2;

const int POT_MIN = 0;
const int POT_MAX = 1023;
const int SERVO_MIN = 0;
const int SERVO_MAX = 180;
const int THRESHOLD_FORWARD = 550;
const int THRESHOLD_BACKWARD = 500;
const int DELAY_TIME = 100;

void forward(int speed, int degree) {
  myservo.write(degree);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward(int speed, int degree) {
  speed = (1024 - speed);
  myservo.write(degree);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stop(int degree) {
  myservo.write(degree);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void move(){

  if (valX > THRESHOLD_FORWARD) {
    forward(valX, valY);
  } else if (valX < THRESHOLD_BACKWARD) {
    backward(valY, valY);
  } else {
    stop(valY);
  }
}
void lostConnection()
{
  Serial.println("We have lost connection, preventing unwanted behavior");

  delay(INTERVAL_MS_SIGNAL_RETRY);
}




void setup() {
  radio.begin();

  //Append ACK packet from the receiving radio back to the transmitting radio
  radio.setAutoAck(false); //(true|false)
  //Set the transmission datarate
  radio.setDataRate(RF24_250KBPS); //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS)
  //Greater level = more consumption = longer distance
  radio.setPALevel(RF24_PA_MIN); //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX)
  //Default value is the maximum 32 bytes1
  radio.setPayloadSize(sizeof(payload));
  //Act as receiver
  radio.openReadingPipe(0, address);
  radio.startListening();
  myservo.attach(0);  // initialize the servo
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  // valX = analogRead(axisX);
  // valY = analogRead(axisY);
  // valY = map(valY, POT_MIN, POT_MAX, SERVO_MIN, SERVO_MAX);
  // move();


    unsigned long currentMillis = millis();

  if (radio.available() > 0) {
    radio.read(&payload, sizeof(payload));

    valX = payload.data1;
    valY = payload.data2;
    valY = map(valY, POT_MIN, POT_MAX, SERVO_MIN, SERVO_MAX);
    move();
  
    lastSignalMillis = currentMillis;
  }

  if (currentMillis - lastSignalMillis > INTERVAL_MS_SIGNAL_LOST) {
    lostConnection();
  }

  delay(DELAY_TIME);
}






