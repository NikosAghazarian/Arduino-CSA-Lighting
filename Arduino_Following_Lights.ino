#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    150
CRGB leds[NUM_LEDS];

const int trigPin = 2;
const int echoPin = 3;
const int buttonLED = 4;
int LEDbutton = 0;
int LEDstate = 1;
int approached = 0;
int approachTimer = 0;
int timerMax = 20;
long duration;
int distance;
int distance_cm;
int distance_in;
int ledNum = 0;



void setup() {
  // initialize serial communication:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonLED, INPUT);
  Serial.begin(9600);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  for(int i = 0; i<2; i++){
    leds[i] = CRGB(20, 20, 200);
    FastLED.show();
  }
  
}
void loop() {
  if (LEDstate == HIGH) {   
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    Serial.println(duration);
    // convert the time into a distance
    distance_cm = duration / 29 / 2;
    //distance_in = distance_cm * 0.393701;  
  
    Serial.print("Distance: ");
    Serial.println(distance_cm);
    delay(100);
  
    approachTimer = approachTimer + 1;
    
    if (approachTimer > timerMax) {
      approachTimer = 0;
      approached = 0;
    }
    Serial.println(approachTimer);
    
    if (distance_cm < 40 || approached == 1) {
      for(int i = 0; i<150; i++){
        leds[i] = CRGB(20, 20, 200);
        FastLED.show();
      }
      delay(20);
      ledNum = 10+(distance_cm*4);
      for (int i = ledNum; i < ledNum+6; i++) {
        leds[i-2] = CRGB(255, 100, 20);
        FastLED.show();
      }
      delay(50);
      approached = 1;
      approachTimer = 0;
    }
    else {
      for(int i = 0; i<150; i++){
        leds[i] = CRGB(0, 0, 0);
        FastLED.show();
      }
    }
  }
  else {
    for(int i = 0; i<150; i++){
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
    }  
  }  
  
  LEDbutton = digitalRead(buttonLED);
  delay(50);
  if (LEDbutton==HIGH) {
    if (LEDstate == 1) {
      LEDstate = 0;
    }
    else {
      LEDstate = 1;
    }
    delay(1000);
  }
}
