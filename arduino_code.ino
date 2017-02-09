// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

// Feb 2017: added serial control for RGB setting (compiled for teensy LC using pin 17, which is the level shifted 5V output)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            17

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      30

int cRed, cGreen, cBlue;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  Serial.begin(9600);

  pixels.begin(); // This initializes the NeoPixel library.
  updateColor(200, 0, 0);
}

void updateColor(int r, int g, int b)
{
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    if (i % 4 == 0)
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    else
      pixels.setPixelColor(i, pixels.Color(r, g, b));

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(1); // Delay for a period of time (in milliseconds).

  }
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  if (Serial.available())
  {
    int readChar = Serial.read();
    if (readChar == 'r')
      updateColor(255, 0, 0);
    else if (readChar == 'g')
      updateColor(0, 255, 0);
    else if (readChar == 'b')
      updateColor(0, 0, 255);
    else if (readChar == 'c') {
      //expect more interesting stuff...
      // block read 3 more bytes
      while (Serial.available() == 0);
      cRed = (int) Serial.read();
      while (Serial.available() == 0);
      cGreen = (int) Serial.read();
      while (Serial.available() == 0);
      cBlue = (int) Serial.read();
      Serial.print("R G B val= ");
      Serial.print(cRed, HEX);
      Serial.print(cGreen, HEX);
      Serial.print(cBlue, HEX);
      updateColor(cRed, cGreen, cBlue);
    }

  }

}
