// CP Kaleidoscope  Make an inexpensive, fun Kaleidoscope with Adafruit's Circuit Playground
//
// Change the LED effect on the Circuit Playground NeoPixel ring based on orientation from
//   the accelerometer position (like turning the end of the kaleidoscope)
//
// Mike Barela  August 30, 2016  MIT License  For Adafruit Industries

#include <Adafruit_CircuitPlayground.h>

const int NUMBER_OF_LEDS_ON_RING = 10;  // NeoPixels on Circuit Playground
const int brightness = 25;              // Change this value to change the NeoPixel brightness

int ledPosition, led, previousLed = 0;
float x, y, nx, ny, angle; 

void setup() {
  CircuitPlayground.begin();                   // Circuit Playground startup
  CircuitPlayground.setBrightness(brightness);
  CircuitPlayground.clearPixels();
}

void loop(){

  x = CircuitPlayground.motionX();   // Get the CP accelerometer x and y positions 
  y = CircuitPlayground.motionY();   //   (we ignore the z axis for this one)
  nx = x / 10.0;
  ny = y / 10.0;
  angle = atan((ny/nx)) * 180 / 3.14;  // Figure out the angle of the accelerometer

  if(angle > 0.0) {        // Adjust based on arctangent function (in degrees)
    if(nx < 0.0)
      angle += 180;
  } 
  else {
    if(ny > 0.0)
      angle += 180;
    else
      angle += 360;
  }
  if(angle == 360.0)      // a 360 degree angle is the same as a zero degree angle 
    angle = 0;

  led = circularize(angle / (360 / NUMBER_OF_LEDS_ON_RING));

  if(previousLed == led) { 
    // nothing to do 
  }
  else if (counterClockwiseDistanceBetweenLeds(previousLed, led) <= 8) {
    led = circularize(previousLed + 1);
    rainbowCycle(led);
    }
  else {
    led = circularize(previousLed - 1);
    rainbowCycle(led);
  }
  previousLed = led;
  delay(20);
}

int circularize(int pos){
  if(pos >= NUMBER_OF_LEDS_ON_RING)
    return(pos - NUMBER_OF_LEDS_ON_RING);
  else if(pos < 0)
    return(pos + NUMBER_OF_LEDS_ON_RING);
  else
    return(pos);
}

int counterClockwiseDistanceBetweenLeds(int prevPos, int nextPos){
  int distance;
  distance = nextPos - prevPos;
  if(distance < 0)
    distance += NUMBER_OF_LEDS_ON_RING;
    
  return(distance); 
}

static int speeds[] = { 0, 5, 10, 20, 35, 50, 70, 90, 120 };

void rainbowCycle(int currentSpeed)  {
    // Make an offset based on the current millisecond count scaled by the current speed.
    uint32_t offset = millis() / speeds[currentSpeed];
    // Loop through each pixel and set it to an incremental color wheel value.
    for(int i=0; i<10; ++i) {
      CircuitPlayground.strip.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / 10) + offset) & 255));
    }
    // Show all the pixels.
    CircuitPlayground.strip.show();
}

