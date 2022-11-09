//11 noveember little lights For Jolien van jelle
/* 22 sk2812 rgbw leds controlled on one data line in stacks of 11
   one button
   arduino nano with bypassed, voltage regulator
   18650 battery

    animation tab can hold random led colors that can be changed ugins the button
    if you add more add the aniAmount to the amont of variables and add more else if statements in the loop

*/

//libs --> fastled  https://github.com/FastLED/FastLED
// animations taken from: https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects with some changes to account for the RGBW part of the thing.


// 11 led on one side rgbw D2
//one button on  D1

#include <FastLED.h>
#include "FastLED_RGBW.h" // litle hack from  (http://krazydad.com). 

const int BUTTON = 2; // button pin
const int aniAmount = 8; // amount of animations that are running in the loop (aray starts at 0 so its 9 now )
int animationSelector = 0; // little animationSelector
int moveSpeed = 40; // used as a delay in the on led travel animation

//local LEDs
#define NUM_LEDS 11 // amount of leds 
#define LED_PIN 4  // led pin

CRGBW leds[NUM_LEDS]; // hack to get rgbw working, im sub buffering the leds and inserting an extra channel
CRGB *ledsRGB = (CRGB *) &leds[0]; // leds

int ledOn = 1; // variable used for the single led chace


void setup() {
  
  //start serial port
  Serial.begin(115200);
  Serial.print("11 novemember is de dag");

  pinMode(LED_PIN, OUTPUT);     //set the led pin as output
  pinMode(BUTTON, INPUT_PULLUP); // set the button as input pullup
  attachInterrupt(digitalPinToInterrupt(BUTTON), blink, FALLING  ); //set the button as interupt so when it is pressed it interupts the program
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS)); // add leds to the array
  animationSelector = random(aniAmount);
  initTest(); // show a little test rgb seqence

}

void loop() {

  // Serial.println(animationSelector);
  if  (animationSelector == 0) {
    Fire(55, 120, 15);
  } else  if  (animationSelector == 1) {
    colorWipe(255, 0, 255, 50);
    colorWipe(0x00, 0x00, 0x00, 50);
  } else if  (animationSelector == 2) {
    meteorRain(0xff, 0xff, 0xff, 10, 64, true, 30);
  } else  if  (animationSelector == 3) {
    OneLedTravel();
  } else  if  (animationSelector == 4) {
    Sparkle(0xff, 0xff, 0xff, 100);
  } else if (animationSelector == 5) {
    FadeInOut(255, 0, 240); // pink?
  } else if (animationSelector == 6) {
    FadeInOut(255, 100, 0); // yellow
  } else  if  (animationSelector == 7) {
    Sparkle(0, 127, 255, 100);
  } else  if  (animationSelector == 8) {
   //rainbowCycle(10);
   CylonBounce(0xff, 0, 0, 4, 20, 50);// little kit animaation 
  }
}


void blink() { // interyupt fuction that increments the animation selector value
  //animationSelector = random(aniAmount);
  animationSelector++;
  if ( animationSelector > aniAmount) {  // circle round
    animationSelector = 0;
  }
  //Serial.println(animationSelector);
}


void initTest() // little test animation
{
  for (int i = 0 ; i < NUM_LEDS ; i++)
  {
    //leds[i] = CRGBW(127, 0, 0, 0);
    leds[i] = CRGB(127, 0, 0);
  }
  FastLED.show();
  delay(500);
  for (int i = 0 ; i < NUM_LEDS ; i++)
  {
    //leds[i] = CRGBW(0, 127, 0, 0);
    leds[i] = CRGB(0, 127, 0);
  }
  FastLED.show();
  delay(500);
  for (int i = 0 ; i < NUM_LEDS ; i++)
  {
    // leds[i] = CRGBW(0, 0, 127, 0);
    leds[i] = CRGB(0, 0, 127);
  }
  FastLED.show();
  delay(500);
  for (int i = 0 ; i < NUM_LEDS ; i++)
  {
    //leds[i] = CRGBW(0, 0, 0, 127);
    leds[i] = CRGB(127, 127, 127);
  }
  FastLED.show();
  delay(500);
  for (int i = 0 ; i < NUM_LEDS ; i++)
  {
    // leds[i] = CRGBW(0, 0, 0, 0);
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}


void showStrip() { // used in the animaiton tab
  FastLED.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue) { // used for animations
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
  //CRGBW(0, 0, 0, 127);
}

void setAll(byte red, byte green, byte blue) { // used in animations
  for (int i = 0; i < NUM_LEDS; i++ ) { // loop thru all and set the pixel colors
    setPixel(i, red, green, blue);
  }
  showStrip(); // send data to the leds
}

void OneLedTravel() { // one led travel animation

  leds[ledOn % NUM_LEDS] = CRGBW(255, 255, 255, 255); // color of the led  // using modulo on the amount of leds to make it travel withoin bounds// will eventualy overflow not sure what happends then :)
  //leds[ledOn] = CRGBW(0, 0, 0, 255);
  //leds[ledOn+1] = CRGBW(0, 0, 255, 0);
  FastLED.show();
  delay(moveSpeed);
  leds[ledOn % NUM_LEDS] = CRGBW(0, 0, 0, 0);
  // leds[ledOn+1] = CRGBW(0, 0, 255, 0);

  ledOn++;
  //  Serial.print("hour:");
  //  Serial.println(hour);
  // Serial.print("led:");
  //  Serial.println(ledOn);
  //  Serial.print("ledModulo:");
  //  Serial.println(ledOn%60);
  FastLED.show();
  //    if (ledOn>=60 ){
  //      ledOn=1;
  //       //delay(50);
  //    }
}
