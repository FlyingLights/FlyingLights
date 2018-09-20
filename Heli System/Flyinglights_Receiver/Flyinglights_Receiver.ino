///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CUSTOMISE THE LINES BELOW TO MATCH YOUR SETUP ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// The three lines below refer to the number of individually referenced pixels on the heli
// see the Wiki page for more details about how to calculate this, especially on the tail
// and skids where the number of individually referenced pixels is less than the actual number
// Finally it is probably best to add one to these numbers as the last pixel can sometimes
// exhibit odd behaviour.
#define CTOTALPIXELS 342 //Number of LEDs on the canopy
#define STOTALPIXELS 23 //Number of (individually referenced) LEDs on the skids
#define TTOTALPIXELS 47 //Number of (individually referenced) LEDs on the tail boom and fin

// this defines the number of ROWS (horizontal strips) and
// COLUMNS (number of LEDS on the longest strip) on your heli canopy
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
// You can use the Excel file leftcanopy_array_maker.xlsx to make this
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
// You can use the Excel file rightcanopy_array_maker.xlsx to make this
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

//initialise the radio
RH_RF95 rf95(RFM95_CS, RFM95_INT);

//define the pins that the LED strips are connected to on the Feather board
#define CPIN 13  // THE PIN NUMBER ON THE BOARD THAT THE CANOPY DATA WIRE IS CONNECTED TO
#define SPIN 11 // THE PIN NUMBER ON THE BOARD THAT THE SKIDS DATA WIRE IS CONNECTED TO
#define TPIN 10  // THE PIN NUMBER ON THE BOARD THAT THE TAIL DATA WIRE IS CONNECTED TO

// set up some RGB colours for easy reference. This is about all you need!
const CRGB blue = CRGB(0x0000FF);
const CRGB red = CRGB(0xFF0000);
const CRGB green = CRGB(0x00FF00);
const CRGB magenta = CRGB(0xFF00FF);
const CRGB cyan = CRGB(0x00FFFF);
const CRGB yellow = CRGB(0xFFFF00);
const CRGB orange = CRGB(0xFF4500);
const CRGB pink = CRGB(0xDC143C);
const CRGB dullyellow = CRGB(0x222200);
const CRGB dullred = CRGB(0x220000);
const CRGB dullgreen = CRGB(0x002200);
const CRGB dullcyan = CRGB(0x002222);
const CRGB dullmagenta = CRGB(0x220022);
const CRGB dullblue = CRGB(0x000022);
const CRGB dullorange = CRGB(0x220900);
const CRGB dullpink = CRGB(0x1D0308);
const CRGB black = CRGB(0x000000);
const CRGB white = CRGB(0xFFFFFF);
const CRGB lightgrey = CRGB(0x222222);
const CRGB grey = CRGB(0x101010);
const CRGB dullgrey = CRGB(0x060606);

#define DEMO_MODE 0 // used for clarity to pass 0 into functions when in demo or ready modes

CRGB cstrip[CTOTALPIXELS]; //setup the array for the canopy leds
CRGB sstrip[STOTALPIXELS]; //setup the array for the skid leds
CRGB tstrip[TTOTALPIXELS]; //setup the array for the tail leds

// this stores 5x5 sprites for characters, numbers and other shapes. Stored by (ASCII code-32) so the first one is ASCII code 32
uint8_t sprites[][6] {{3, 0, 0, 0, 0, 0}, {1, 23, 0, 0, 0, 0}, {3, 3, 0, 3, 0, 0}, {5, 10, 31, 10, 31, 10}, {5, 10, 21, 10, 21, 10}, {5, 21, 10, 21, 10, 21}, {5, 31, 31, 31, 31, 31}, {1, 1, 0, 0, 0, 0}, {5, 31, 0, 31, 0, 31}, {5, 21, 21, 21, 21, 21}, {5, 4, 4, 4, 4, 4}, {5, 4, 4, 31, 4, 4}, {1, 24, 0, 0, 0, 0}, {5, 4, 4, 4, 4, 4}, {1, 16, 0, 0, 0, 0}, {5, 16, 8, 4, 2, 1}, {5, 31, 17, 17, 17, 31}, {5, 17, 17, 31, 16, 16}, {5, 25, 21, 21, 21, 22}, {5, 21, 21, 21, 21, 10}, {5, 15, 8, 8, 31, 8}, {5, 23, 21, 21, 21, 9}, {5, 14, 21, 21, 21, 9}, {5, 1, 1, 25, 5, 3}, {5, 10, 21, 21, 21, 10}, {5, 18, 21, 21, 21, 14}, {1, 10, 0, 0, 0, 0}, {1, 26, 0, 0, 0, 0}, {4, 21, 21, 10, 10, 0}, {5, 10, 10, 10, 10, 10}, {4, 10, 10, 21, 21, 0}, {5, 1, 1, 21, 5, 7}, {5, 31, 17, 21, 17, 31}, {5, 28, 10, 9, 10, 28}, {5, 31, 21, 21, 21, 10}, {5, 14, 17, 17, 17, 10}, {5, 31, 17, 17, 17, 14}, {5, 31, 21, 21, 17, 17}, {5, 31, 5, 5, 1, 1}, {5, 14, 17, 17, 21, 29}, {5, 31, 4, 4, 4, 31}, {5, 17, 17, 31, 17, 17}, {5, 8, 16, 16, 16, 15}, {5, 31, 4, 4, 10, 17}, {5, 31, 16, 16, 16, 16}, {5, 31, 2, 4, 2, 31}, {5, 31, 2, 4, 8, 31}, {5, 14, 17, 17, 17, 14}, {5, 31, 5, 5, 5, 2}, {5, 14, 17, 17, 25, 30}, {5, 31, 5, 5, 5, 26}, {5, 18, 21, 21, 21, 9},
  {5, 1, 1, 31, 1, 1}, {5, 15, 16, 16, 16, 15}, {5, 7, 8, 16, 8, 7}, {5, 15, 16, 12, 16, 15}, {5, 17, 10, 4, 10, 17}, {5, 1, 2, 28, 2, 1}, {5, 17, 25, 21, 19, 17}, {2, 31, 17, 0, 0, 0}, {5, 1, 2, 4, 8, 16}, {2, 17, 31, 0, 0, 0}, {3, 2, 1, 2, 0, 0}, {3, 0, 0, 0, 0, 0}
};
uint8_t mode;  //mode 1=run,2=ready,3=stop,4=demo

