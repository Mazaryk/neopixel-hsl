# neopixel-hsl
NeoPixel HSL allows for HSL to RGB Colour Space conversion. 

While using the awesome AdaFruit NeoPixels, I found it much more intuitive to use HSL (Hue, Saturation, Lightness) colour encoding instead of RGB (Red, Green, Blue). HSL makes it much easier to handle hue and brightness independently. This simplifies many common lighting effects, like fading a pixel from off to on, and keeping the colour consistent.

Also, this will make it much easier to say, hook up a potentiomiter and have it control only the hue. Using the pot, it's simple to wipe through the entire rainbow.

This implementation is designed for use with the NeoPixel Library, but should be easily modifiable to be used in other contexts. The hsl() function returns a 32 bit, packed RGB value, exaclty the same as Adafruit_NeoPixel::Color().

## Usage

### Inline

strip.setPixelColor(index, hsl(120, 100, 50)); // Gree, full saturation and brightness

### Assignment

uint32_t colour = hsl(0, 100, 25); // Red, full saturation, half brighness

### Good To Know
* Hue is specified in degrees, thus ranges from 0 - 359, Red = 0, Green = 120, Blue = 240 
* Hue input is mod’d by 360, so 540 == 180
* Saturation is a percentage, ranges 0 - 100
* Lightness is a percentage, ranges 0 - 100
* Saturation and Lightness inputs are constrained, anything > 100 will be treated as 100.

## HSL Primer

Here are some notes/gotchas for those new to HSL, but familiar with RGB.

* Hue values should be stored in an int (or uint16_t), not a byte (or uint8_t)
* Saturation and lightness values can be stored in a byte (or uint8_t)
* The value returned by hsl() should be stored in a uint32_t
* A lightness value of 0 is off (same as RGB: 0,0,0) regardless of hue or saturation values
* A Lightness value of 50 is full colour lightness (Red in RGB 255,0,0 in HSL is 0,100,50)
* A Lightness value of 100 is always white, regardless of h or s values
* To fade a pixel from off to on, in only white, set saturation to 0, and increase lightness. Hue value is irrelevant. 





