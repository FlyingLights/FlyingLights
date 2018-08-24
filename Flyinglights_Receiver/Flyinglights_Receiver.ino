
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CUSTOMISE THE LINES BELOW TO MATCH YOUR SETUP ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// for the three lines below it can be worth setting one more
// than the actual number of pixels if the last pixel is behaving oddly
#define CTOTALPIXELS 342 //TOTALNUMBER OF PIXELS ON THE CANOPY
#define STOTALPIXELS 23 //total number of pixels on the skids
#define TTOTALPIXELS 47 //TOTALNUMBER OF PIXELS ON THE tail

// this defines the number of rows (horizontal strips) and
// columns (number of LEDS on the longest strip
#define COLUMNS 37 // THE NUMBER OF COLUMNS OF CANOPY LEDS
#define ROWS 8 // THE NUMBER OF ROWS OF CANOPY LEDS

// reference pixels
#define TAILFINFIRST 28 // THE FIRST TAIL FIN PIXEL
#define TAILFINLAST 46 // THE LAST TAIL FIN PIXEL
#define SKIDSFIRST 4 // THE FIRST SKIDS PIXEL
#define SKIDSLAST 17 // THE LAST SKIDS PIXEL
#define BOOMFRONT 0 // THE FRONT (FIRST) TAIL BOOM PIXEL
#define BOOMREAR 27 // THE REAR TAIL BOOM PIXEL
#define UNDERFRONTFIRST 0 // THE FIRST FRONT UNDERCARRIAGE PIXEL
#define UNDERFRONTLAST 3 // THE LAST FRONT UNDERCARRIAGE PIXEL
#define UNDERREARFIRST 18 // THE FIRST REAR UNDERCARRIAGE PIXEL
#define UNDERREARLAST 21 // THE LAST REAR UNDERCARRIAGE PIXEL

// this defines the LED matrix on the LEFT canopy. The numbers are the addresses of the LEDs in rows from FRONT to BACK, running from TOP to BOTTOM
// 999 refers to an LED that is not present
uint16_t leftcanopy [][37] = {
  {999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 336, 337, 338, 339, 340, 341, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999},
  {999, 999, 999, 999, 999, 999, 999, 999, 308, 307, 306, 305, 304, 303, 302, 301, 300, 299, 298, 297, 296, 295, 294, 293, 292, 291, 290, 289, 288, 999, 999, 999, 999, 999, 999, 999, 999},
  {999, 999, 999, 999, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 999, 999, 999, 999, 999},
  {999, 199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 999, 999},
  {129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165},
  {999, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999},
  {999, 999, 999, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999},
  {999, 999, 999, 999, 34, 33, 32, 999, 6, 5, 4, 3, 2, 1, 0, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999},
};