//this is the data structure for the info that comes over the radio
struct dataStruct {
  uint8_t millisec[3]; //millisecond timer is split up into 4 bytes
  uint8_t spectrum[7]; //spectrum analyser over seven channels
} radio;

// radiomillis is the millisecond signal being sent over the radio. It is used
// during run mode but set to 15000000 when in other modes
uint32_t radiomillis;

// used to put a bright spot on the top of the spectrumtop function bars
uint8_t leftspectrumtop[7];
uint8_t rightspectrumtop[7];
// leftmax and rightmax store where the last actual pixel is on each row rather than a 999 blank. Used for spectrumtop function
uint8_t leftmax[7];
uint8_t rightmax[7];

uint32_t x;  //start time for repeating loops
uint32_t y;  //end time for repeating loops
uint32_t z;  //repeat interval for repeating loops

// This variable is used for the starlights function. One variable for each row.
uint8_t starlights[ROWS];

uint8_t n; //just a handy reusable global 8bit unsigned integer!
uint8_t m; //just a handy reusable global 8bit unsigned integer!
bool on_off; // a handy reuseable global boolean variable!

// this is a variable that triggers the functions to only execute once in demo & ready modes (when it is TRUE)
// in run mode it is set to FALSE and the functions will execute until a particular time is reached
bool runthrough;


//Predefined Palettes
/// Cloudy color pallete: CloudColors_p
/// Lava colors: LavaColors_p
/// Ocean colors, blues and whites: OceanColors_p
/// Forest colors, greens: ForestColors_p
/// HSV Rainbow: RainbowColors_p
/// HSV Rainbow colors with alternatating stripes of black: RainbowStripeColors_p
/// HSV color ramp: blue purple ping red orange yellow (and back): PartyColors_p
/// Approximate "black body radiation" palette: HeatColors_p


DEFINE_GRADIENT_PALETTE( CandyStore_p ) {
  0, 255, 255, 255,
  45,   7, 12, 255,
  112, 227,  1, 127,
  112, 227,  1, 127,
  140, 255, 255, 255,
  155, 227,  1, 127,
  196,  45,  1, 99,
  255, 255, 255, 255
};

DEFINE_GRADIENT_PALETTE( JungleBoogie_p ) {
  0,   0, 12,  0,
  61, 153, 239, 112,
  127,   0, 12,  0,
  165, 106, 239,  2,
  196, 167, 229, 71,
  229, 106, 239,  2,
  255,   0, 12,  0
};

DEFINE_GRADIENT_PALETTE( Blellow_p ) {
  0,   0,  0,  0,
  66,  57, 227, 233,
  96, 255, 255,  8,
  124, 255, 255, 255,
  153, 255, 255,  8,
  188,  57, 227, 233,
  255,   0,  0,  0
};

DEFINE_GRADIENT_PALETTE( Xmas_p ) {
  0,   0, 12,  0,
  40,   0, 55,  0,
  66,   1, 117,  2,
  77,   1, 84,  1,
  81,   0, 55,  0,
  119,   0, 12,  0,
  153,  42,  0,  0,
  181, 121,  0,  0,
  204, 255, 12,  8,
  224, 121,  0,  0,
  244,  42,  0,  0,
  255,  42,  0,  0
};

DEFINE_GRADIENT_PALETTE( LaFrance_p ) {
  0,   0,  0, 45,
  71,   7, 12, 255,
  76,  75, 91, 255,
  76, 255, 255, 255,
  81, 255, 255, 255,
  178, 255, 255, 255,
  179, 255, 55, 45,
  196, 255,  0,  0,
  255,  42,  0,  0
};

DEFINE_GRADIENT_PALETTE( ForestPool_p ) {
  0,   2,  5, 11,
  30,  12, 10, 87,
  48,  61, 124, 201,
  63,  10, 54, 111,
  81,   1,  8, 68,
  117,  88, 84, 247,
  145,   1, 12,  9,
  175,  61, 130, 43,
  196,  31, 146,  6,
  234,   4, 31, 10,
  255,   0,  1,  1
};

DEFINE_GRADIENT_PALETTE( Teddybear_p ) {
  0, 255, 255, 45,
  43, 208, 93,  1,
  137, 224,  1, 242,
  181, 159,  1, 29,
  255,  63,  4, 68
};

DEFINE_GRADIENT_PALETTE( PurpleNight_p ) {
  0,   0,  0,  0,
  66,  20,  4, 45,
  132, 121, 20, 255,
  180, 179, 73, 255,
  228, 255, 164, 255,
  241, 255, 207, 255,
  255, 255, 255, 255
};

