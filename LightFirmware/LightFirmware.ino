#include <Adafruit_NeoPixel.h>

#define PIN 2
#define nPixels 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(nPixels, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.setBrightness(255);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
//  rainbow_sync(20);
  rainbow_async(10);
//  strobe(50);
}

void strobe(uint32_t wait)
{
  for(uint8_t i = 0; i < 5; i++)
  {
    for(uint8_t j = 0; j < nPixels; j++)
    {
      strip.setPixelColor(j, strip.Color(255,255,255));
      strip.show();
      delay(wait);
      strip.setPixelColor(j, 0);
    }
  }
}

void rainbow_async(uint32_t wait)
{
  uint32_t this_color = 0;
  for(uint16_t i = 0; i < 255; i++)
  {
    for(uint8_t j = 0; j < nPixels; j++)
    {
      strip.setPixelColor(j, HSLtoRGB((i + 20 * j) % 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbow_sync(uint32_t wait)
{
  uint32_t this_color = 0;
  for(uint16_t i = 0; i < 255; i++)
  {
    this_color = HSLtoRGB(i);
    for(uint8_t j = 0; j < nPixels; j++)
    {
      strip.setPixelColor(j, this_color);
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t HSLtoRGB(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
