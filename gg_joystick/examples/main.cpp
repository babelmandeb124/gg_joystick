#include "Arduino.h"
#include "gg_joystick.h"

#define SW 35
#define X 34
#define Y 32


void manual(void* );

using gg_joystick_ns::gg_joystick;
gg_joystick j(X, Y, SW);



void setup(){
  Serial.begin(9600);
  j.begin();
  xTaskCreate(manual, "MANUAL", 2048, NULL, 1, NULL);
}


void loop(){
  delay(1000);
}


void manual(void*  paramBaram){
  while(1){
    j.raw();
    j.vctr_print();
    delay(600);
  }
}