DEFINE_GRADIENT_PALETTE( Tangerine_p ) {
  0,   0,  0,  0,
  14,   1,  1,  0,
  29,   6,  1,  0,
  57,  33,  3,  1,
  85,  91,  9,  1,
  114, 155, 22,  1,
  144, 242, 43,  1,
  165, 244, 70,  5,
  186, 249, 105, 17,
  220, 252, 171, 93,
  255, 255, 255, 255
};

DEFINE_GRADIENT_PALETTE( ForestFlowers_p ) {
  0,   2, 37, 16,
  51,   2, 37, 16,
  51,   3, 62, 11,
  102,   3, 62, 11,
  102,  42, 68,  6,
  153,  42, 68,  6,
  153, 109, 112,  2,
  204, 109, 112,  2,
  204, 242, 100,  0,
  255, 242, 100,  0
};

DEFINE_GRADIENT_PALETTE( SpookyBlue_p ) {
  0,  5, 5, 30,
  101,  5, 5, 30,
  102, 199, 213, 252,
  122, 199, 213, 252,
  126,  5, 5, 30,
  151,  5, 5, 30,
  152,  39, 34, 245,
  177,  39, 34, 245,
  178,  5, 5, 30,
  203,  5, 5, 30,
  204,  24, 246, 140,
  227,  24, 246, 140,
  229,  5, 5, 30,
  252,  5, 5, 30,
  255,   5, 5, 30
};

DEFINE_GRADIENT_PALETTE( GoldenRain_p ) {
  0,   0,  0,  0,
  124, 210, 221,  1,
  255, 255, 255, 255
};

DEFINE_GRADIENT_PALETTE( LiquidGold_p ) {
  0, 255, 255,  8,
  73, 150, 16,  1,
  153, 182,  1,  1,
  244, 255, 255,  8,
  255, 255, 255,  8
};

DEFINE_GRADIENT_PALETTE( ColouredLight_p ) {
  0, 255, 255, 255,
  5, 255, 255, 255,
  43, 255, 12,  8,
  51, 255, 255, 255,
  68, 220, 47,  1,
  89, 255, 255, 255,
  109, 255, 255,  8,
  127, 255, 255, 255,
  145,   3, 178,  3,
  160, 255, 255, 255,
  178,   7, 12, 255,
  201, 255, 255, 255,
  219, 121,  0, 125,
  244, 255, 255, 255,
  255, 255, 255, 255
};

DEFINE_GRADIENT_PALETTE( GoddessMoon_p ) {
  0,   2,  3, 20,
  40,   2,  3, 27,
  76,   2,  3, 19,
  101,   5,  2, 73,
  137,   5,  2, 73,
  158, 255, 255, 174,
  175,  11,  4, 127,
  221,   5,  2, 73,
  249,   2,  3, 27,
  255,   2,  3, 27
};

DEFINE_GRADIENT_PALETTE( Goldfish_p ) {
  0, 186, 223, 245,
  28, 190, 223, 214,
  58, 222, 233, 228,
  73, 222, 233, 228,
  89, 186, 36,  5,
  101, 206, 73, 14,
  114, 157, 13,  1,
  124, 206, 73, 14,
  135,  46,  2,  1,
  147, 157, 13,  1,
  163, 210, 25,  1,
  175, 222, 233, 228,
  196, 177, 221, 240,
  221, 186, 221, 192,
  255, 206, 229, 250
};

DEFINE_GRADIENT_PALETTE( SubtleZebra_p ) {
  0,   0,  0,  0,
  20, 255, 255, 255,
  53, 121, 136, 125,
  81,   1,  2,  1,
  96,   1,  2,  1,
  130,  42, 55, 45,
  145,  42, 55, 45,
  165, 255, 255, 255,
  183,  54, 62, 52,
  211,  54, 62, 52,
  229,  54, 62, 52,
  242, 121, 136, 125,
  255,   0,  0,  0
};

DEFINE_GRADIENT_PALETTE( NightStripes_p ) {
  0,   1,  1,  1,
  51,   1,  1,  1,
  56, 255, 255, 255,
  94, 255, 255, 255,
  101,   1,  1,  1,
  135,   1,  1,  1,
  153,  18,  7, 230,
  255, 224, 10,  9
};

DEFINE_GRADIENT_PALETTE( Wasp_p ) {
  0,   1,  1,  1,
  40, 255, 255,  8,
  84,   1,  1,  1,
  99,   1,  1,  1,
  119, 255, 255,  8,
  142,   1,  1,  1,
  155,   1,  1,  1,
  198, 255, 255,  8,
  242,   1,  1,  1,
  255,   1,  1,  1
};

DEFINE_GRADIENT_PALETTE( Xanadu_p ) {
  0, 118, 161, 226,
  5, 255, 255, 45,
  15, 252, 203, 156,
  53,  79,  1, 162,
  94,  67,  1,  7,
  132,   1, 55, 156,
  173,   1, 127, 61,
  211,  39, 45, 72,
  255, 118, 161, 226
};

DEFINE_GRADIENT_PALETTE( RedNight_p ) {
  0,   0,  0,  0,
  124, 213,  1,  8,
  255, 255, 255, 255
};

DEFINE_GRADIENT_PALETTE( BlueBurst_p ) {
  0,   0,  0,  10,
  255, 40, 40, 255
};

DEFINE_GRADIENT_PALETTE( CyanLight_p ) {
  0,   0,  0,  0,
  127,   3, 178, 151,
  255, 255, 255, 255
};

DEFINE_GRADIENT_PALETTE( GreenLight_p ) {
  0,   0,  0,  0,
  127,  27, 248,  1,
  255, 255, 255, 255
};

