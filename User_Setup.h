
#define USER_SETUP_INFO "User_Setup"


#pragma message("MY_HEADER_H is included!")

// #define ILI9341_2_DRIVER     // Alternative ILI9341 driver,1172
// #define ILI9486_DRIVER
#define ILI9488_DRIVER 
#define TFT_WIDTH  320 
#define TFT_HEIGHT 480 
// ------------------ PINS DEFINES 
// TIRQ  36 
// TOUT 39
//TDIN 32
#define TOUCH_CS 21  // 21    // Chip select pin (T_CS) of touch screen
// T_CLK 33
#define TFT_MISO 12 // SDO
#define TFT_BL   27            // LED back-light control pin
#define TFT_BACKLIGHT_ON HIGH  // Level to turn ON back-light (HIGH or LOW)
#define TFT_SCLK 14
#define TFT_MOSI 13 // SDI
#define TFT_DC    2 // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to RST pin)
#define TFT_CS   15 // 15 // Chip select control pin

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

// Comment out the #define below to stop the SPIFFS filing system and smooth font code being loaded
// this will save ~20kbytes of FLASH
#define SMOOTH_FONT

#define SPI_FREQUENCY  27000000 ///


// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  20000000 ///

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
#define SPI_TOUCH_FREQUENCY  2500000 //

void my_func_test();
