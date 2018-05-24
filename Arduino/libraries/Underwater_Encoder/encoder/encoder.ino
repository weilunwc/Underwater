#include <SPI.h>
#include "Underwater_Encoder.h"
//#include <Math.h>

Encoder myEncoder;
void setup(){
  Serial.begin(9600);
  myEncoder.attach(2);
  myEncoder.set_offset(1963);
}

void loop(){
  int value = myEncoder.read_value();
  float angle = myEncoder.read_angle();
  Serial.print("encoder value is : ");Serial.print(value);
  Serial.print(" encoder angle is : ");Serial.println(angle);

  delay(100);
}
