/*
 * use Adafruit Trinket m0
 * https://learn.adafruit.com/adafruit-trinket-m0-circuitpython-arduino/overview
 * connect Sparkfun Line Sensor to A3. 
 * https://www.sparkfun.com/products/9453
 * 
 * download the FastLED library for the "dotstar color led"
 * http://fastled.io
 * i had to use the adafruit fork to make things work
 * https://github.com/adafruit/FastLED
 * 
 *  Daniel Saakes 2017 daniel@saakes.net
 *  
 *  MIT licensed. https://opensource.org/licenses/MIT
 */

// #include <FastLED.h>
const int kNumDotStar = 1;
const int kDotStarDataPin = 7;
const int kDotStarClockPin = 8;

// CRGB gLeds[kNumDotStar];


bool gDetect = false;
long gDetectTime = 0;


#include "average.h"

const int kSensorSpeed = 200;  // in millis

long gReportTimer = 0;

RunningAverage rAvg;

void setup() {
  // heartbeat LED
  pinMode(13, OUTPUT);

  // dotstar LED

//  FastLED.addLeds<APA102, 7,8>(gLeds, kNumDotStar);

  // sensor input
  pinMode(A3, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("# start ");
  
}

// the loop function runs over and over again forever
void loop() {


/*  
   // heartbeat....
  digitalWrite(13, HIGH);   
  delay(kSensorSpeed/2);             
  digitalWrite(13, LOW);   
  delay(kSensorSpeed/2);
*/

  // read sensor
  int sensor = analogRead(A3);

  if (sensor < 800) {
    digitalWrite(13, HIGH);   
    if (gDetect==false) {
      gDetectTime = millis();
    }
    gDetect = true;
    
  } else {
    digitalWrite(13, LOW); 
    if (gDetect==true) {      
      Serial.print("stop detect ");
      Serial.println( millis() - gDetectTime);
    }
    gDetect = false;

  }


/*
  if (millis() > gReportTimer) {
    // dump it on the serial
    Serial.println(sensor);
    gReportTimer = millis() + 500;
  }
*/
}





