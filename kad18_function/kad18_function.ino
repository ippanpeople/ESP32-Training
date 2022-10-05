#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN   5
#define LED_PIN2   25

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 5
#define LED_COUNT2 5

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT2, LED_PIN2, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();
  strip2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip2.show();
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip2.setBrightness(50);
}

void loop() {
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorDotOn(0, strip.Color(255,0,0)); //0 番目(一番下)が赤色に光る delay(1000);
  colorDotOn(0, strip2.Color(255,0,0)); //0 番目(一番下)が赤色に光る delay(1000);
  colorDotOff(0); //Red 0 番目(一番下)が消える
  delay(1000);
  colorDotOn(4, strip.Color(0, 255, 0)); //4 番目(一番上)が緑色に光る delay(1000);
  colorDotOn(4, strip2.Color(0, 255, 0)); //4 番目(一番上)が緑色に光る delay(1000);
  colorDotOff(4); //Red 4 番目(一番上)が消える
  delay(1000);
}
/**
* colorDotOn
*/
void colorDotOn(int i, uint32_t color){
  //ここに i 番目の LED が color 色に光る処理を入れる
  strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  strip2.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  strip.show();                          //  Update strip to match
  strip2.show();                          //  Update strip to match
}
/**
 * colorDotOff
 */
void colorDotOff(int i){
  //ここに i 番目の LED が消灯する処理を入れる
  strip.clear();         //   Set all pixels in RAM to 0 (off)
  strip2.clear();         //   Set all pixels in RAM to 0 (off)
  strip.show();          //  Update strip to match
  strip2.show();          //  Update strip to match
}
/**
* colorWipe
*/
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);  // Set pixel's color (in RAM)
    strip2.setPixelColor(i, color);  // Set pixel's color (in RAM)
    strip.show(); // Update strip to match
    strip2.show(); // Update strip to match
    delay(wait);  // Pause for a moment

  }
}

