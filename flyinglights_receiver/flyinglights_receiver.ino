// This code is written to run on a Feather M0 LORA 433Mhz
// https://www.adafruit.com/product/3179

//include the fastled library for driving the RGB LEDs
#include <FastLED.h>

// setup for 433mhz lora radio
#include <SPI.h> //include SPI library
#include <RH_RF95.h> //include radiohead library
// setup the correct pins
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
// Define the operating frequency   **** you only need to change the line below to use a different frequency
#define RF95_FREQ 433.0
//initialise the radio
RH_RF95 rf95(RFM95_CS, RFM95_INT);

#define CPIN 13  // THE PIN NUMBER ON THE BOARD THAT THE CANOPY DATA WIRE IS CONNECTED TO
#define SPIN 11 // THE PIN NUMBER ON THE BOARD THAT THE SKIDS DATA WIRE IS CONNECTED TO
#define TPIN 10  // THE PIN NUMBER ON THE BOARD THAT THE TAIL DATA WIRE IS CONNECTED TO

// this defines the number of rows (horizontal strips) and
// columns (number of LEDS on the longest strip
#define COLUMNS 37 // THE NUMBER OF COLUMNS OF CANOPY LEDS
#define ROWS 8 // THE NUMBER OF ROWS OF CANOPY LEDS

// for the three lines below it can be worth setting one more
// than the actual number of pixels if the last pixel is behaving oddly
#define CTOTALPIXELS 342 //TOTALNUMBER OF PIXELS ON THE CANOPY
#define STOTALPIXELS 23 //total number of pixels on the skids
#define TTOTALPIXELS 47 //TOTALNUMBER OF PIXELS ON THE tail

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

// prefined hue colours. These come from the FASTLED library
//  HUE_RED = 0, HUE_ORANGE = 32, HUE_YELLOW = 64, HUE_GREEN = 96,
//  HUE_AQUA = 128, HUE_BLUE = 160, HUE_PURPLE = 192, HUE_PINK = 224

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

CRGB cstrip[CTOTALPIXELS]; //setup the array for the canopy leds
CRGB sstrip[STOTALPIXELS]; //setup the array for the skid leds
CRGB tstrip[TTOTALPIXELS]; //setup the array for the tail leds

//this is the data structure for the info that comes over the radio
struct dataStruct {
  uint8_t mode;  //mode 1=run,2=ready,3=stop,4=demo
  uint8_t millisec[4]; //millisecond timer is split up into 4 bytes
  uint8_t spectrum[7]; //spectrum analyser over seven channels
} radio;

// radiomillis is the millisecond signal being sent over the radio. It is used
// during run mode but set to 2000000000 when in other modes
uint32_t radiomillis;

// used to put a bright spot on the top of the spectrumtop function bars
uint8_t leftspectrumtop[7];
uint8_t rightspectrumtop[7];

// this defines the LED matrix on the canopy. The numbers are the addresses of the LEDs in rows from FRONT to BACK, starting at the bottom and working up
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


uint8_t n; //just a handy reusable 8bit unsigned integer!
uint8_t m; //just a handy reusable 8bit unsigned integer!
uint8_t leftmax[7];
uint8_t rightmax[7];