// this defines the LED matrix on the RIGHT canopy. The numbers are the addresses of the LEDs in rows from FRONT to BACK, running from TOP to BOTTOM
// 999 refers to an LED that is not present
uint16_t rightcanopy [][37] = {
  {999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 335, 334, 333, 332, 331, 330, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999},
  {999, 999, 999, 999, 999, 999, 999, 999, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 999, 999, 999, 999, 999, 999, 999, 999},
  {999, 999, 999, 999, 259, 258, 257, 256, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 235, 234, 233, 999, 999, 999, 999, 999, 999},
  {999, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 999, 999, 999},
  {128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92},
  {999, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999},
  {999, 999, 999, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999},
  {999, 999, 999, 29, 30, 31, 999, 7, 8, 9, 10, 11, 12, 13, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999},
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// END OF CUSTOM SETUP ////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This code is written to run on a Feather M0 LORA 433Mhz
// https://www.adafruit.com/product/3179

//include the fastled library for driving the RGB LEDs
#include <FastLED.h>

// setup for 433mhz lora radio
#include <SPI.h> //include SPI library
#include <RH_RF95.h> //include radiohead library

// setup the correct pins feather board/LORA connection
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// THIS IS MY UNIQUE ADDRESS AND IT MUST MATCH THE ADDRESS IN THE TRANSMITTER
// PLEASE CHANGE THIS FROM 43 AS THAT IS WHAT HAMISH IS USING!
#define UNIQUE_ADDRESS 43

//initialise the radio
RH_RF95 rf95(RFM95_CS, RFM95_INT);

#define CPIN 13  // THE PIN NUMBER ON THE BOARD THAT THE CANOPY DATA WIRE IS CONNECTED TO
#define SPIN 11 // THE PIN NUMBER ON THE BOARD THAT THE SKIDS DATA WIRE IS CONNECTED TO
#define TPIN 10  // THE PIN NUMBER ON THE BOARD THAT THE TAIL DATA WIRE IS CONNECTED TO


// set up some useful colours for easy reference later
#define BLUE 0x0000FF
#define RED 0xFF0000
#define GREEN 0x00FF00
#define MAGENTA 0xFF00FF
#define CYAN 0x00FFFF
#define YELLOW 0xFFFF00
#define ORANGE 0xFF4500
#define PINK 0xDC143C
#define DULLYELLOW 0x222200
#define DULLRED 0x220000
#define DULLGREEN 0x002200
#define DULLCYAN 0x002222
#define DULLMAGENTA 0x220022
#define DULLBLUE 0x000022
#define DULLORANGE 0x220900
#define DULLPINK 0x1D0308
#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define LIGHTGREY 0x222222
#define GREY 0x101010
#define DULLGREY 0x060606


const CRGB blue = CRGB( BLUE);
const CRGB red = CRGB( RED);
const CRGB green = CRGB( GREEN);
const CRGB magenta = CRGB( MAGENTA);
const CRGB cyan = CRGB( CYAN);
const CRGB yellow = CRGB( YELLOW );
const CRGB orange = CRGB( ORANGE );
const CRGB pink = CRGB( PINK);
const CRGB dullyellow = CRGB( DULLYELLOW);
const CRGB dullred = CRGB( DULLRED);
const CRGB dullgreen = CRGB( DULLGREEN);
const CRGB dullcyan = CRGB( DULLCYAN);
const CRGB dullmagenta = CRGB( DULLMAGENTA);
const CRGB dullblue = CRGB( DULLBLUE);
const CRGB dullorange = CRGB( DULLORANGE);
const CRGB dullpink = CRGB( DULLPINK);
const CRGB black = CRGB( BLACK);
const CRGB white = CRGB( WHITE);
const CRGB lightgrey = CRGB( LIGHTGREY);
const CRGB grey = CRGB( GREY);
const CRGB dullgrey = CRGB( DULLGREY);


// prefined hue colours. These come from the FASTLED library
//  HUE_RED = 0, HUE_ORANGE = 32, HUE_YELLOW = 64, HUE_GREEN = 96,
//  HUE_AQUA = 128, HUE_BLUE = 160, HUE_PURPLE = 192, HUE_PINK = 224

CRGB cstrip[CTOTALPIXELS]; //setup the array for the canopy leds
CRGB sstrip[STOTALPIXELS]; //setup the array for the skid leds
CRGB tstrip[TTOTALPIXELS]; //setup the array for the tail leds

//this is the data structure for the info that comes over the radio
struct dataStruct {
  uint8_t mode;  //mode 1=run,2=ready,3=stop,4=demo
  uint8_t millisec[3]; //millisecond timer is split up into 4 bytes
  uint8_t spectrum[7]; //spectrum analyser over seven channels
} radio;

// radiomillis is the millisecond signal being sent over the radio. It is used
// during run mode but set to 15000000 when in other modes
uint32_t radiomillis;

// used to put a bright spot on the top of the spectrumtop function bars
uint8_t leftspectrumtop[7];
uint8_t rightspectrumtop[7];

// This variable is used for the starlights function. One variable for each row.
uint8_t starlights[ROWS];

uint8_t n; //just a handy reusable 8bit unsigned integer!
uint8_t m; //just a handy reusable 8bit unsigned integer!
uint8_t leftmax[7];
uint8_t rightmax[7];

void setup()
{

  //PUT THE VALUE OF COLUMNS INTO EACH OF STARLIGHTS
  for (uint8_t f = 0; f < ROWS; f++)
  {
    starlights[f] = COLUMNS;
  }

  // set the unique address of this receiver
  rf95.setThisAddress(UNIQUE_ADDRESS);

  //setup the FastLED strips with the correct led type, pin and array reference
  FastLED.addLeds<WS2812, CPIN, GRB>(cstrip, CTOTALPIXELS);
  FastLED.addLeds<WS2812, TPIN, GRB>(tstrip, TTOTALPIXELS);
  FastLED.addLeds<WS2812, SPIN, GRB>(sstrip, STOTALPIXELS);

  // only necessary for debugging
  Serial.begin(9600);

  //work out which pixel in each row is the last "real" pixel rather than a 999 blank
  // this is used for the specttrumtops function. Just looks nicer!
  for (uint8_t f = 0; f < 7; f++)
  {
    for (uint8_t g = 0; g < COLUMNS; g++)
    {
      if (leftcanopy[f + 1][g] < 999) {
        leftmax[f] = g;
      }
      if (rightcanopy[f + 1][g] < 999) {
        rightmax[f] = g;
      }
    }

    Serial.print(f);
    Serial.print(" leftmax:");
    Serial.print(leftmax[f]);
    Serial.print(" rightmax:");
    Serial.println(rightmax[f]);
  }


  if (!rf95.init())
    Serial.println("init failed");
}

void RadioCheck()  // this is used to check the LORA radio for incoming data
// it must be included in all "until" functions
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
  }
}