DEFINE_GRADIENT_PALETTE( GrassHeart_p ) {
  0,   1, 199,  1,
  56,   6, 93,  7,
  84, 192, 47, 65,
  119, 232, 159, 203,
  155, 192, 47, 65,
  206,   6, 93,  7,
  255,   1, 199,  1
};

DEFINE_GRADIENT_PALETTE( Tertiary_p ) {
  0,   0,  1, 44,
  63,  20,  1, 14,
  127, 120,  1,  2,
  191, 177, 66,  1,
  255, 247, 255,  0
};

DEFINE_GRADIENT_PALETTE( Topographic_p ) {
  0, 255, 255, 255,
  17, 215, 187, 245,
  33, 153, 146, 252,
  51,  87, 130, 250,
  68,  39, 139, 221,
  84,  14, 169, 160,
  102,   5, 211, 83,
  119,   5, 244, 23,
  135,  13, 209,  2,
  153,  30, 122,  1,
  170,  41, 55,  0,
  186,  37, 17,  1,
  204,  22,  3,  1,
  221,   7,  1,  1,
  237,   1,  1,  1,
  255,   0,  0,  0
};


void setup()
{

  float frequency = 433 + (FREQUENCY_BAND * 0.2); // set the frequency

  //put the value of COLUMNS into the variables in starlights[] array to get it ready
  for (uint8_t f = 0; f < ROWS; f ++ ) {
    starlights[f] = COLUMNS;
  }
  // set the unique address of this receiver
  rf95.setThisAddress(UNIQUE_ADDRESS);

  //setup the FastLED strips with the correct led type, pin and array reference
  FastLED.addLeds<WS2812, CPIN, GRB>(cstrip, CTOTALPIXELS);
  FastLED.addLeds<WS2812, TPIN, GRB>(tstrip, TTOTALPIXELS);
  FastLED.addLeds<WS2812, SPIN, GRB>(sstrip, STOTALPIXELS);

  // only necessary for debugging
  Serial.begin(115200);

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

    //serial print just for debugging
    Serial.print(f);
    Serial.print(" leftmax:");
    Serial.print(leftmax[f]);
    Serial.print(" rightmax:");
    Serial.println(rightmax[f]);
  }


  if (!rf95.init())
    Serial.println("init failed");

  rf95.setFrequency(frequency);
  rf95.setModemConfig(RH_RF95::Bw500Cr45Sf128);
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

void Flash(CRGB colour) // set the whole heli to a solid colour
{

  if (radiomillis < 14999999)
  {
    Canopy(colour);
    Tail(colour);
    Skids(colour);
    Show();
    delay(10);
  }
}

void LongFlash(CRGB colour) // set the whole heli to a solid colour
{

  if (radiomillis < 14999999)
  {
    Canopy(colour);
    Tail(colour);
    Skids(colour);
    Show();
    delay(70);
  }
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

void EvenRows(CRGB colouration) {
  Canopy(black);
  for (int j = 0; j < COLUMNS; j++) {
    for (int q = 0; q < ROWS; q = q + 2) {
      cstrip[(leftcanopy [q][j])] = colouration;
      cstrip[(rightcanopy [q][j])] = colouration;
    }
  }
}

void OddRows(CRGB colouration) {
  Canopy(black);
  for (int j = 0; j < COLUMNS; j++) {
    for (int q = 1; q < ROWS; q = q + 2) {
      cstrip[(leftcanopy [q][j])] = colouration;
      cstrip[(rightcanopy [q][j])] = colouration;
    }
  }
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

void RandomCol() {

  m = m + random(55, 200);
  Canopy(CHSV(m, 255, 255));
  TailBoom(CHSV(m + 60, 255, 255));
  SkidsUnder(CHSV(m + 120, 255, 255));
  SkidsSide(CHSV(m + 180, 255, 255));
  TailFin(CHSV(m + 180, 255, 255));

}


void SparkleCanopyTailBoom(uint32_t waituntil, float howmany1, CRGB colour1, uint8_t fade)
{

  howmany1 *= 100;
  while (radiomillis < waituntil || runthrough)
  {


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

    RadioCheck();
    if (runthrough) {
      break;
    }

  }
}

void SparkleAll(uint32_t waituntil, float howmany1, CRGB colour1, uint8_t fade)
{

  howmany1 *= 100;
  while (radiomillis < waituntil || runthrough)
  {

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

    RadioCheck();
    if (runthrough) {
      break;
    }
  }
}



void TwoSparkleAll(uint32_t waituntil, float howmany1, CRGB colour1, CRGB colour2, uint8_t fade)
{

  howmany1 *= 100;
  while (radiomillis < waituntil || runthrough)
  {


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

    RadioCheck();

    if (runthrough) {
      break;
    }
  }
}

void TwoSparkleCanopy(uint32_t waituntil, float howmany1, CRGB colour1, CRGB colour2, uint8_t fade)
{

  howmany1 *= 100;
  while (radiomillis < waituntil || runthrough)
  {


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

    FastLED.show();
    nscale8(cstrip, CTOTALPIXELS, fade);

    RadioCheck();
    if (runthrough) {
      break;
    }
  }
}

void TwoSparkleCanopyTail(uint32_t waituntil, float howmany1, CRGB colour1, CRGB colour2, uint8_t fade)
{

  howmany1 *= 100;
  while (radiomillis < waituntil || runthrough)
  {


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

    FastLED.show();
    nscale8(cstrip, CTOTALPIXELS, fade);
    nscale8(tstrip, TTOTALPIXELS, fade);

    RadioCheck();

    if (runthrough) {
      break;
    }
  }
}


void PaletteSparkleAll(uint32_t waituntil, float howmany1, CRGBPalette16 palette1, uint8_t fade)
{

  howmany1 *= 100;
  while (radiomillis < waituntil || runthrough)
  {

    for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
      if (random16(10000) < howmany1) {
        cstrip[j] = ColorFromPalette(palette1, random8());
      }
    }

    for (uint16_t j = 0; j < TTOTALPIXELS; j++) {
      if (random16(10000) < howmany1) {
        tstrip[j] = ColorFromPalette(palette1, random8());
      }
    }

    for (uint16_t j = 0; j < STOTALPIXELS; j++) {

      if (random16(10000) < howmany1) {
        sstrip[j] = ColorFromPalette(palette1, random8());
      }
    }

    FastLED.show();
    nscale8(cstrip, CTOTALPIXELS, fade);
    nscale8(tstrip, TTOTALPIXELS, fade);
    nscale8(sstrip, STOTALPIXELS, fade);

    RadioCheck();

    if (runthrough) {
      break;
    }
  }
}


void PaletteSparkleCanopy(uint32_t waituntil, float howmany1, CRGBPalette16 palette1, uint8_t fade)
{

  howmany1 *= 100;
  while (radiomillis < waituntil || runthrough)
  {

    for (uint16_t j = 0; j < CTOTALPIXELS; j++) {
      if (random16(10000) < howmany1) {
        cstrip[j] = ColorFromPalette(palette1, random8());
      }
    }

    FastLED.show();
    nscale8(cstrip, CTOTALPIXELS, fade);

    RadioCheck();

    if (runthrough) {
      break;
    }
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


void MergeCanopyTailBoom (uint32_t until, CRGB startcolour, CRGB endcolour) { // merge from one solid colour to another on canopy, tail and skids

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
    TailBoom(newcolour);
    Show();

    RadioCheck();
  }
}



void MergeCrazyBars (uint32_t until, CRGB startcolour, CRGB endcolour) { // merge from one solid colour to another on canopy, tail and skids

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

    if (on_off) {
      EvenRows(newcolour);
      TailBoom(black);
    }
    else
    {
      OddRows(newcolour);
      TailBoom(newcolour);
    }
    on_off = !on_off;

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

  while (radiomillis < until || runthrough)
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
    if (runthrough) {
      break;
    }
  }
}

// Spectrum analyser function for the canopy
void SpectrumTwoColour(uint32_t until, CRGB colour1, CRGB colour2) {

  while (radiomillis < until || runthrough)
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
    if (runthrough) {
      break;
    }
  }
}

