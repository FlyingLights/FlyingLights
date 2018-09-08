// This code is designed to run on an Arduino Uno mp3 player
// It has an adafruit music maker board stacked on top of it and is connected by I2C
// to another board which is running I2C_Receiver and is connected to a LORA radio.

// include SPI, MP3, SD and I2C libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>


#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS       6     // VS1053 chip select pin (output)
#define SHIELD_DCS     10     // VS1053 Data/command select pin (output)
#define CARDCS          5     // Card chip select pin
#define DREQ     9     // VS1053 Data request, ideally an Interrupt pin




Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);


uint8_t oldmode; //to pick up if the mode has changed
uint8_t mode;  //mode 1=run,2=ready,3=stop,4=demo
uint8_t RunPin = 11;
uint8_t StopPin = 12;
uint8_t ReadyPin = A0;
uint8_t DemoPin = A3;

void setup() {


  pinMode(RunPin, INPUT_PULLUP);
  pinMode(StopPin, INPUT_PULLUP);
  pinMode(DemoPin, INPUT_PULLUP);
  pinMode(ReadyPin, INPUT_PULLUP);


  Serial.begin(115200); // for debugging



  Serial.println("\n\nAdafruit VS1053 Feather Test");

  if (! musicPlayer.begin()) { // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }
  Serial.println(F("VS1053 found"));

  musicPlayer.sineTest(0x45, 500);    // Make a tone to indicate VS1053 is working

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  Serial.println("SD OK!");

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(1, 1); //this is loud!

  // This option uses a pin interrupt. No timers required! But DREQ
  // must be on an interrupt pin. For Uno/Duemilanove/Diecimilla
  // that's Digital #2 or #3


  if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
    Serial.println(F("DREQ pin is not an interrupt pin"));
}

void loop() {

  if (digitalRead(RunPin)==LOW) { //IF IT IS RUNNING
    mode = 1;

    Serial.println(1);
  }

  else if (digitalRead(ReadyPin)==LOW) {
    Serial.println(2);
    mode = 2;
  }
  else if (digitalRead(DemoPin)==LOW) {
   Serial.println(4);
    mode = 4;
  }
  else if (digitalRead(StopPin)==LOW) {
       Serial.println(3);
    mode = 3;
  }



  if (mode != oldmode) { //if the mode has changed

    if (mode == 1) { //run mode
      musicPlayer.stopPlaying(); //stop playing first in case it was in demo mode
      musicPlayer.startPlayingFile("music.mp3"); // play the run music
    }

    else if (mode == 4) {
      musicPlayer.stopPlaying();  //stop playing first
      musicPlayer.startPlayingFile("demo.mp3");  // play the demo music
    }

    else {
      musicPlayer.stopPlaying(); //stop playing, it is not in run or demo mode
    }
  }

  oldmode = mode;
}
