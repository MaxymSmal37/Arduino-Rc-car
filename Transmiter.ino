#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"

#define CE_PIN 9
#define CSN_PIN 10


#define INTERVAL_MS_TRANSMISSION 250

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

struct payload {
  int data1;
  int data2;
};
int axisX = 1;
int axisY = 0;

payload payload;

void setup()
{
  Serial.begin(115200);

  radio.begin();
  pinMode(2, OUTPUT); 


  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX); 
  radio.setPayloadSize(sizeof(payload));
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop()
{
  digitalWrite(2, HIGH);

  payload.data1 = analogRead(axisX);
  payload.data2 = analogRead(axisY);

  radio.write(&payload, sizeof(payload));

  Serial.print("Data1:");
  Serial.println(payload.data1);

  Serial.print("Data2:");
  Serial.println(payload.data2);

  Serial.println("Sent");

  delay(INTERVAL_MS_TRANSMISSION);
}

