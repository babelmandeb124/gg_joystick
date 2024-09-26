#pragma once

#include "Arduino.h"

namespace gg_joystick_ns {

//вектор: дистанция и угол
struct vctr_t{
  int w;
  int l;
};

enum axis_t{xax, yax};


class gg_joystick{
public:
  gg_joystick(int x_pin, int y_pin, int b_pin, int htrz = 20){
    pinx = x_pin;
    piny = y_pin; 
    pinb = b_pin; 
    gisteresis = htrz;

  }
  gg_joystick(){
    
  }

  void begin(int x_pin, int y_pin, int b_pin, int htrz = 20){
    pinx = x_pin;
    piny = y_pin; 
    pinb = b_pin; 
    pinMode(pinx, INPUT_PULLUP);
    pinMode(piny, INPUT_PULLUP);
    pinMode(pinb, INPUT_PULLUP);
    gisteresis = htrz;
    midX = analogRead(pinx);
    midY = analogRead(piny);


  }

    void begin(){
    pinMode(pinx, INPUT_PULLUP);
    pinMode(piny, INPUT_PULLUP);
    pinMode(pinb, INPUT_PULLUP);
    gisteresis = 20;
    midX = analogRead(pinx);
    midY = analogRead(piny);
  }

//вывод сырья в serial
  void raw(){
    read();
    printf("X: %d\n Y: %d\n butt: %d\n", adcx, adcy, pmsb);
  }

  //вывод сырья в serial
  void vctr_print(){
    processing();
    // Serial.println(vctr.l);
    // Serial.println(vctr.w);

    printf("l: %d\n w: %d\n\n", vctr.l, vctr.w);
  }
//полезные данные на управление  
  vctr_t checkout(){
    processing();
  }
  
private:
  int pinx, piny, pinb;
  int gisteresis = 20, midX = 2047, midY = 2047;
  int adcx = 0, adcy = 0, pmsb = 1;
  float x, y;
  vctr_t vctr;


//...закрытые функции..

  //чтение 
  void read(){
    adcx = analogRead(pinx);
    adcy = analogRead(piny);
    pmsb = digitalRead(pinb);



   // x = adcx - mid;
    //y = adcy - mid;
    
    
  }

  float formalize(int adc, int midX_Y, axis_t axis){
    float curr;
    float r;
    switch(axis){
      // if(adc >= (mid - gisteresis) && adc <= (mid + gisteresis))
      //    return 0.0;
      case xax:
        if(adc >= (midX - gisteresis) && adc <= (midX + gisteresis))
          return 0.0;
        curr = adc - midX;
        r = (curr/midX) * 100;
        if (r > 100)
          r = 100;
        if (r < -100)
          r = -100;
      break;
      case yax:
        if(adc >= (midY - gisteresis) && adc <= (midY + gisteresis))
          return 0.0;
        curr = adc - midY;
        r = (curr/midY) * 100;
        if (r > 100)
          r = 100;
        if (r < -100)
          r = -100;
      break;

    }
  
    return r;
  }

//вычисления
  void processing(){
    float atanr, gyp;
    read();
    x = formalize(adcx, midX, xax);
    y = formalize(adcy, midY, yax);
   atanr = atan2(y, x);
   vctr.w = degrees(atanr);
    gyp = sqrt(pow(x, 2) + pow(y,2));
    if (gyp > 100)
      gyp = 100;
    vctr.l = gyp;
  }



//...закрытые функции END..

};





//prototypes
// void joystick_init(void);
// void joystick_read();



}