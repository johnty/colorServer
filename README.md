# colorServer

basic python server for providing an UI to send RGB values to serial port to control NeoPixel LEDs. 

arduino_code.ino contains an adapted version of some NeoPixel example code that drives a hardcoded 30 LED strip, but can be easily modified. (also, one in every 4 LEDs are hardcoded to blue in this example)

designed for use on a raspberry pi and a teensy LC, which has a 5V output on pin 17. can use any 5V arduino as well, or even 3.3V device if you like to live dangerously as the TTL high of 3.3V often will drive the NeoPixels fine.

used for indoor hydroponic rack:

![](http://i.imgur.com/InGTbk0.gif)

- python server based on [this code](https://gist.github.com/thepacketgeek/65bea2613d3d23f9bea5)

- [jscolor](http://jscolor.com/) for javascript colour picker
