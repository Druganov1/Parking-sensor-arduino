#include "Ultrasonic.h"
#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);
bool isInReverse = false;
 
Ultrasonic ultrasonic(7);
void setup()
{
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, INPUT);

    Serial.begin(9600);
    u8x8.begin();
    u8x8.setFont(u8x8_font_5x8_r);

}
void loop()
{
    if(digitalRead(6) == HIGH){
      if(isInReverse){
        isInReverse = false;
        u8x8.clear();
        u8x8.setCursor(0,0);
        u8x8.print("Current gear: D");

      } else {


        isInReverse = true;
        u8x8.clear();
        u8x8.setCursor(0,0);
        u8x8.print("Current gear: R");
      }
    }

  
    long RangeInCentimeters;
 
 
    RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
    Serial.print(RangeInCentimeters);//0~400cm
    Serial.println(" cm");
    if(isInReverse){
      if(RangeInCentimeters < 15 && RangeInCentimeters > 10){ //15CM of minder

      delay(200);
      digitalWrite(4, HIGH);
      analogWrite(5, 127);
      delay(200);
      digitalWrite(4, LOW);
      analogWrite(5, 0);
      
    } 
    else if(RangeInCentimeters < 10 && RangeInCentimeters > 5) {

      delay(100);
      digitalWrite(4, HIGH);
      analogWrite(5, 127);
      delay(100);
      digitalWrite(4, LOW);
      analogWrite(5, 0);
    } else if(RangeInCentimeters < 5){
      digitalWrite(4, HIGH);
      analogWrite(5, 127);
    }
    
    
    else {
      digitalWrite(4, LOW);
      analogWrite(5, 0);
    }
    }

}
