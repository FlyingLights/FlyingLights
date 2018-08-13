// This code is designed to run on an Arduino Uno in the ground station
// It is connected to an Adafruit Music Maker https://www.adafruit.com/product/1790
// an LCD display and snother UNO with MSGEQ7 spectrum analyser.

// include SPI, MP3, SD and LiquidCrystal libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <LiquidCrystal.h>

// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
#define CARDCS 4     // Card chip select pin
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

// set pin numbers:
const int RunButtonPin = 6;    // the number of the GPIO pin for RUN button
const int StopButtonPin = 7;
const int ReadyButtonPin = 5;
const int DemoButtonPin = 4;
const int PedalPin = 2;

const int RunLEDPin = 8;
const int StopLEDPin = 10;
const int ReadyLEDPin = 5;
const int DemoLEDPin = 9;

// Variables will change:
int StopLEDState = HIGH;
int ReadyLEDState = LOW;
int DemoLEDState = LOW;
int RunLEDState = LOW;

// the current reading from the input pins
int ReadyButtonState;
int RunButtonState;
int StopButtonState;
int DemoButtonState;
int PedalState;

int LastDebounce = 0;   // the previous reading from the input pin
uint8_t Debounce;

int Playing = 0;
int LastPlaying = 0;

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
uint32_t startplaying;