void setup()
{


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
      if (leftcanopy[f+1][g] < 999) {
        leftmax[f] = g;
      }
      if (rightcanopy[f+1][g] < 999) {
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

void loop()
{

  RadioCheck(); //get the data from the radio
  printout(); //serial.print just for debugging

  switch (radio.mode) { // go different ways depending on the current radio mode

    case 1: //run mode when radio.mode=1

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // THIS IS WHERE THE CODE GOES THAT RUNS THE NIGHT FLYING ROUTINE /////////////////////////////////////////////////////
      // ONLY USE FUNCTIONS IN HERE FOR CLARITY /////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // ***********  SPECIAL FUNCTIONS THAT CAN BE USED: ***********

      // 1. Show();
      // This shows the pre-selected static colours on the canopy.
      // Not needed with dynamic functions.

      // 2. WaitUntil(TIME_IN_MILLISECONDS);
      // This function waits *unitl* TIME_IN_MILLISECONDS is reached.

      // 3. Finish();
      // This is almost always placed at the end of the routine.
      // It waits here until another mode is selected. Without it
      // the run routine will repeat again.

      // ***********  STATIC FUNCTIONS THAT CAN BE USED: ***********

      // * STATIC COLOUR FUNCTIONS

      // 1. ColourCanopy (COLOUR);
      // This fills the canopy with a 24 bit RGB colour.
      // Can use predifined colours such as DULLGREEN but not hues such as HUE_AQUA
      // Note it does not show the colour until SHOW(); function is called.

      // 2. ColourTail (COLOUR);
      // This fills the whole tail with a 24 bit RGB colour.
      // Can use predifined colours such as DULLGREEN but not hues such as HUE_AQUA
      // Note it does not show the colour until SHOW(); function is called.

      // 3. ColourSkids (COLOUR);
      // This fills the whole skids with a 24 bit RGB colour.
      // Can use predifined colours such as DULLGREEN but not hues such as HUE_AQUA
      // Note it does not show the colour until SHOW(); function is called.

      // 4. ColourTailBoom (COLOUR);
      // This fills the tail boom with a 24 bit RGB colour.
      // Can use predifined colours such as DULLGREEN but not hues such as HUE_AQUA
      // Note it does not show the colour until SHOW(); function is called.

      // 5. ColourTailFin (COLOUR);
      // This fills the tail fin with a 24 bit RGB colour.
      // Can use predifined colours such as DULLGREEN but not hues such as HUE_AQUA
      // Note it does not show the colour until SHOW(); function is called.

      // 6. ColourSkidsUnder (COLOUR);
      // This fills the tail boom with a 24 bit RGB colour.
      // Can use predifined colours such as DULLGREEN but not hues such as HUE_AQUA
      // Note it does not show the colour until SHOW(); function is called.

      // 7. ColourSkidsSide (COLOUR);
      // This fills the side of the skids with a 24 bit RGB colour.
      // Can use predifined colours such as DULLGREEN but not hues such as HUE_AQUA
      // Note it does not show the colour until SHOW(); function is called.

      // 8. ColourAll (COLOUR);
      // This fills the whole heli with a 24 bit RGB colour.
      // Can use predifined colours such as DULLGREEN but not hues such as HUE_AQUA

      // * STATIC HUE FUNCTIONS

      // 1. HueCanopy (HUE);
      // This fills the canopy with a rainbow hue from 0-255.
      // Can use hues such as HUE_YELLOW but not colours such as WHITE
      // Note it does not show the colour until SHOW(); function is called.

      // 2. HueTail (HUE);
      // This fills the tail with a rainbow hue from 0-255.
      // Can use hues such as HUE_YELLOW but not colours such as WHITE
      // Note it does not show the colour until SHOW(); function is called.

      // 3. HueSkids (HUE);
      // This fills the whole skids with a rainbow hue from 0-255.
      // Can use hues such as HUE_YELLOW but not colours such as WHITE
      // Note it does not show the colour until SHOW(); function is called.

      // 4. HueTailBoom (HUE);
      // This fills the tail boom with a rainbow hue from 0-255.
      // Can use hues such as HUE_YELLOW but not colours such as WHITE
      // Note it does not show the colour until SHOW(); function is called.

      // 5. HueTailFin (HUE);
      // This fills the tail fin with a rainbow hue from 0-255.
      // Can use hues such as HUE_YELLOW but not colours such as WHITE
      // Note it does not show the colour until SHOW(); function is called.

      // 6. HueSkidsUnder (HUE);
      // This fills the tail boom with a rainbow hue from 0-255.
      // Can use hues such as HUE_YELLOW but not colours such as WHITE
      // Note it does not show the colour until SHOW(); function is called.

      // 7. HueSkidsSide (HUE);
      // This fills the side of the skids with a rainbow hue from 0-255.
      // Can use hues such as HUE_YELLOW but not colours such as WHITE
      // Note it does not show the colour until SHOW(); function is called.

      // 8. HueAll (HUE);
      // This fills the whole heli with a rainbow hue from 0-255.
      // Can use hues such as HUE_YELLOW but not colours such as WHITE

      // ***********  DYNAMIC "UNTIL" FUNCTIONS THAT CAN BE USED: ***********

      // * COLOUR "UNTIL" FUNCTIONS

      // 1. ColourMergeAllUntil(TIME_IN_MILLISECONDS, COLOUR_1, COLOUR_2);

      // This fills the heli with COLOUR_1 which merges to COLOUR_2.
      // Runs until TIME_IN_MILLIDECONDS is reached.

      // 2. ColourOneSparkleAllUntil(TIME_IN_MILLISECONDS, PERCENT_OF_PIXELS_ON, COLOUR_1, FADE_SPEED)

      // This sparkles the whole heli with one colour (COLOUR_1).
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)
      // Runs until TIME_IN_MILLISECONDS is reached

      // 3. ColourOneSparkleCanopyTailBoomUntil(TIME_IN_MILLISECONDS, PERCENT_OF_PIXELS_ON, COLOUR_1, FADE_SPEED)

      // This sparkles the canopy and tail boom with one colour (COLOUR_1).
      // ALSO KEEPS THE TAIL FIN THAT SOLID COLOUR TO STOP IT FADING
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)
      // Runs until TIME_IN_MILLISECONDS is reached

      // 4. ColourMergeAllSparklingCanopyTailBoomUntil (TIME_IN_MILLISECONDS, PERCENT_OF_PIXELS_ON, START_COLOUR, END_COLOUR, FADE_SPEED)
      // This sparkles the canopy and tail boom with the rest of the heli solid colour.
      // The colour merges from COLOUR_1 to COLOUR_2.
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100 and is just for canopy and tail boom.
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)
      // Runs until TIME_IN_MILLISECONDS is reached


      // * HUE "UNTIL" FUNCTIONS

      // 1. HueTwoSparkleCanopyUntil(TIME_IN_MILLISECONDS, PERCENT_OF_PIXELS_ON, HUE_1, HUE_2, FADE_SPEED)

      // This sparkles the canopy with two hues (HUE_1 and HUE_2).
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)
      // Runs until TIME_IN_MILLISECONDS is reached
      // tail and skids do not change from previously set colours

      // 2. HueTwoSparkleAllUntil(TIME_IN_MILLISECONDS, PERCENT_OF_PIXELS_ON, HUE_1, HUE_2, FADE_SPEED)

      // This sparkles the whole heli with two hues (HUE_1 and HUE_2).
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)
      // Runs until TIME_IN_MILLISECONDS is reached

      // 3. HueOneSparkleAllUntil(TIME_IN_MILLISECONDS, PERCENT_OF_PIXELS_ON, HUE_1, FADE_SPEED)

      // This sparkles the whole heli with one hue (HUE_1).
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)
      // Runs until TIME_IN_MILLISECONDS is reached

      // 4. HueMergeAllUntil(TIME_IN_MILLISECONDS, HUE_1, HUE_2);

      // This fills the heli with HUE_1 which merges to HUE_2.
      // Runs until TIME_IN_MILLISECONDS is reached.
      
      SpectrumTop(900000, DULLCYAN, RED, 100);
      ColourAll(BLACK);
      WaitUntil(15279); // wait for "staring upwards at the gleaming stars in the obsidian sky"
      ColourMergeAllSparklingCanopyTailBoomUntil (19279, 0.3, BLACK, WHITE, 200);
      ColourSkids(WHITE);
      ColourTailFin(WHITE);
      ColourOneSparkleCanopyTailBoomUntil(19365, 0.3, WHITE, 200); //up to chord change
      ColourOneSparkleCanopyTailBoomUntil(21942, 1, WHITE, 200); //up to "we're marooned on a small island"
      ColourMergeAllSparklingCanopyTailBoomUntil (23225, 1, WHITE, GREEN, 200); //merge through to "island" at 23225
      ColourOneSparkleCanopyTailBoomUntil(25066, 1, GREEN, 200); //up to "in an endless"
      ColourMergeAllSparklingCanopyTailBoomUntil (26342, 1, GREEN, BLUE, 200); //merge through to "sea" at 26342
      ColourOneSparkleCanopyTailBoomUntil(28532, 1, BLUE, 200); //up to a point where it starts merging to yellow
      ColourMergeAllSparklingCanopyTailBoomUntil(29164, 1, BLUE, YELLOW, 200); //merged as it gets to sand
      ColourOneSparkleCanopyTailBoomUntil(32322, 1, YELLOW, 200); //up to dramatic
      ColourMergeAllUntil(32722, BLACK, RED); //up to "but tonight"


      //      ColourCanopy (DULLGREEN);
      //      ColourTailBoom (DULLPINK);
      //      ColourTailFin (DULLRED);
      //      ColourSkidsSide (DULLBLUE);
      //      ColourSkidsUnder (DULLCYAN);
      //      Show();
      //      WaitUntil(5000);
      //
      //      HueCanopy (HUE_BLUE);
      //      ColourTailBoom(DULLMAGENTA);
      //      ColourTailFin (DULLBLUE);
      //      ColourSkidsSide (DULLORANGE);
      //      ColourSkidsUnder (DULLGREEN);
      //      Show();
      //      WaitUntil(10000);
      //
      //      ColourMergeAllUntil(12000, DULLPINK, GREEN);
      //      ColourMergeAllUntil(16000, BLACK, CYAN);
      //      ColourMergeAllUntil(19000, DULLRED, DULLYELLOW);
      //      ColourMergeAllUntil(23000, GREY, GREEN);
      //
      //      ColourCanopy (DULLORANGE);
      //      ColourTailBoom (DULLBLUE);
      //      ColourTailFin (DULLPINK);
      //      ColourSkidsSide (DULLGREEN);
      //      ColourSkidsUnder (DULLRED);

      ColourAll(BLACK);
      Show();

      Finish();

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // END OF THE NIGHT FLYING ROUTINE ////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      break; // end of run mode

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

      // 3. HueOneSparkleAll(PERCENT_OF_PIXELS_ON, HUE_1, FADE_SPEED)

      // This sparkles the whole heli with one hue (HUE_1).
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)

      // 4. ColourOneSparkleAll(PERCENT_OF_PIXELS_ON, COLOUR_1, FADE_SPEED)

      // This sparkles the whole heli with one colour (COLOUR_1).
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)

      // 5. ColourOneSparkleCanopyTailBoom(PERCENT_OF_PIXELS_ON, COLOUR_1, FADE_SPEED)

      // This sparkles the canopy and tail boom with one colour (COLOUR_1).
      // ALSO KEEPS THE TAIL FIN THAT SOLID COLOUR TO STOP IT FADING
      // PERCENT_OF_PIXELS_ON can be from 0.01 to 100
      // FADE_SPEED determines how fast the pixels fade to black (0= instant, 255= v.slow)


      HueTwoSparkleAll( 0.8, m, n, 200);
      ColourTail(BLACK);
      ColourSkids (BLACK);

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

      ColourAll (BLACK);
      Show();
      break; // end of stop mode

    case 4:   // demo mode when radio.mode=4

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // DEMO MODE //////////////////////////////////////////////////////////////////////////////////////////////////////////
      // CAN USE STATIC COLOURS OR DYNAMIC PATTERNS BUT NOT "UNTIL" FUNCTIONS   /////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      ColourAll (DULLGREY);
      Show();
      break; // end of demo mode

  } // end of switch case
} // end of loop

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
    radiomillis = radio.millisec[3] << 24 | (uint32_t)radio.millisec[2] << 16 | (uint32_t)radio.millisec[1] << 8 | (uint32_t)radio.millisec[0];
  }
}