void Printout() // just for serial debugging
{

  Serial.print(radio.mode);
  Serial.print(" ");
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
  Serial.print(" RSSI: ");
  Serial.println(rf95.lastRssi(), DEC);
  Serial.println();

}

void WaitUntil(uint32_t waituntil) // just wait until a certain number of milliseconds has been reached. Keep checking the radio.
{
  while (radiomillis < waituntil)
  {
    Show();
    RadioCheck();
    Printout();
  }
}

void Canopy(CRGB colour) // set the whole canopy to a solid colour
{
  fill_solid( &(cstrip[0]), CTOTALPIXELS , colour );
}

void Tail(CRGB colour)  // set the whole tail to a solid colour
{
  fill_solid( &(tstrip[0]), TTOTALPIXELS , colour );
}

void Skids(CRGB colour)  // set the whole skids to a solid colour
{
  fill_solid( &(sstrip[0]), STOTALPIXELS , colour );
}

void All(CRGB colour) // set the whole heli to a solid colour
{
  Canopy(colour);
  Tail(colour);
  Skids(colour);
}

void TailFin(CRGB colour) // set the tail fin to a solid colour
{
  fill_solid( &(tstrip[TAILFINFIRST]), TAILFINLAST - TAILFINFIRST + 1 , colour );
}

void TailBoom(CRGB colour) // set the tail boom to a solid colour
{
  fill_solid( &(tstrip[BOOMFRONT]), BOOMREAR - BOOMFRONT + 1 , colour );
}

void SkidsSide(CRGB colour)  // set the side of the skids to a solid colour
{
  fill_solid( &(sstrip[SKIDSFIRST]), SKIDSLAST - SKIDSFIRST + 1 , colour );
}

void SkidsUnder(CRGB colour) // set the underside of the skids to a solic colour
{
  fill_solid( &(sstrip[UNDERFRONTFIRST]), UNDERFRONTLAST - UNDERFRONTFIRST + 1 , colour );
  fill_solid( &(sstrip[UNDERREARFIRST]), UNDERREARLAST - UNDERREARFIRST + 1 , colour );
}

void Show()
{
  FastLED.show();
}

void Finish()  // when this is reached it will hold until another mode is selected
{
  while (radiomillis < 14999999)
  {
    Show();
    RadioCheck();
    Printout();
  }

}