void setup() {

  pinMode(RunLEDPin, OUTPUT); // set up the LED pins
  pinMode(DemoLEDPin, OUTPUT);
  pinMode(ReadyLEDPin, OUTPUT);
  pinMode(StopLEDPin, OUTPUT);
  
  digitalWrite(RunLEDPin, LOW); // prob unnecessary but anyway!
  digitalWrite(DemoLEDPin, LOW);
  digitalWrite(StopLEDPin, LOW);
  digitalWrite(ReadyLEDPin, LOW);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Library Test");

  // initialise the music player
  if (! musicPlayer.begin()) { // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }
  Serial.println(F("VS1053 found"));

  musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working

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

// this are adafruit music maker pins
  musicPlayer.GPIO_pinMode(RunButtonPin, INPUT);
  musicPlayer.GPIO_pinMode(DemoButtonPin, INPUT);
  musicPlayer.GPIO_pinMode(StopButtonPin, INPUT);
  musicPlayer.GPIO_pinMode(ReadyButtonPin, INPUT);
  musicPlayer.GPIO_pinMode(PedalPin, INPUT);

// this bit just looks cool if you put the LEDs in the order stop,demo,ready,run 
  // it has no actual function.
  for (uint8_t f = 0; f < 3; f++) {
    digitalWrite(RunLEDPin, HIGH);
    delay(100);
    digitalWrite(RunLEDPin, LOW);
    digitalWrite(ReadyLEDPin, HIGH);
    delay(100);
    digitalWrite(ReadyLEDPin, LOW);
    digitalWrite(DemoLEDPin, HIGH);
    delay(100);
    digitalWrite(DemoLEDPin, LOW);
    digitalWrite(StopLEDPin, HIGH);
    delay(100);
    digitalWrite(StopLEDPin, LOW);
    digitalWrite(DemoLEDPin, HIGH);
    delay(100);
    digitalWrite(DemoLEDPin, LOW);
    digitalWrite(ReadyLEDPin, HIGH);
    delay(100);
    digitalWrite(ReadyLEDPin, LOW);
  }
  digitalWrite(RunLEDPin, HIGH);
  delay(100);
  digitalWrite(RunLEDPin, LOW);
  digitalWrite(ReadyLEDPin, HIGH);
  delay(100);
  digitalWrite(ReadyLEDPin, LOW);
  digitalWrite(DemoLEDPin, HIGH);
  delay(100);
  digitalWrite(DemoLEDPin, LOW);
  digitalWrite(StopLEDPin, HIGH);
  // end of cool but useless bit

  // set initial LED state
  digitalWrite(RunLEDPin, RunLEDState);
  digitalWrite(DemoLEDPin, DemoLEDState);
  digitalWrite(StopLEDPin, StopLEDState);
  digitalWrite(ReadyLEDPin, ReadyLEDState);
}

void loop() {
  // read the state of the switch into a local variable:
  int RunReading = musicPlayer.GPIO_digitalRead(RunButtonPin);
  int StopReading = musicPlayer.GPIO_digitalRead(StopButtonPin);
  int ReadyReading = musicPlayer.GPIO_digitalRead(ReadyButtonPin);
  int DemoReading = musicPlayer.GPIO_digitalRead(DemoButtonPin);
  int PedalReading = musicPlayer.GPIO_digitalRead(PedalPin);

  Serial.print ("RunReading: ");
  Serial.print (RunReading);
  Serial.print ("StopReading: ");
  Serial.print (StopReading);
  Serial.print ("ReadyReading: ");
  Serial.print (ReadyReading);
  Serial.print ("DemoReading: ");
  Serial.print (DemoReading);
  Serial.print ("PedalReading: ");
  Serial.println (PedalReading);

  Debounce = RunReading | (StopReading << 1) | (ReadyReading << 2) | (DemoReading << 3) | (PedalReading << 4);

  Serial.println(Debounce);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (Debounce != LastDebounce) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (RunReading != RunButtonState) {
      RunButtonState = RunReading;

      // only toggle the LED if the new button state is HIGH
      if (RunButtonState == HIGH) { // if run button is pressed

        if (RunLEDState == LOW) { // if it was not in run mode already
          musicPlayer.stopPlaying(); //stop playing first in case it was in demo mode
          musicPlayer.startPlayingFile("music.mp3"); // play the run music
          startplaying = millis();
          StopLEDState = LOW;
          RunLEDState = HIGH;
          ReadyLEDState = LOW;
          DemoLEDState = LOW;
        }
        else  //if it was in run mode already then go to stop and stop the music playing
        {
          StopLEDState = HIGH;
          RunLEDState = LOW;
          ReadyLEDState = LOW;
          DemoLEDState = LOW;
          musicPlayer.stopPlaying();
        }
      }
    }

    // if the button state has changed:
    if (PedalReading != PedalState) {
      PedalState = PedalReading;

      // only toggle the LED if the new button state is HIGH
      if (PedalState == HIGH) { // if pedal is pressed


        if (RunLEDState == LOW) { // if it was not in run mode already
          musicPlayer.stopPlaying();  // stop playing first in case it was in demo mode
          musicPlayer.startPlayingFile("music.mp3");  // play the run music
          startplaying = millis();
          StopLEDState = LOW;
          RunLEDState = HIGH;
          ReadyLEDState = LOW;
          DemoLEDState = LOW;
        }
        // there is no "else" here. You could add code to make the pedal stop run mode but it has been taken out
        // in case someone stands on it by accident. Use the buttons instead!
      }
    }

    if (DemoReading != DemoButtonState) {
      DemoButtonState = DemoReading;

      // only toggle the LED if the new button state is HIGH
      if (DemoButtonState == HIGH) { // if the demo button is pressed.

        if (DemoLEDState == LOW) {  //if it was not in demo mode already.
          musicPlayer.stopPlaying();  //stop playing first 
          musicPlayer.startPlayingFile("demo.mp3");  // play the demo music
          startplaying = millis();
          StopLEDState = LOW;
          RunLEDState = LOW;
          ReadyLEDState = LOW;
          DemoLEDState = HIGH;

        }
        else  // if it was already in demo mode then stop music and go into stop mode
        {
          StopLEDState = HIGH;
          RunLEDState = LOW;
          ReadyLEDState = LOW;
          DemoLEDState = LOW;
          musicPlayer.stopPlaying();
        }
      }
    }

    if (ReadyReading != ReadyButtonState) {
      ReadyButtonState = ReadyReading;

      // only toggle the LED if the new button state is HIGH
      if (ReadyButtonState == HIGH) {  // if the ready button is pressed
        
        if (ReadyLEDState == LOW) { // if it was not in ready mode already
          musicPlayer.stopPlaying(); //stop the music in case it was playing
          StopLEDState = LOW;
          RunLEDState = LOW;
          ReadyLEDState = HIGH;  // go into ready mode
          DemoLEDState = LOW;

        }
        else // go into stop mode if it was already in ready mode
        {
          StopLEDState = HIGH;
          RunLEDState = LOW;
          ReadyLEDState = LOW;
          DemoLEDState = LOW;

        }
      }
    }

    if (StopReading != StopButtonState) {
      StopButtonState = StopReading;


      // only toggle the LED if the new button state is HIGH
      if (StopButtonState == HIGH) { //if the stop button is pressed

        if (StopLEDState == LOW) {  // if it is not already in stop mode then do it.
          StopLEDState = HIGH;
          RunLEDState = LOW;
          ReadyLEDState = LOW;
          DemoLEDState = LOW;

          musicPlayer.stopPlaying();
          Serial.println("STOP going from low to high");
        }
        // no else here!
      }
    }
  }


  if  (musicPlayer.playingMusic) { // if it is playing music store it in this variable
    Playing = HIGH;
  }
  else
  {
    Playing = LOW;
  }

  if (LastPlaying > Playing && (RunLEDState == HIGH || DemoLEDState == HIGH)) { // if it has just stopped playing music on this cycle through the loop
  // them put it into stop mode
    StopLEDState = HIGH;
    RunLEDState = LOW;
    ReadyLEDState = LOW;
    DemoLEDState = LOW;
  }

  // send data to the LCD
  if  (RunLEDState) {
    lcd.setCursor(0, 0);
    lcd.print("RUNNING       ");
  }

  if (StopLEDState)
  {
    lcd.setCursor(0, 0);
    lcd.print("STOPPED       ");
  }

  if (ReadyLEDState)
  {
    lcd.setCursor(0, 0);
    lcd.print("READY         ");
  }

  if (DemoLEDState)
  {
    lcd.setCursor(0, 0);
    lcd.print("DEMO         ");
  }

  // set the LEDs:
  digitalWrite(RunLEDPin, RunLEDState);
  digitalWrite(StopLEDPin, StopLEDState);
  digitalWrite(ReadyLEDPin, ReadyLEDState);
  digitalWrite(DemoLEDPin, DemoLEDState);

  // save the reading.  Next time through the loop,
  // it'll be the LastDebounce
  LastDebounce = Debounce;
  LastPlaying = Playing;  //remember for the next time through the loop whether it was playing this time or not
}