void SpectrumTop(uint32_t until, CRGB colour1, CRGB colour2, uint8_t fade) {

  uint8_t tracker;
  while (radiomillis < until || runthrough)
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

    RadioCheck();

    if (runthrough) {
      break;
    }
  }
}

void Starlights(uint32_t until, CRGB colour, uint8_t fade, uint8_t wait) {

  while (radiomillis < until || runthrough)
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
    if (runthrough) {
      break;
    }

  }

}

void ReverseStarlights(uint32_t until, CRGB colour, uint8_t fade, uint8_t wait) {

  while (radiomillis < until || runthrough)
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
    if (runthrough) {
      break;
    }
  }

}


void PaletteCycleAll(uint32_t until, CRGBPalette16 palette1, uint8_t fastness) {

  while (radiomillis < until || runthrough)
  {

    m = m + fastness;
    CRGB colour1 = ColorFromPalette(palette1, m);
    Canopy(colour1);
    Skids(colour1);
    Tail(colour1);

    // show the pixels
    FastLED.show();

    //check the radio
    RadioCheck();
    if (runthrough) {
      break;
    }
  }

}


void ShiftingPaletteCanopy(uint32_t until, CRGBPalette16 palette1, uint8_t shiftyh, uint8_t shiftyv, uint8_t fastness) {

  while (radiomillis < until || runthrough)
  {

    m = m + fastness;

    for (int j = 0; j < COLUMNS; j++) {
      for (int q = 0; q < ROWS; q++) {
        cstrip[(leftcanopy [q][j])] = ColorFromPalette(palette1, m + (j * shiftyh) + (q * shiftyv));
        cstrip[(rightcanopy [q][j])] = ColorFromPalette(palette1, m + (j * shiftyh) + (q * shiftyv));
      }
    }

    // show the pixels
    FastLED.show();

    //check the radio
    RadioCheck();
    if (runthrough) {
      break;
    }
  }

}


void Strobe(uint32_t until, CRGB colour1) {

  while (radiomillis < until || runthrough)
  {

    Canopy(colour1);
    Tail(colour1);
    Skids(colour1);

    Show();

    delay(5);
    Canopy(black);
    Tail(black);
    Skids(black);

    Show();
    delay(45);

    //check the radio
    RadioCheck();
    if (runthrough) {
      break;
    }
  }

}


void ShiftingTwoSparkle() {

  TwoSparkleAll(0, 0.8, CHSV(m, 255, 255), CHSV(n, 255, 255), 200);

  Tail(black);
  Skids (black);

  if (m % 10 == 0) {
    n += 1;
  }
  m += 1;

}

void BeatCalculator(uint32_t xx, uint32_t yy, uint32_t zz) {
  z = (yy - xx) / zz;
  x = xx + (z);
  y = yy + (z / 10);
}

void LittleBlock (int8_t row, int8_t column,  CRGB colour) {
  for (int8_t rows = 0; rows < 3; rows++)
  {
    for (int8_t columns = 0; columns < 4; columns++)
    {
      int8_t east = column + columns;
      int8_t south = row + rows;
      if (east >= 0 && south >= 0 && east < COLUMNS && south < ROWS) {
        cstrip[(leftcanopy [south][east])] = colour;
        cstrip[(rightcanopy [south][east])] = colour;
      }
    }
  }
  Show();
}