void TwoSparkleCanopy(float howmany1, CRGB colour1, CRGB colour2, uint8_t fade)
{

  howmany1 *= 100;

  for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      if (random8() < 128) {
        cstrip[j]=colour1;
      }
      else
      {
        cstrip[j]=colour2;
      }
    }
  }

  FastLED.show();

  nscale8(cstrip, CTOTALPIXELS, fade);

}

void SparkleCanopyTailBoom(float howmany1, CRGB colour1, uint8_t fade)
{

  howmany1 *= 100;

  for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      cstrip[j] = colour1;
    }
  }

  for (uint16_t j = BOOMFRONT; j <= BOOMREAR; j++) {
    if (random16(10000) < howmany1) {
      tstrip[j] = colour1;
    }
  }

  TailFin(colour1);  // bug

  FastLED.show();

  nscale8(cstrip, CTOTALPIXELS, fade);
  nscale8(tstrip, TTOTALPIXELS, fade);

}

void SparkleAll(float howmany1, CRGB colour1, uint8_t fade)
{

  howmany1 *= 100;

  for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      cstrip[j] = colour1;
    }
  }

  for (uint16_t j = 0; j < TTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      tstrip[j] = colour1;
    }
  }

  for (uint16_t j = 0; j < STOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      sstrip[j] = colour1;
    }
  }

  FastLED.show();

  nscale8(cstrip, CTOTALPIXELS, fade);
  nscale8(tstrip, TTOTALPIXELS, fade);
  nscale8(sstrip, STOTALPIXELS, fade);

}

void TwoSparkleAll(float howmany1, CRGB colour1, CRGB colour2, uint8_t fade)
{

  howmany1 *= 100;

  for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      if (random8() < 128) {
        cstrip[j] = colour1;
      }
      else
      {
        cstrip[j] = colour2;
      }
    }
  }

  for (uint16_t j = 0; j < TTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      if (random8() < 128) {
        tstrip[j] = colour1;
      }
      else
      {
        tstrip[j] = colour2;
      }
    }

  }

  for (uint16_t j = 0; j < STOTALPIXELS; j++) {

    if (random16(10000) < howmany1) {
      if (random8() < 128) {
        sstrip[j] = colour1;
      }
      else
      {
        sstrip[j] = colour2;
      }
    }
  }

  FastLED.show();

  nscale8(cstrip, CTOTALPIXELS, fade);
  nscale8(tstrip, TTOTALPIXELS, fade);
  nscale8(sstrip, STOTALPIXELS, fade);

}

void SparkleCanopyTailBoomUntil(uint32_t waituntil, float howmany1, CRGB colour1, uint8_t fade)
{
  while (radiomillis < waituntil)
  {
    RadioCheck();
    SparkleCanopyTailBoom(howmany1, colour1, fade);
  }
}

void SparkleAllUntil(uint32_t waituntil, float howmany1, CRGB colour1, uint8_t fade)
{
  while (radiomillis < waituntil)
  {
    RadioCheck();
    SparkleAll(howmany1, colour1, fade);
  }
}


void TwoSparkleAllUntil(uint32_t waituntil, float howmany1, CRGB colour1, CRGB colour2, uint8_t fade)
{
  while (radiomillis < waituntil)
  {
    RadioCheck();
    TwoSparkleAll(howmany1, colour1, colour2, fade);
  }
}
void TwoSparkleCanopyUntil(uint32_t waituntil, float howmany1, CRGB colour1, CRGB colour2, uint8_t fade)
{
  while (radiomillis < waituntil)
  {
    RadioCheck();
    TwoSparkleCanopy(howmany1, colour1, colour2, fade);
  }
}


void MergeAll (uint32_t until, CRGB startcolour, CRGB endcolour) { // merge from one solid colour to another on canopy, tail and skids

  // until = The radiomillis when this colour merge ends
  // startcolour = The starting RGB colour
  // endcolour = The ending RGB colour
  RadioCheck();
  uint32_t starttime = radiomillis;
  uint32_t totalduration = until - radiomillis;
  while (radiomillis < until)

  {
    uint32_t elapsed = radiomillis - starttime;
    uint32_t fraction = (elapsed << 8) / totalduration; //elapsed*256/totalduration gives the 8 bit fraction

    CRGB newcolour = startcolour.lerp8(endcolour, fraction);
    
    Canopy(newcolour);
    Skids(newcolour);
    Tail(newcolour);
    Show();
    RadioCheck();
  }

}

