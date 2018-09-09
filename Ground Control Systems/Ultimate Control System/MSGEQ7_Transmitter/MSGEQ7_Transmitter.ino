// this arduino transmits to the heli and is connected to
// a MSGEQ7 spectrum analyser board

// THIS IS YOUR UNIQUE ADDRESS (from 0-254) AND IT MUST MATCH THE ADDRESS IN THE RECEIVERS
// PLEASE CHANGE THIS FROM 43 AS THAT IS WHAT HAMISH IS USING!
#define UNIQUE_ADDRESS 43

// THIS DEFINES THE FREQUENCY BAND YOU'RE USING (from 0-8)
// IT MUST MATCH IN YOUR RECEIVERS AS WELL
// Hamish is using band 7 so you may want to change it
// Band 0 = 433.0 MHz
// Band 1 = 433.2 MHz
// Band 2 = 433.4 Mhz
// Band 3 = 433.6 MHz
// Band 4 = 433.8 MHz
// Band 5 = 434.0 MHz
// Band 6 = 434.2 Mhz
// Band 7 = 434.4 MHz
// Band 8 = 434.6 MHz
#define FREQUENCY_BAND 7

#define TRANSMITTER_ADDRESS 42

#include <SPI.h>
#include <RH_RF95.h>
#include <RHDatagram.h>

// MSGEQ7 SETUP
#include "MSGEQ7.h"
//definte MSGEQ7 pins
#define pinAnalogLeft A1
#define pinAnalogRight A0
#define pinReset 10
#define pinStrobe 9
//#define MSGEQ7_INTERVAL ReadsPerSecond(50)
#define MSGEQ7_SMOOTH false
CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, pinAnalogLeft, pinAnalogRight> MSGEQ7;

// DEFINE RADIO PINS ON UNO
#define RFM95_CS 4
#define RFM95_RST 2
#define RFM95_INT 3



//INITIALISE RADIO
RH_RF95 rf95(RFM95_CS, RFM95_INT);
RHDatagram manager(rf95, TRANSMITTER_ADDRESS);

// THIS DATA STRUCURE MATCHES THE ONE ON THE RECEIVER
struct dataStruct {
  uint8_t millisec[3];
  uint8_t spectrum[7];
} myData;

uint8_t tx_buf[sizeof(myData)] = {0};

const int RunPin = 7;
const int StopPin = 5;
const int ReadyPin = 8;
const int DemoPin = 6;

uint32_t millisec;
uint32_t startmillis;

void setup()
{

  float frequency = 433 + (FREQUENCY_BAND * 0.2); // set the frequency


  //MSGEQ7
  MSGEQ7.begin();


  pinMode(RunPin, INPUT);
  pinMode(ReadyPin, INPUT);
  pinMode(DemoPin, INPUT);
  pinMode(StopPin, INPUT);

  Serial.begin(115200);
  if (!rf95.init())
    Serial.println("init failed");
  rf95.setFrequency(frequency);
  rf95.setModemConfig(RH_RF95::Bw500Cr45Sf128); // set the radio to work fast
}

void loop()
{


  if (digitalRead(RunPin)) { //IF IT IS RUNNING

    rf95.setHeaderId(1); //mode is transmitted in the header.Run is 1
    if (millisec == 15000000) { //IF IT HAS BEEN STOPPED
      startmillis = millis();  //RESTART THE TIMER TO NOW
    }

    millisec = millis() - startmillis; //CALCULATE THE RUN TIME
    bool newReading = MSGEQ7.read(); //NEW MSGEQ7 READING
    for (uint8_t f = 0; f < 7; f++) {
      myData.spectrum[f] = mapNoise(MSGEQ7.get(f))  ; // PUT IT IN myData.spectrum
    }
  }
  else if (digitalRead(ReadyPin)) {

    rf95.setHeaderId(2);    //mode is transmitted in the header. Ready is 2
    millisec = 15000000;  // this is vital. It means the run routine goes straight through all the "Untils" if it comes out of run mid routine.
    for (uint8_t f = 0; f < 7; f++) {
      myData.spectrum[f] = 0  ;
    }
  }
  else if (digitalRead(DemoPin)) {

    rf95.setHeaderId(4);   //mode is transmitted in the header. Demo is 4

    millisec = 15000000; // this is vital. It means the run routine goes straight through all the "Untils" if it comes out of run mid routine.
    bool newReading = MSGEQ7.read(); //NEW MSGEQ7 READING
    for (uint8_t f = 0; f < 7; f++) {
      myData.spectrum[f] = mapNoise(MSGEQ7.get(f))  ; // PUT IT IN myData.spectrum
    }
  }
  else {

    rf95.setHeaderId(3);  //mode is transmitted in the header. Stop is 3

    millisec = 15000000; // this is vital. It means the run routine goes straight through all the "Untils" if it comes out of run mid routine.
    for (uint8_t f = 0; f < 7; f++) {
      myData.spectrum[f] = 0 ;
    }
  }

  // split up millisec into three octets.
  myData.millisec[0] = millisec;
  myData.millisec[1] = millisec >> 8;
  myData.millisec[2] = millisec >> 16;

  memcpy (tx_buf, &myData, sizeof(myData));
  byte zize = sizeof(myData);
  Serial.println("Sending to rf95_server");

  manager.sendto((uint8_t *)tx_buf, zize, UNIQUE_ADDRESS); //send the data

  rf95.waitPacketSent(); // wait until it is sent


}