void printout() // just for serial debugging
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
    RadioCheck();
    printout();
  }
}

void ColourCanopy(uint32_t colour) // set the whole canopy to a solid colour
{
  fill_solid( &(cstrip[0]), CTOTALPIXELS , colour );
}

void ColourTail(uint32_t colour)  // set the whole tail to a solid colour
{
  fill_solid( &(tstrip[0]), TTOTALPIXELS , colour );
}

void ColourSkids(uint32_t colour)  // set the whole skids to a solid colour
{
  fill_solid( &(sstrip[0]), STOTALPIXELS , colour );
}

void ColourAll(uint32_t colour) // set the whole heli to a solid colour and show it
{
  ColourCanopy(colour);
  ColourTail(colour);
  ColourSkids(colour);
  Show();
}

void ColourTailFin(uint32_t colour) // set the tail fin to a solid colour
{
  fill_solid( &(tstrip[TAILFINFIRST]), TAILFINLAST - TAILFINFIRST + 1 , colour );
}

void ColourTailBoom(uint32_t colour) // set the tail boom to a solid colour
{
  fill_solid( &(tstrip[BOOMFRONT]), BOOMREAR - BOOMFRONT + 1 , colour );
}

void ColourSkidsSide(uint32_t colour)  // set the side of the skids to a solid colour
{
  fill_solid( &(sstrip[SKIDSFIRST]), SKIDSLAST - SKIDSFIRST + 1 , colour );
}