void SparkleMerge1 (uint32_t until, float howmany1, CRGB startcolour, CRGB endcolour, uint8_t fade) { // merge from one colour to another, but with the canopy and tail boom sparkling

  // until = The radiomillis when this colour merge ends
  // startcolour = The starting RGB colour
  // endcolour = The ending RGB colour

  howmany1 *= 100;

  RadioCheck();
  uint32_t starttime = radiomillis;
  uint32_t totalduration = until - radiomillis;
  while (radiomillis < until)
  {
    uint32_t elapsed = radiomillis - starttime;
    uint32_t fraction = (elapsed << 8) / totalduration; //elapsed*256/totalduration gives the 8 bit fraction

    CRGB newcolour = startcolour.lerp8(endcolour, fraction);

    for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
      if (random16(10000) < howmany1) {
        cstrip[j] = newcolour;

      }
    }

    for (uint16_t j = BOOMFRONT; j <= BOOMREAR; j++) {
      if (random16(10000) < howmany1) {
        tstrip[j] = newcolour;
      }
    }

    Skids(newcolour);
    TailFin(newcolour);

    FastLED.show();
    nscale8(cstrip, CTOTALPIXELS, fade);
    nscale8(tstrip, TTOTALPIXELS, fade);
    RadioCheck();
  }

}

// Spectrum analyser function for the canopy
void Spectrum(uint32_t until, uint32_t colour, uint8_t fade) {

  while (radiomillis < until)
  {
    //run down the rows and channels
    for (uint16_t i = 0; i < 7; i++) {
      // work out the WIDTH of the HORIZONTAL bars for each channel and put that in y
      uint16_t  y = (COLUMNS * radio.spectrum[i]) >> 8; //multiply the radio.spectrum signal by the number of columns and divide by 256
      // run ALONG the bar
      for (uint16_t j = 0; j < y; j++) {
        cstrip[(leftcanopy [i + 1][j])] = colour;
        cstrip[(rightcanopy [i + 1][j])] = colour;
      }
    }
    // show the pixels
    FastLED.show();
    //fade
    nscale8(cstrip, CTOTALPIXELS, fade);

    RadioCheck();
  }
}

// Spectrum analyser function for the canopy
void SpectrumTwoColour(uint32_t until, CRGB colour1, CRGB colour2) {

  while (radiomillis < until)
  {
    Canopy(colour2);

    //run down the rows and channels
    for (uint16_t i = 0; i < 7; i++) {
      // work out the WIDTH of the HORIZONTAL bars for each channel and put that in y
      uint16_t  y = (COLUMNS * radio.spectrum[i]) >> 8; //multiply the radio.spectrum signal by the number of columns and divide by 256
      // run ALONG the bar
      for (uint16_t j = 0; j < y; j++) {
        cstrip[(leftcanopy [i + 1][j])] = colour1;
        cstrip[(rightcanopy [i + 1][j])] = colour1;
      }
    }
    // show the pixels
    FastLED.show();
    RadioCheck();
  }
}

