#include <Wire.h>
#include "Underwater_Barometer.h"


Barometer myBarometer;

void setup(){
  Serial.begin(115200);
  myBarometer.setup();
}

void loop(){

  myBarometer.display_data();
  float z = myBarometer.depth();
  Serial.print("depth = ");Serial.println(z);
  delay(100);
}



