// This code is for UNO-based 433MHz receivers connected to other boards by I2C

// THIS IS MY UNIQUE ADDRESS AND IT MUST MATCH THE ADDRESS IN THE TRANSMITTER
// PLEASE CHANGE THIS FROM 43 AS THAT IS WHAT HAMISH IS USING!
#define UNIQUE_ADDRESS 43

//include the correct libraries
#include <SPI.h>
#include <RH_RF95.h>
#include <RHDatagram.h>

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3


//INITIALISE RADIO
RH_RF95 rf95(RFM95_CS, RFM95_INT);

uint8_t mode;  //mode 1=run,2=ready,3=stop,4=demo
uint8_t RunPin = 11;
uint8_t StopPin = 12;
uint8_t ReadyPin = A0;
uint8_t DemoPin = A3;


void setup() {
  // set the unique address of this receiver
  rf95.setThisAddress(UNIQUE_ADDRESS);


  // only necessary for debugging
  Serial.begin(115200);

  if (!rf95.init())
    Serial.println("init failed");


  rf95.setModemConfig(RH_RF95::Bw500Cr45Sf128);


  pinMode(RunPin, OUTPUT);
  pinMode(StopPin, OUTPUT);
  pinMode(DemoPin, OUTPUT);
  pinMode(ReadyPin, OUTPUT);

  digitalWrite(RunPin, HIGH);
  digitalWrite(StopPin, HIGH);
  digitalWrite(ReadyPin, HIGH);
  digitalWrite(DemoPin, HIGH);

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
       Serial.println("recv success");
    }
    else
    {
      Serial.println("recv failed");
    }

    mode = rf95.headerId();
  }
}

void Printout() // just for serial debugging
{
  Serial.print(" MODE: ");
  Serial.print(mode);
  Serial.print(" RSSI: ");
  Serial.println(rf95.lastRssi(), DEC);
  Serial.println();
}



void loop() { //loop just keeps requesting data from the radio
  RadioCheck();
  Printout();

  if (mode == 1) {
    digitalWrite(RunPin, LOW);
    digitalWrite(StopPin, HIGH);
    digitalWrite(ReadyPin, HIGH);
    digitalWrite(DemoPin, HIGH);
  }
  else if (mode == 4) {
    digitalWrite(RunPin, HIGH);
    digitalWrite(StopPin, HIGH);
    digitalWrite(ReadyPin, HIGH);
    digitalWrite(DemoPin, LOW);
  }
  else if (mode == 3) {
    digitalWrite(RunPin, HIGH);
    digitalWrite(StopPin, LOW);
    digitalWrite(ReadyPin, HIGH);
    digitalWrite(DemoPin, HIGH);
  }
  else if (mode == 2) {
    digitalWrite(RunPin, HIGH);
    digitalWrite(StopPin, LOW);
    digitalWrite(ReadyPin, HIGH);
    digitalWrite(DemoPin, HIGH);
  }
}