void SpectrumTop(uint32_t until, CRGB colour1, CRGB colour2, uint8_t fade) {

  uint8_t tracker;
  while (radiomillis < until)
  {
    tracker += 1;
    if (tracker == 3) {
      tracker = 0;
    }
    //run down the rows and channels
    for (uint16_t i = 0; i < 7; i++) {
      // work out the WIDTH of the HORIZONTAL bars for each channel and put that in y
      uint16_t  y = (COLUMNS * radio.spectrum[i]) >> 8; //multiply the radio.spectrum signal by the number of columns and divide by 256
      uint16_t j;
      // run ALONG the bar
      for (j = 0; j < y; j++) {
        cstrip[(leftcanopy [i + 1][j])] = colour1;
        cstrip[(rightcanopy [i + 1][j])] = colour1;
      }


      // put the right top on
      if ( rightspectrumtop[i] < j)
      {
        if (j > rightmax[i]) {
          rightspectrumtop[i] = rightmax[i];
        }
        else
        {
          rightspectrumtop[i] = j;
        }
      }
      else
      {
        if (rightspectrumtop[i] > 0 && tracker == 0) {
          rightspectrumtop[i] -= 1;
        }
      }

      cstrip[(rightcanopy [i + 1][rightspectrumtop[i]])] = colour2;

      // put the left top on it
      if ( leftspectrumtop[i] < j)
      {
        if (j > leftmax[i]) {
          leftspectrumtop[i] = leftmax[i];
        }
        else
        {
          leftspectrumtop[i] = j;
        }
      }
      else
      {
        if (leftspectrumtop[i] > 0 && tracker == 0) {
          leftspectrumtop[i] -= 1;
        }
      }
      cstrip[(leftcanopy [i + 1][leftspectrumtop[i]])] = colour2;

    }
    // show the pixels
    FastLED.show();
    //fade
    nscale8(cstrip, CTOTALPIXELS, fade);
    Printout();
    RadioCheck();
  }
}

void Starlights(uint32_t until, CRGB colour, uint8_t fade, uint8_t wait) {

  while (radiomillis < until)
  {
    for (uint8_t f = 0; f < ROWS; f++) {

      if  (starlights[f] == COLUMNS)
      {
        if (random(1, 10) == 1)
        {
          starlights[f] = 0;
        }
      }

      else
      {
        cstrip[(leftcanopy [f][starlights[f]])] = colour;
        cstrip[(rightcanopy [f][starlights[f]])] = colour;

        starlights[f]++;

      }
    }

    // show the pixels
    FastLED.show();
    //fade
    nscale8(cstrip, CTOTALPIXELS, fade);
    //slow it down a bit
    delay(wait);
    //check the radio
    RadioCheck();

  }

}

void ReverseStarlights(uint32_t until, CRGB colour, uint8_t fade, uint8_t wait) {

  while (radiomillis < until)
  {
    for (uint8_t f = 0; f < ROWS; f++) {

      if  (starlights[f] == COLUMNS)
      {
        if (random(1, 10) == 1)
        {
          starlights[f] = COLUMNS - 1;
        }
      }

      else

      {
        cstrip[(leftcanopy [f][starlights[f]])] = colour;
        cstrip[(rightcanopy [f][starlights[f]])] = colour;

        if (starlights[f] > 0)
        {
          starlights[f]--;
        }
        else
        {
          starlights[f] = COLUMNS;

        }
      }
    }

    // show the pixels
    FastLED.show();
    //fade
    nscale8(cstrip, CTOTALPIXELS, fade);
    //slow it down a bit
    delay(wait);
    //check the radio
    RadioCheck();
  }

}