void BigBlock (int8_t row, int8_t column,  CRGB colour) {
  for (int8_t rows = 0; rows < 6; rows++)
  {
    for (int8_t columns = 0; columns < 8; columns++)
    {
      int8_t east = column + columns;
      int8_t south = row + rows;
      if (east >= 0 && south >= 0 && east < COLUMNS && south < ROWS) {
        cstrip[(leftcanopy [south][east])] = colour;
        cstrip[(rightcanopy [south][east])] = colour;
      }
    }
  }
  Show();
}


void PaletteStrobe(uint32_t until, CRGBPalette16 palette1) {

  while (radiomillis < until || runthrough)
  {

    Canopy(ColorFromPalette(palette1, random8()));
    Tail(ColorFromPalette(palette1, random8()));
    Skids(ColorFromPalette(palette1, random8()));

    Show();

    delay(5);
    Canopy(black);
    Tail(black);
    Skids(black);

    Show();
    delay(45);

    //check the radio
    RadioCheck();
    if (runthrough) {
      break;
    }
  }

}





void DiscoPalette (uint32_t until, CRGBPalette16 palette1, uint8_t fade, uint8_t slowness) { // Disco effect based on a palette

  while (radiomillis < until || runthrough)
  {

    LittleBlock (random8(ROWS), random8(COLUMNS), ColorFromPalette(palette1, random8()));
    BigBlock (random8(ROWS), random8(COLUMNS), ColorFromPalette(palette1, random8()));
    Show();
    nscale8(cstrip, CTOTALPIXELS, fade);
    delay(slowness);
    RadioCheck();
    if (runthrough) {
      break;
    }
  }
}


void SpectrumFire (uint32_t until, CRGBPalette16 palette1, uint8_t fade, uint8_t slowness) {

  while (radiomillis < until || runthrough)
  {

    //run across the bars of the spectrum analyser
    for (uint16_t i = 0; i < 7; i++) {

      // work out the HEIGHT of the HORIZONTAL bars for each channel and put that in y
      uint16_t height = (ROWS * radio.spectrum[i]) >> 9;
      CRGB colourvariable = ColorFromPalette(palette1, radio.spectrum[i]);
      // run UP the bar
      for (uint16_t j = 0; j <= height; j++) {

        //work out what the pixel number is

        for (uint8_t f = 3; f <= 6; f++) {

          uint8_t east = (i * 5) + f ;

          cstrip[(leftcanopy [j + 4][east])] = colourvariable;
          cstrip[(leftcanopy [4 - j][east])] = colourvariable;
          cstrip[(rightcanopy [j + 4][east])] = colourvariable;
          cstrip[(rightcanopy [4 - j][east])] = colourvariable;
        }
      }
    }

    Show();
    nscale8(cstrip, CTOTALPIXELS, fade);

    delay(slowness);
    RadioCheck();
    if (runthrough) {
      break;
    }
  }
}

void SpriteBothSides (uint8_t ascii, int16_t row, int16_t column,  CRGB colour) {
  if (ascii > 95) {  // if it is greater than an underscore then set it to 0, which will appear as a blank
    ascii = 0;
  }
  else if (ascii < 32) // if it is less than 32 then make it 0, which will appear as a blank space.
  {
    ascii = 0;
  }
  else {
    ascii = ascii - 32; //take 32 off the number to match with my array which starts with 0 = blank space = ascii 32
  }


  uint8_t width = sprites[ascii][0]; //the first byte in each subarray stores the width of the character

  for (uint8_t place = 0; place < width; place++) //run through the width of the sprite/character
  {

    uint8_t reading = sprites[ascii][place + 1];

    int16_t east = column + place;
    if (east >= COLUMNS ) {  //if it is off the right of the canopy
      break;
    }
    for (int16_t k = 0; k < 5; k++) //characters are 5 pixels high. Increase the number here for higher number of pixels
    {
      int16_t south = k + row;
      if (south >= ROWS) {  //if it is off the bottom of the canopy
        break;
      }
      if (bitRead(reading, k) == 1 && east >= 0 && south >= 0) {  //if it is a pixel and it is not off the top or left of the canopy
        cstrip[(leftcanopy [south][east])] = colour;
        cstrip[(rightcanopy [south][COLUMNS - east])] = colour;
      }
    }
  }
  m = width; //return the width in the global uint8_t m
}







void ScrollText(char text[], uint8_t row) {

  if (mode !=3) {

    do
    {
      if (mode == 2 | mode == 4) {
        runthrough = true;
      }


      CRGB colour = white;
      int16_t firstcolumn = COLUMNS;
      int16_t place;
      int16_t endplace = COLUMNS;
      uint8_t length = strlen(text);
      Serial.print("strlen:");
      Serial.println(length);
      while (endplace > 0) {
        place = firstcolumn;



        for (uint8_t f = 0; f < length; f++) {
          uint8_t ff = text[f];


          if (ff > 95) // all the lower case letters and other stuff I don't use are >95
          {
            if (ff == 114) {
              colour = red;  //r goes to red
            }
            if (ff == 115) {
              colour = dullred;  //d goes to dullred
            }
            else if (ff == 103) {
              colour = green; //g goes to green
            }
            else if (ff == 104) {
              colour = dullgreen; //h goes to dullgreen
            }
            else if (ff == 98) {
              colour = blue; //b goes to blue
            }
            else if (ff == 97) {
              colour = dullblue; //a goes to dullblue
            }
            else if (ff == 121) {
              colour = yellow; //y goes to yellow
            }
            else if (ff == 122) {
              colour = dullyellow; //z goes to dullyellow
            }
            else if (ff == 109) {
              colour = magenta; //m goes to magenta
            }
            else if (ff == 99) {
              colour = cyan; //c goes to cyan
            }
            else if (ff == 100) {
              colour = cyan; //d goes to dullcyan
            }
            else if (ff == 119) {
              colour = white; //w goes to white
            }
            else if (ff == 116) {
              colour = lightgrey; //t goes to lightgrey
            }
            else if (ff == 117) {
              colour = grey; //u goes to grey
            }
            else if (ff == 118) {
              colour = dullgrey; //v goes to dullgrey
            }
            else if (ff == 111) {
              colour = orange; //o goes to orange
            }
            else if (ff == 111) {
              colour = orange; //o goes to orange
            }


          }
          else {
            SpriteBothSides (ff, row, place, colour);
            place = place + m + 2;
            Serial.print("m:");
            Serial.print(m);
          }
        }

        Show();
        Canopy(black);
        endplace = place;

        firstcolumn--;
        Serial.print(" endplace:");
        Serial.println(endplace);
      }

    } while (!runthrough);
  }
}