void ColourSkidsUnder(uint32_t colour) // set the underside of the skids to a solic colour
{
  fill_solid( &(sstrip[UNDERFRONTFIRST]), UNDERFRONTLAST - UNDERFRONTFIRST + 1 , colour );
  fill_solid( &(sstrip[UNDERREARFIRST]), UNDERREARLAST - UNDERREARFIRST + 1 , colour );
}

void HueCanopy(uint8_t hue)
{
  fill_solid( &(cstrip[0]), CTOTALPIXELS , CHSV( hue, 255, 255) );
}

void HueTail(uint8_t hue)
{
  fill_solid( &(tstrip[0]), TTOTALPIXELS , CHSV( hue, 255, 255) );
}

void HueSkids(uint8_t hue)
{
  fill_solid( &(sstrip[0]), STOTALPIXELS , CHSV( hue, 255, 255) );
}

void HueTailFin(uint8_t hue)
{
  fill_solid( &(tstrip[TAILFINFIRST]), TAILFINLAST - TAILFINFIRST + 1 , CHSV( hue, 255, 255) );
}

void HueTailBoom(uint8_t hue)
{
  fill_solid( &(tstrip[BOOMFRONT]), BOOMREAR - BOOMFRONT + 1 , CHSV( hue, 255, 255) );
}

