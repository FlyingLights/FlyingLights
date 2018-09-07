// This code is for UNO-based 433MHz receivers connected to other boards by I2C

// THIS IS MY UNIQUE ADDRESS AND IT MUST MATCH THE ADDRESS IN THE TRANSMITTER
// PLEASE CHANGE THIS FROM 43 AS THAT IS WHAT HAMISH IS USING!
#define UNIQUE_ADDRESS 43

//include the correct libraries
#include <SPI.h>
#include <RH_RF95.h>
#include <RHDatagram.h>
#include <Wire.h>

// DEFINE RADIO PINS ON UNO
#define RFM95_CS 4
#define RFM95_RST 2
#define RFM95_INT 3

//INITIALISE RADIO
RH_RF95 rf95(RFM95_CS, RFM95_INT);

uint8_t mode;  //mode 1=run,2=ready,3=stop,4=demo

// THIS DATA STRUCURE MATCHES THE ONE ON THE RECEIVER
struct dataStruct {
  uint8_t millisec[3];
  uint8_t spectrum[7];
} radio;

// radiomillis is the millisecond signal being sent over the radio. It is used
// during run mode but set to 15000000 when in other modes
uint32_t radiomillis;


void setup() {
  // set the unique address of this receiver
  rf95.setThisAddress(UNIQUE_ADDRESS);

    Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(I2C_request); // register event


  // only necessary for debugging
  Serial.begin(115200);
  
  if (!rf95.init())
    Serial.println("init failed");


  rf95.setModemConfig(RH_RF95::Bw500Cr45Sf128);

}

void RadioCheck()  // this is used to check the LORA radio for incoming data

{
  if (rf95.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      memcpy(&radio, buf, sizeof(radio));
    }
    else
    {
      Serial.println("recv failed");
    }
    radiomillis = (uint32_t)radio.millisec[2] << 16 | (uint32_t)radio.millisec[1] << 8 | (uint32_t)radio.millisec[0];

    mode = rf95.headerId();
  }
}

void Printout() // just for serial debugging
{

  //  Serial.print(radio.mode);
  //  Serial.print(" ");
  Serial.print(radiomillis);

  for (uint8_t f = 0; f < 7; f++) {

    uint8_t x = (radio.spectrum[f]);

    if (x < 30) {
      Serial.print                (" O        ");
    }
    else if (x < 60 && x > 29)    {
      Serial.print(" OX       ");
    }
    else if (x < 90 && x > 59)    {
      Serial.print(" O-X      ");
    }
    else if (x < 120 && x > 89)   {
      Serial.print(" O--X     ");
    }
    else if (x < 150 && x > 119)  {
      Serial.print(" O---X    ");
    }
    else if (x < 180 && x > 149)  {
      Serial.print(" O----X   ");
    }
    else if (x < 210 && x > 179)  {
      Serial.print(" O-----X  ");
    }
    else if (x < 240 && x > 209)  {
      Serial.print(" O------X ");
    }
    else if (x < 270 && x > 239)  {
      Serial.print(" O-------X");
    }

  }

  //   Serial.print("got request: ");
  //     Serial.println((char*)buf);

  Serial.print(" MODE: ");
  Serial.print(mode);
  Serial.print(" RSSI: ");
  Serial.println(rf95.lastRssi(), DEC);
  Serial.println();
}

// function that executes whenever data is requested by master, see setup()
void I2C_request() {
 Wire.write(mode); // respond with just 1 byte, which is the mode
}

void loop() { //loop just keeps requesting data from the radio
  RadioCheck();
  Printout();
}
