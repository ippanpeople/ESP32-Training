#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN 5
// #define LED_PIN2 25

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 5
// #define LED_COUNT2 5

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel strip2(LED_COUNT2, LED_PIN2, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
int c[5][3] = { {255, 0, 0}, {242, 133, 0}, {244, 208, 0}, {0, 255, 0}, {0, 0, 255} };

// setup() function -- runs once at startup --------------------------------
void setup()
{
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();
  // strip2.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();   // Turn OFF all pixels ASAP
  // strip2.show();
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  // strip2.setBrightness(50);
}

void loop()
{
  // // colorWipe(strip.Color(255, 0, 0), 50); // Red
  // colorRun(strip.Color(255, 0, 0), 50);
  // // colorRun(strip2.Color(255, 0, 0), 50);
  // delay(1000);
  // colorRun(strip.Color(0, 255, 0), 50);
  // // colorRun(strip2.Color(0, 255, 0), 50);
  // delay(1000);
    for (int j = 0; j < 5; j++)
    {
      strip.setPixelColor(j, strip.Color(c[j][0], c[j][1], c[j][2])); //  Set pixel's color (in RAM)
      delay(50);
      strip.show();
      strip.clear();
    }
    for (int k = 4; k >= 0; k--)
    {
      strip.setPixelColor(k, strip.Color(c[k][0], c[k][1], c[k][2])); //  Set pixel's color (in RAM)
      delay(50);
      strip.show();
      strip.clear();
    }
    strip.clear();
    strip.show();
    delay(1000);
  }
/**
 * colorRun
 */
// void colorRun(uint32_t color, int wait)
// {
//   // ここに color 色の LED が 0 番目から wait ミリ秒おきに点滅する処理を入れる
//   for (int i = 0; i < 5; i++)
//   {
//     strip.setPixelColor(i, color);  //  Set pixel's color (in RAM)
//     strip2.setPixelColor(i, color); //  Set pixel's color (in RAM)
//     strip.show();
//     strip2.show();
//     delay(wait);
//     strip.clear();
//     strip2.clear();
//     strip.show();
//     strip2.show();
//   }
// }
