// This code is written to run on a Feather M0 LORA 433Mhz
// https://www.adafruit.com/product/3179

// setup for 433mhz lora radio
#include <SPI.h> //include SPI library
#include <RH_RF95.h> //include radiohead library
#include <RHDatagram.h>

// setup the correct pins feather board/LORA connection
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// THIS IS MY UNIQUE ADDRESS AND IT MUST MATCH THE ADDRESS IN THE TRANSMITTER
// PLEASE CHANGE THIS FROM 43 AS THAT IS WHAT HAMISH IS USING!
#define UNIQUE_ADDRESS 43

#define TRANSMITTER_ADDRESS 42

//INITIALISE RADIO
RH_RF95 rf95(RFM95_CS, RFM95_INT);
RHDatagram manager(rf95, TRANSMITTER_ADDRESS);

const int PedalPin = A2;
const int LEDPin = 13;

bool mode = LOW;         // the current state of the output pin
int PedalState;             // the current reading from the input pin
int lastPedalState = LOW;   // the previous reading from the input pin

uint32_t lastDebounceTime = 0;  // the last time the output pin was toggled
uint32_t debounceDelay = 50;    // the debounce time; increase if the output flickers


// THIS DATA STRUCURE MATCHES THE ONE ON THE RECEIVER
struct dataStruct {
  uint8_t millisec[3];
  uint8_t spectrum[7];
} myData;

uint8_t tx_buf[sizeof(myData)] = {0};

uint32_t millisec;
uint32_t startmillis;


void setup() {

  pinMode(LEDPin, OUTPUT);
  pinMode(PedalPin, INPUT_PULLUP);
  Serial.print("initial mode:");
  Serial.println(mode);

  // this simple transmitter does not have a spectrum analyser. Fill this up with zeros
  for (uint8_t f = 0; f < 7; f++) {
    myData.spectrum[f] = 0  ;
  }

  Serial.begin(115200);
  if (!rf95.init())
    Serial.println("init failed");
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
  rf95.setPreambleLength(8);
  rf95.setModemConfig(RH_RF95::Bw500Cr45Sf128); // set the radio to work fast
}

void loop() {

    // read the state of the pedal into a local variable:
 uint8_t reading = digitalRead(PedalPin);

   // If the pedal has changed:
  if (reading != lastPedalState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the pedal state has changed:
    if (reading != PedalState) {
      PedalState = reading;

      // only toggle the LED if the new pedal state is LOW (because it is being grounded)
      if (PedalState == LOW) {
        mode = !mode;
      }
    }
  }

    // set the LED:
  digitalWrite(LEDPin, mode);

  // save the reading.  Next time through the loop,
  // it'll be the lastPedalState:
  lastPedalState = reading;


  if (mode) { //IF IT IS RUNNING

    rf95.setHeaderId(1); //mode is transmitted in the header. Run is 1.

    if (millisec == 15000000) { //IF IT HAS BEEN STOPPED
      startmillis = millis();  //RESTART THE TIMER TO NOW
    }

    millisec = millis() - startmillis; //CALCULATE THE RUN TIME

  }


  else { // if we are not in run mode it must be stopped
    //simple transmitter only has run and stop modes

    rf95.setHeaderId(3); //mode is transmitted in the header. Stop is 3.
    millisec = 15000000; // this is vital. It means the run routine goes straight through all the "Untils" if it comes out of run mid routine.
    for (uint8_t f = 0; f < 7; f++) {
      myData.spectrum[f] = 0 ;
    }
  }

Serial.println(mode);

// split up millisec into three octets. 
  myData.millisec[0] = millisec;
  myData.millisec[1] = millisec >> 8;
  myData.millisec[2] = millisec >> 16;

  memcpy (tx_buf, &myData, sizeof(myData));
  byte zize = sizeof(myData);
  Serial.println("Sending to rf95_server");

  manager.sendto((uint8_t *)tx_buf, zize,UNIQUE_ADDRESS); //send the data

  rf95.waitPacketSent(); // wait until it is sent


}