void RainbowCanopyTailBoom(uint32_t until) {
  Skids(white);

  while (radiomillis < until || runthrough)
  {

    m = m + 5;  //use one of the re-useable global variables
    for (int j = 0; j < COLUMNS; j++) {
      for (int q = 0; q < ROWS; q++) {
        CRGB hue = CHSV(m + (j * 5), 255, 255);
        cstrip[(leftcanopy [q][COLUMNS - (1 + j)])] = hue;
        cstrip[(rightcanopy [q][j])] = hue;
      }
    }

    for (int j = 0; j < TTOTALPIXELS; j++) {
      tstrip[j] = CHSV(m - (j * 5), 255, 255);
    }


    Show();
    RadioCheck();
    if (runthrough) {
      break;
    }
  }


}



void loop()
{

  RadioCheck(); //get the data from the radio
  Printout(); //serial.print just for debugging

  switch (mode) { // go different ways depending on the current radio mode

    case 2:  //ready mode when mode=2
      runthrough = true;

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // READY MODE CAN BE USED WHEN THE HELI IS WAITING TO START ROUTINE ///////////////////////////////////////////////////
      // IT DOES NOT PLAY ANY MUSIC /////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      ShiftingTwoSparkle();

      break; // end of ready mode

    case 3:  // stop mode when mode=3
      runthrough = true;

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // STOP MODE IS USED TO SWITCH OFF ALL LEDS ///////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      All (black);
      //in demo, stop & ready modes you need to use Show() to make static colours work
      Show();
      break; // end of stop mode

    case 4:   // demo mode when mode=4
      runthrough = true;

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // DEMO MODE IS USED TO MAKE SURE EVERYTHING IS WORKING WHEN SETTING UP////////////////////////////////////////////////
      // THE LIGHTING FUNCTIONS SHOULD TEST EVERY LED ///////////////////////////////////////////////////////////////////////
      // IT WILL PLAY demo.mp3 ON THE MP3 PLAYER TO TEST THE MUSIC IS WORKING ///////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ScrollText("rOyPgTcIbPmOrWyEgRcEbD", 1);

      Show();


      break; // end of demo mode

    case 1: //run mode when mode=1
      runthrough = false;

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
      SparkleCanopyTailBoom(19365, 0.3, white, 200); //up to chord change
      SparkleCanopyTailBoom(21942, 1, white, 200); //up to "we're marooned on a small island"
      SparkleMerge1 (23225, 1, white, green, 200); //merge through to "island" at 23225
      SparkleCanopyTailBoom(25066, 1, green, 200); //up to "in an endless"
      SparkleMerge1 (26342, 1, green, blue, 200); //merge through to "sea" at 26342
      SparkleCanopyTailBoom(28532, 1, blue, 200); //up to a point where it starts merging to yellow
      SparkleMerge1(29164, 1, blue, yellow, 200); //merged as it gets to sand
      SparkleCanopyTailBoom(32322, 1, yellow, 200); //up to dramatic
      MergeAll(32722, black, red); //up to "but tonight"
      WaitUntil(35573);
      ReverseStarlights(38452, red, 200, 5);
      Tail(cyan);
      Skids(cyan);
      ReverseStarlights(41723, cyan, 200, 5);
      Tail(green);
      Skids(green);
      ReverseStarlights(47554, green, 200, 5);
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
      Skids(cyan);
      Tail(cyan);
      //The numbers in this function are start time of repeating section, end time of repeating section, number of intervals
      BeatCalculator(63645, 67477, 5);
      for (uint32_t timer = x; timer < y; timer = timer + z)
      {
        MergeCrazyBars (timer, cyan, black);
      }

      //The numbers in this function are start time of repeating section, end time of repeating section, number of intervals
      BeatCalculator(67477, 73375, 17);
      for (uint32_t timer = x; timer < y; timer = timer + z)
      {
        MergeCrazyBars (timer - 70, cyan, black);
        Canopy(black);
        TailBoom(black);
        WaitUntil(timer);
      }

      //The numbers in this function are start time of repeating section, end time of repeating section, number of intervals
      BeatCalculator(73375, 76146, 16);
      for (uint32_t timer = x; timer < y; timer = timer + z)
      {
        MergeAll(timer - 45, cyan, black);
        All(black);
        WaitUntil(timer);
      }

      Strobe(77577, cyan);
      Strobe(78955, yellow);
      All(black);
      WaitUntil(79946);
      MergeAll(80434, yellow, black);
      TailFin(red);
      TailBoom(yellow);
      SkidsUnder(yellow);
      SkidsSide(red);
      DiscoPalette(86169, LiquidGold_p, 175, 10);
      Canopy(black);
      TailBoom(blue);
      SkidsSide(blue);
      SkidsUnder(red);
      WaitUntil(86426);
      SpectrumFire(88050, BlueBurst_p, 10, 100);
      TailBoom(yellow);
      SkidsUnder(yellow);
      SkidsSide(red);
      DiscoPalette(97577, LiquidGold_p, 175, 10);
      Canopy(black);
      TailBoom(blue);
      SkidsSide(blue);
      SkidsUnder(red);
      SpectrumFire(99240, BlueBurst_p, 10, 100);
      Skids(yellow);
      TailFin(yellow);
      MergeCanopyTailBoom(99676, blue, black);
      Canopy(black);
      TailBoom(black);
      WaitUntil(99726);
      MergeCanopyTailBoom(100156, blue, black);
      Canopy(black);
      TailBoom(black);
      WaitUntil(100206);
      MergeCanopyTailBoom(100645, blue, black);
      Canopy(black);
      TailBoom(black);
      WaitUntil(100695);
      MergeAll(100897, white, black);
      All(black);
      WaitUntil(101159);
      Skids(cyan);
      TailFin(cyan);
      MergeCanopyTailBoom(103820, red, black);
      Skids(yellow);
      TailFin(yellow);
      Canopy(blue);
      TailBoom(blue);
      WaitUntil(104663);
      MergeCanopyTailBoom(104663 + 341, blue, black);
      Skids(cyan);
      TailFin(cyan);
      TailBoom(red);
      Canopy(red);
      WaitUntil(107287);
      MergeCanopyTailBoom(107287 + 302, red, black);
      SkidsSide(yellow);
      TailFin(yellow);
      TailBoom(blue);
      SkidsUnder(yellow);
      Canopy(blue);
      WaitUntil(108522);
      MergeCanopyTailBoom(108522 + 255, blue, black);
      SkidsSide(cyan);
      TailFin(cyan);
      TailBoom(red);
      SkidsUnder(cyan);
      Canopy(red);
      WaitUntil(111705);
      MergeCanopyTailBoom(111705 + 952, red, black);
      SkidsSide(cyan);
      TailFin(cyan);
      TailBoom(red);
      SkidsUnder(cyan);
      Canopy(red);
      WaitUntil(114834);
      SkidsSide(yellow);
      TailFin(yellow);
      TailBoom(blue);
      SkidsUnder(yellow);
      Canopy(blue);
      WaitUntil(116693);
      All(black);
      WaitUntil(116963);
      MergeAll(116963 + 434, white, black);
      All(black);
      WaitUntil(117697);
      SkidsSide(white);
      TailFin(white);
      TailBoom(dullred);
      SkidsUnder(red);
      SpectrumTwoColour(133110, white, dullred);
      PaletteSparkleAll(147249, 5, RainbowColors_p, 175);
      Flash(white);
      SparkleMerge1(151085, 5, magenta, red, 175);
      Flash(white);
      SparkleMerge1(154955, 5, green, red, 175);
      Flash(white);
      SparkleMerge1(158791, 5, blue, orange, 175);
      Flash(white);
      SparkleMerge1(162493, 5, cyan, magenta, 175);
      TailFin(yellow);
      SkidsSide(magenta);
      SkidsUnder(blue);
      Canopy(red);
      TailBoom(cyan);
      WaitUntil(163260);
      SkidsUnder(red);
      SkidsSide(red);
      TailFin(red);
      ShiftingPaletteCanopy(164415, RainbowStripeColors_p, 1, 6, 2);
      //The numbers in this function are start time of repeating section, end time of repeating section, number of intervals
      BeatCalculator(164415, 170046, 12);
      for (uint32_t timer = x; timer < y; timer = timer + z)
      {
        LongFlash(white);
        RandomCol();
        WaitUntil(timer);
      }
      //The numbers in this function are start time of repeating section, end time of repeating section, number of intervals
      BeatCalculator(170046, 171908, 8);
      for (uint32_t timer = x; timer < y; timer = timer + z)
      {
        LongFlash(white);
        RandomCol();
        WaitUntil(timer);
      }
      BeatCalculator(171908, 178432, 14);
      for (uint32_t timer = x; timer < y; timer = timer + z)
      {
        LongFlash(white);
        RandomCol();
        WaitUntil(timer);
      }
      RainbowCanopyTailBoom(189521);
      Skids(red);
      TwoSparkleCanopyTail(189722, 35, magenta, white, 175);
      TwoSparkleCanopyTail(190200, 35, green, white, 175);
      TwoSparkleCanopyTail(190669, 35, red, white, 175);
      TwoSparkleCanopyTail(191133, 35, blue, white, 175);
      TwoSparkleCanopyTail(191610, 35, yellow, white, 175);
      TwoSparkleCanopyTail(192073, 35, cyan, white, 175);
      TwoSparkleCanopyTail(193008, 35, green, white, 175);
      TwoSparkleCanopyTail(193282, 35, red, white, 175);
      PaletteStrobe(194448, RainbowColors_p);
      All(black);
      WaitUntil(196448);
      Tail(dullred);
      Skids(dullred);
      ScrollText("bTEAM_AT", 1);
      Finish();

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // END OF THE NIGHT FLYING ROUTINE ////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // DON'T CHANGE THE LINES BELOW!
      break; // end of run mode

    default:
      runthrough = true;
      ScrollText("rNO SIGNAL", 1);
      break;



  } // end of switch case
} // end of loop