void HueSkidsSide(uint8_t hue)
{
  fill_solid( &(sstrip[SKIDSFIRST]), SKIDSLAST - SKIDSFIRST + 1 , CHSV( hue, 255, 255) );
}

void HueSkidsUnder(uint8_t hue)
{
  fill_solid( &(sstrip[UNDERFRONTFIRST]), UNDERFRONTLAST - UNDERFRONTFIRST + 1 , CHSV( hue, 255, 255) );
  fill_solid( &(sstrip[UNDERREARFIRST]), UNDERREARLAST - UNDERREARFIRST + 1 , CHSV( hue, 255, 255) );
}

void Show()
{
  FastLED.show();
}

void Finish()  // when this is reached it will hold until another mode is selected
{
  while (radiomillis < 1999999999)
  {
    RadioCheck();
    printout();
  }

}

void HueTwoSparkleCanopy(float howmany1, uint8_t hue1, uint8_t hue2, uint8_t fade)
{

  howmany1 *= 100;

  for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      if (random8() < 128) {
        cstrip[j].setHue(hue1);
      }
      else
      {
        cstrip[j].setHue(hue2);
      }
    }
  }

  FastLED.show();

  nscale8(cstrip, CTOTALPIXELS, fade);

}

void HueOneSparkleAll(float howmany1, uint8_t hue1, uint8_t fade)
{

  howmany1 *= 100;

  for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      cstrip[j].setHue(hue1);
    }
  }

  for (uint16_t j = 0; j < TTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      tstrip[j].setHue(hue1);
    }
  }


  for (uint16_t j = 0; j < STOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      sstrip[j].setHue(hue1);
    }
  }

  FastLED.show();

  nscale8(cstrip, CTOTALPIXELS, fade);
  nscale8(tstrip, TTOTALPIXELS, fade);
  nscale8(sstrip, STOTALPIXELS, fade);

}



