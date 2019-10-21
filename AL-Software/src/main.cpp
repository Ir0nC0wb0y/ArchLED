#include <Arduino.h>

#define PIN_LED_R                   9
#define PIN_LED_G                   6
#define PIN_LED_B                   5
#define PIN_LED_W                   3

#define PIN_SWITCH                 11

// Color stuff
#include "custom_colors.h"
#define PIN_POT_1                   A0 // Using for brightness
#define PIN_POT_2                   A1 // Using for RGB Color
Color Leds;
#define COLOR_TRANSITIONS            5
int color_transitions       =    1000/COLOR_TRANSITIONS;
#define BRIGHTNESS_MAX             250
#define BRIGHTNESS_MIN               1
#define BRIGHTNESS_DEF             100

// Loop Stuff
unsigned long time_last     =        0;
#define LOOP_TIME                  500

int check_bightness() {
  int brightness = analogRead(PIN_POT_1);
  brightness = map(brightness,0,1023,1,250);
  //Serial.print("Brightness: "); Serial.println(brightness);
  return brightness;
}

void set_color(int brightness) {
  // check brightness w/in bounds
  if ( brightness < BRIGHTNESS_MIN || brightness > BRIGHTNESS_MAX) {
    Serial.print("Brightness ("); Serial.print(brightness); Serial.println(") outside of bounds");
    brightness = BRIGHTNESS_DEF;
  }

  int pot_color = analogRead(PIN_POT_2);
  //Serial.print("pot_color: "); Serial.println(pot_color);
  
  int choose_val = pot_color / color_transitions; // This should set choose_val to 0-5, but may be 1-6...
  int mapper = map(pot_color % color_transitions, 0, color_transitions,   0, 100);
    switch (choose_val) {
    case 0:
      // do something with pot_color
      Leds.mapRO(mapper);
      break;

    case 1:
      Leds.mapOY(mapper);
      break;

    case 2:
      Leds.mapYG(mapper);
      break;

    case 3:
      Leds.mapGB(mapper);
      break;

    case 4:
      Leds.mapBP(mapper);
      break;

    default:
      Leds.mapW();
      break;
  }

  int color_R = Leds.return_R() * ( (float)brightness / BRIGHTNESS_MAX );
  int color_G = Leds.return_G() * ( (float)brightness / BRIGHTNESS_MAX );
  int color_B = Leds.return_B() * ( (float)brightness / BRIGHTNESS_MAX );
  int color_W = brightness;
  
  Serial.print("Setting Color (R, G, B, W): ");
  Serial.print(color_R); Serial.print(", ");
  Serial.print(color_G); Serial.print(", ");
  Serial.print(color_B); Serial.print(", ");
  Serial.print(color_W); Serial.print(" ");
  analogWrite(PIN_LED_R,color_R);
  Serial.print(".");
  analogWrite(PIN_LED_G,color_G);
  Serial.print(".");
  analogWrite(PIN_LED_B,color_B);
  Serial.print(".");
  analogWrite(PIN_LED_W,color_W);
  Serial.print(".");
  Serial.println(" Done");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Sketch Started");

  pinMode(PIN_LED_R,OUTPUT);
  pinMode(PIN_LED_G,OUTPUT);
  pinMode(PIN_LED_B,OUTPUT);
  pinMode(PIN_LED_W,OUTPUT);

  digitalWrite(PIN_LED_R,LOW);
  digitalWrite(PIN_LED_G,LOW);
  digitalWrite(PIN_LED_B,LOW);
  digitalWrite(PIN_LED_W,LOW);

  pinMode(PIN_SWITCH,INPUT);
}

void loop() {
  if (millis() >= time_last + LOOP_TIME) {
    if (digitalRead(PIN_SWITCH)) {
      //Serial.print("Reading Potentiometers (1,2): ("); Serial.print(analogRead(PIN_POT_1)); Serial.print(", "); Serial.print(analogRead(PIN_POT_2)); Serial.println(")");
      set_color(check_bightness());
    } else {
      Serial.println("Flip the switch!");
      digitalWrite(PIN_LED_R,LOW);
      digitalWrite(PIN_LED_G,LOW);
      digitalWrite(PIN_LED_B,LOW);
      digitalWrite(PIN_LED_W,LOW);
    }
    time_last = millis();
  }
}