/**
 * NeoPixel HSL
 * 
 * Author: E. Scott Eastman
 * Date: Feb 2017 
 * 
 * Add HSL to RGB Color space conversion. Originially designed to 
 * work with the Adafruit NeoPixel Library
 * 
 * MIT License
 * Copyright (c) 2017 E. Scott Eastman (Mazaryk)
 * 
 * Author is not associated with Adafuit or NeoPixel 
 */
#include <Adafruit_NeoPixel.h>

#define PIN 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); 
}

void loop() {
  demo_rotate();
//  demo_random();
}

/**
 * Demo Rotate
 * 
 * Iterate through the hues, one pixel at time, 
 * and divide the strip into 3 equal parts.
 */
void demo_rotate() { 

  static uint8_t n = strip.numPixels();
  
  static uint16_t hue = 0; // 0-359
  uint8_t saturation = 100; // 0-100
  uint8_t lightness = 50; // 0-100
  
  uint32_t color;
  uint8_t i; 
  
  for(i=0; i < n; i++) {
    color = hsl(hue++, saturation, lightness);
    strip.setPixelColor(i, color);
    strip.setPixelColor((i+n/3)%n, color);
    strip.setPixelColor((i+n/3*2)%n, color);
    strip.show();
    delay(40);
  }

  hue %= 360;
}
/**
 * Demo Random
 * 
 * Random Pixel, Random Color
 */
void demo_random() { 

  uint8_t pixel = random(0, strip.numPixels());
  uint16_t hue = random(0, 360);
  uint8_t saturation = 100;
  uint8_t lightness = 50;
  
  strip.setPixelColor(pixel, hsl(hue, saturation, lightness));
  strip.show();
}

/**
 * Map HSL color space to RGB
 * 
 * Totally borrowed from:
 * http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/ 
 * 
 * Probably not the most efficient solution, but 
 * it get's the job done.
 */
uint32_t hsl(uint16_t ih, uint8_t is, uint8_t il) {

  float h, s, l, t1, t2, tr, tg, tb;
  uint8_t r, g, b;

  h = (ih % 360) / 360.0;
  s = constrain(is, 0, 100) / 100.0;
  l = constrain(il, 0, 100) / 100.0;

  if ( s == 0 ) { 
    r = g = b = 255 * l;
    return strip.Color(r, g, b);
  } 
  
  if ( l < 0.5 ) t1 = l * (1.0 + s);
  else t1 = l + s - l * s;
  
  t2 = 2 * l - t1;
  tr = h + 1/3.0;
  tg = h;
  tb = h - 1/3.0;

  r = hsl_convert(tr, t1, t2);
  g = hsl_convert(tg, t1, t2);
  b = hsl_convert(tb, t1, t2);

  return strip.Color(r, g, b); 
}
/**
 * HSL Convert
 * Helper function
 */
uint8_t hsl_convert(float c, float t1, float t2) {

  if ( c < 0 ) c+=1; 
  else if ( c > 1 ) c-=1;

  if ( 6 * c < 1 ) c = t2 + ( t1 - t2 ) * 6 * c;
  else if ( 2 * c < 1 ) c = t1;
  else if ( 3 * c < 2 ) c = t2 + ( t1 - t2 ) * ( 2/3.0 - c ) * 6;
  else c = t2;
  
  return (uint8_t)(c*255); 
}