void ColourOneSparkleCanopyTailBoom(float howmany1, uint32_t colour1, uint8_t fade)
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

  ColourTailFin(colour1);

  FastLED.show();

  nscale8(cstrip, CTOTALPIXELS, fade);
  nscale8(tstrip, TTOTALPIXELS, fade);


}


void ColourOneSparkleAll(float howmany1, uint32_t colour1, uint8_t fade)
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

void HueTwoSparkleAll(float howmany1, uint8_t hue1, uint8_t hue2, uint8_t fade)
{

  howmany1 *= 100;

  for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      if (random8() < 128) {
        cstrip[j].setHue(hue1);
      }
      else
      {
        cstrip[j].setHue(hue2);
      }
    }
  }

  for (uint16_t j = 0; j < TTOTALPIXELS; j++) {
    if (random16(10000) < howmany1) {
      if (random8() < 128) {
        tstrip[j].setHue(hue1);
      }
      else
      {
        tstrip[j].setHue(hue2);
      }
    }

  }

  for (uint16_t j = 0; j < STOTALPIXELS; j++) {

    if (random16(10000) < howmany1) {
      if (random8() < 128) {
        sstrip[j].setHue(hue1);
      }
      else
      {
        sstrip[j].setHue(hue2);
      }
    }
  }

  FastLED.show();

  nscale8(cstrip, CTOTALPIXELS, fade);
  nscale8(tstrip, TTOTALPIXELS, fade);
  nscale8(sstrip, STOTALPIXELS, fade);

}

void ColourOneSparkleCanopyTailBoomUntil(uint32_t waituntil, float howmany1, uint32_t colour1, uint8_t fade)
{
  while (radiomillis < waituntil)
  {
    RadioCheck();
    ColourOneSparkleCanopyTailBoom(howmany1, colour1, fade);
  }
}

void ColourOneSparkleAllUntil(uint32_t waituntil, float howmany1, uint8_t colour1, uint8_t fade)
{
  while (radiomillis < waituntil)
  {
    RadioCheck();
    ColourOneSparkleAll(howmany1, colour1, fade);
  }
}

void HueOneSparkleAllUntil(uint32_t waituntil, float howmany1, uint8_t hue1, uint8_t fade)
{
  while (radiomillis < waituntil)
  {
    RadioCheck();
    HueOneSparkleAll(howmany1, hue1, fade);
  }
}

void HueTwoSparkleAllUntil(uint32_t waituntil, float howmany1, uint8_t hue1, uint8_t hue2, uint8_t fade)
{
  while (radiomillis < waituntil)
  {
    RadioCheck();
    HueTwoSparkleAll(howmany1, hue1, hue2, fade);
  }
}
void HueTwoSparkleCanopyUntil(uint32_t waituntil, float howmany1, uint8_t hue1, uint8_t hue2, uint8_t fade)
{
  while (radiomillis < waituntil)
  {
    RadioCheck();
    HueTwoSparkleCanopy(howmany1, hue1, hue2, fade);
  }
}


void ColourMergeAllUntil (uint32_t until, uint32_t startcolour, uint32_t endcolour) { // merge from one solid colour to another on canopy, tail and skids

  // until = The radiomillis when this colour merge ends
  // startcolour = The starting RGB colour
  // endcolour = The ending RGB colour

  uint8_t rr = startcolour >> 16; //dismantle the colour into RGB components
  uint8_t gg = startcolour >> 8;
  uint8_t bb = startcolour;

  uint8_t r = endcolour >> 16; //dismantle the colour into RGB components
  uint8_t g = endcolour >> 8;
  uint8_t b = endcolour;

  RadioCheck();
  uint32_t starttime = radiomillis;
  uint32_t totalduration = until - radiomillis;
  while (radiomillis < until)

  {
    uint32_t elapsed = radiomillis - starttime;
    uint32_t fraction = (elapsed << 8) / totalduration; //elapsed*256/totalduration gives the 8 bit fraction
    uint8_t rrr = lerp8by8(rr, r, fraction); //interpolate between rr & r
    uint8_t ggg = lerp8by8(gg, g, fraction);
    uint8_t bbb = lerp8by8(bb, b, fraction);
    uint32_t colour = (uint32_t)rrr << 16 | (uint32_t)ggg << 8 | (uint32_t)bbb; //put the colour back together as 24bit RGB colour
    ColourCanopy(colour);
    ColourSkids(colour);
    ColourTail(colour);
    Show();
    RadioCheck();
  }

}