void loop()
{

  RadioCheck(); //get the data from the radio
  Printout(); //serial.print just for debugging

  switch (radio.mode) { // go different ways depending on the current radio mode

    case 2:  //ready mode when radio.mode=2

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // READY MODE IS GENERALLY USED WHEN THE HELI IS WAITING TO START ROUTINE /////////////////////////////////////////////
      // CAN USE STATIC COLOURS OR DYNAMIC PATTERNS BUT NOT "UNTIL" FUNCTIONS   /////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // *********** FUNCTIONS FOR READY AND DEMO MODES  ***********

      // 1. HueTwoSparkleCanopy(PERCENT_OF_PIXELS_ON, HUE_1, HUE_2, FADE_SPEED)

      // This sparkles the canopy with two hues (HUE_1 and HUE_2).
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)
      // tail and skids do not change from previously set colours

      // 2. HueTwoSparkleAll(PERCENT_OF_PIXELS_ON, HUE_1, HUE_2, FADE_SPEED)

      // This sparkles the whole heli with two hues (HUE_1 and HUE_2).
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)

      // 3. HueSparkleAll(PERCENT_OF_PIXELS_ON, HUE_1, FADE_SPEED)

      // This sparkles the whole heli with one hue (HUE_1).
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)

      // 4. ColourSparkleAll(PERCENT_OF_PIXELS_ON, COLOUR_1, FADE_SPEED)

      // This sparkles the whole heli with one colour (COLOUR_1).
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)

      // 5. ColourSparkleCanopyTailBoom(PERCENT_OF_PIXELS_ON, COLOUR_1, FADE_SPEED)

      // This sparkles the canopy and tail boom with one colour (COLOUR_1).
      // ALSO KEEPS THE TAIL FIN THAT SOLID COLOUR TO STOP IT FADING
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)


      TwoSparkleAll( 0.8, CHSV(m, 255, 255), CHSV(n, 255, 255), 200);
      Tail(black);
      Skids (black);

      if (m % 10 == 0) {
        n += 1;
      }
      m += 1;

      break; // end of ready mode

    case 3:  // stop mode when radio.mode=3

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STOP MODE IS GENERALLY USED TO SWITCH OFF ALL LEDS /////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      All (black);
      Show();
      break; // end of stop mode

    case 4:   // demo mode when radio.mode=4

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // DEMO MODE //////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CAN USE STATIC COLOURS OR DYNAMIC PATTERNS BUT NOT "UNTIL" FUNCTIONS   /////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      All (dullgrey);
      Show();
      break; // end of demo mode

    case 1: //run mode when radio.mode=1

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // THIS IS WHERE THE CODE GOES THAT RUNS THE NIGHT FLYING ROUTINE /////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // Help on using this section is at https://github.com/FlyingLights/FlyingLights/wiki/RUN-Functions



      All(black);
      WaitUntil(15279); // wait for "staring upwards at the gleaming stars in the obsidian sky"
      SparkleMerge1 (19279, 0.3, black, white, 200);
      Skids(white);
      TailFin(white);
      SparkleCanopyTailBoomUntil(19365, 0.3, white, 200); //up to chord change
      SparkleCanopyTailBoomUntil(21942, 1, white, 200); //up to "we're marooned on a small island"
      SparkleMerge1 (23225, 1, white, green, 200); //merge through to "island" at 23225
      SparkleCanopyTailBoomUntil(25066, 1, green, 200); //up to "in an endless"
      SparkleMerge1 (26342, 1, green, blue, 200); //merge through to "sea" at 26342
      SparkleCanopyTailBoomUntil(28532, 1, blue, 200); //up to a point where it starts merging to yellow
      SparkleMerge1(29164, 1, blue, yellow, 200); //merged as it gets to sand
      SparkleCanopyTailBoomUntil(32322, 1, yellow, 200); //up to dramatic
      MergeAll(32722, black, red); //up to "but tonight"
      WaitUntil(35573);
      Starlights(38452, red, 200, 5);
      TailFin(cyan);
      Skids(cyan);
      Starlights(41723, cyan, 200, 5);
      TailFin(green);
      Skids(green);
      Starlights(47554, green, 200, 5);
      MergeAll(48054, black, orange); //this is the start of whaa
      WaitUntil(52616);
      Skids(orange);
      SparkleMerge1(55279, 50, orange, black, 20); //Bam1 up to Bam2 orange to black 50% sparkling
      WaitUntil(55379);
      SparkleMerge1(58089, 50, green, black, 20); //Bam2 up to Bam3
      WaitUntil(58189);
      SparkleMerge1(60829, 50, cyan, black, 20); //Bam3 up to Bam4
      WaitUntil(60929);
      SparkleMerge1(63545, 50, yellow, black, 20); //Ba4 up to Building up
      WaitUntil(63645);
      All(black);
      Finish();

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // END OF THE NIGHT FLYING ROUTINE ////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // DON'T CHANGE THE LINES BELOW!
      break; // end of run mode
  } // end of switch case
} // end of loop