void HueMergeAllUntil (uint32_t until, uint8_t starthue, uint32_t endhue) { // merge from one solid hue to another on canopy, tail and skids

  // until = The radiomillis when this colour merge ends
  // starthue = The starting 8 bit hue
  // endhue = The ending 8 bit hue

  RadioCheck();
  uint32_t starttime = radiomillis;
  uint32_t totalduration = until - radiomillis;
  while (radiomillis < until)

  {
    uint32_t elapsed = radiomillis - starttime;
    uint32_t fraction = (elapsed << 8) / totalduration; //elapsed*256/totalduration gives the 8 bit fraction
    uint8_t huey = lerp8by8(starthue, endhue, fraction); //interpolate between starthue and endhue

    HueCanopy(huey);
    HueSkids(huey);
    HueTail(huey);
    Show();
    RadioCheck();
  }

}

void ColourMergeAllSparklingCanopyTailBoomUntil (uint32_t until, float howmany1, uint32_t startcolour, uint32_t endcolour, uint8_t fade) { // merge from one colour to another, but with the canopy and tail boom sparkling

  // until = The radiomillis when this colour merge ends
  // startcolour = The starting RGB colour
  // endcolour = The ending RGB colour

  howmany1 *= 100;
  /* this is what it is going to change to. To stop using a float.
    uint16_t howmany;

    if (howmany1>100) {
    howmany=100;
    }
    else
    {
    howmany=howmany1*100;
    }
  */

  uint8_t rr = startcolour >> 16; //dismantle the colour into RGB components
  uint8_t gg = startcolour >> 8;
  uint8_t bb = startcolour;

  uint8_t r = endcolour >> 16; //dismantle the colour into RGB components
  uint8_t g = endcolour >> 8;
  uint8_t b = endcolour;

  RadioCheck();
  uint32_t starttime = radiomillis;
  uint32_t totalduration = until - radiomillis;
  while (radiomillis < until)
  {
    uint32_t elapsed = radiomillis - starttime;
    uint32_t fraction = (elapsed << 8) / totalduration; //elapsed*256/totalduration gives the 8 bit fraction
    uint8_t rrr = lerp8by8(rr, r, fraction); //interpolate between rr & r
    uint8_t ggg = lerp8by8(gg, g, fraction);
    uint8_t bbb = lerp8by8(bb, b, fraction);
    uint32_t colour = (uint32_t)rrr << 16 | (uint32_t)ggg << 8 | (uint32_t)bbb; //put the colour back together as 24bit RGB colour

    for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
      if (random16(10000) < howmany1) {
        cstrip[j] = colour;
      }
    }

    for (uint16_t j = BOOMFRONT; j <= BOOMREAR; j++) {
      if (random16(10000) < howmany1) {
        tstrip[j] = colour;
      }
    }

    ColourTailFin(colour);
    ColourSkids(colour);
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

void SpectrumTop(uint32_t until, uint32_t colour1, uint32_t colour2, uint8_t fade) {

uint8_t tracker;
  while (radiomillis < until)
  {
    tracker+= 1;
    if (tracker==3) {
      tracker=0;
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
        if (rightspectrumtop[i] > 0 && tracker==0) {
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
        if (leftspectrumtop[i] > 0 && tracker==0) {
          leftspectrumtop[i] -= 1;
        }
      }
      cstrip[(leftcanopy [i + 1][leftspectrumtop[i]])] = colour2;

    }
    // show the pixels
    FastLED.show();
    //fade
    nscale8(cstrip, CTOTALPIXELS, fade);

    RadioCheck();
  }
}

