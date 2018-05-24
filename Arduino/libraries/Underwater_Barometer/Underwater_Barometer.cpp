#include "Underwater_Barometer.h"
#include <Wire.h>

#define Barometer_ADDR               0x76
#define Barometer_RESET              0x1E
#define Barometer_ADC_READ           0x00
#define Barometer_PROM_READ          0xA0
#define Barometer_CONVERT_D1_8192    0x4A
#define Barometer_CONVERT_D2_8192    0x5A

const float Barometer::Pa = 100.0f;
const float Barometer::bar = 0.001f;
const float Barometer::mbar = 1.0f;

const uint8_t Barometer::Barometer_30BA = 0;
const uint8_t Barometer::Barometer_02BA = 1;

Barometer::Barometer() {
  fluidDensity = 1029;
}

/* setup - run this code at the beginng to get everything set*/
void Barometer::setup(){
  Wire.begin();

  while (!init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }

  setModel(Barometer::Barometer_30BA);
  setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
}

void Barometer::display_data(){

  read();

  Serial.print("Pressure: ");
  Serial.print(pressure());
  Serial.println(" mbar");

  Serial.print("Temperature: ");
  Serial.print(temperature());
  Serial.println(" deg C");

  Serial.print("Depth: ");
  Serial.print(depth());
  Serial.println(" m");

  Serial.print("Altitude: ");
  Serial.print(altitude());
  Serial.println(" m above mean sea level");

}


bool Barometer::init() {
  // Reset the Barometer, per datasheet
  Wire.beginTransmission(Barometer_ADDR);
  Wire.write(Barometer_RESET);
  Wire.endTransmission();

  // Wait for reset to complete
  delay(10);

  // Read calibration values and CRC
  for ( uint8_t i = 0 ; i < 7 ; i++ ) {
    Wire.beginTransmission(Barometer_ADDR);
    Wire.write(Barometer_PROM_READ+i*2);
    Wire.endTransmission();

    Wire.requestFrom(Barometer_ADDR,2);
    C[i] = (Wire.read() << 8) | Wire.read();
  }

  // Verify that data is correct with CRC
  uint8_t crcRead = C[0] >> 12;
  uint8_t crcCalculated = crc4(C);

  if ( crcCalculated == crcRead ) {
    return true; // Initialization success
  }

  return false; // CRC fail
}

void Barometer::setModel(uint8_t model) {
  _model = model;
}

void Barometer::setFluidDensity(float density) {
  fluidDensity = density;
}

void Barometer::read() {
  // Request D1 conversion
  Wire.beginTransmission(Barometer_ADDR);
  Wire.write(Barometer_CONVERT_D1_8192);
  Wire.endTransmission();

  delay(20); // Max conversion time per datasheet

  Wire.beginTransmission(Barometer_ADDR);
  Wire.write(Barometer_ADC_READ);
  Wire.endTransmission();

  Wire.requestFrom(Barometer_ADDR,3);
  D1 = 0;
  D1 = Wire.read();
  D1 = (D1 << 8) | Wire.read();
  D1 = (D1 << 8) | Wire.read();

  // Request D2 conversion
  Wire.beginTransmission(Barometer_ADDR);
  Wire.write(Barometer_CONVERT_D2_8192);
  Wire.endTransmission();

  delay(20); // Max conversion time per datasheet

  Wire.beginTransmission(Barometer_ADDR);
  Wire.write(Barometer_ADC_READ);
  Wire.endTransmission();

  Wire.requestFrom(Barometer_ADDR,3);
  D2 = 0;
  D2 = Wire.read();
  D2 = (D2 << 8) | Wire.read();
  D2 = (D2 << 8) | Wire.read();

  calculate();
}

void Barometer::calculate() {
  // Given C1-C6 and D1, D2, calculated TEMP and P
  // Do conversion first and then second order temp compensation

  int32_t dT = 0;
  int64_t SENS = 0;
  int64_t OFF = 0;
  int32_t SENSi = 0;
  int32_t OFFi = 0;
  int32_t Ti = 0;
  int64_t OFF2 = 0;
  int64_t SENS2 = 0;

  // Terms called
  dT = D2-uint32_t(C[5])*256l;
  if ( _model == Barometer_02BA ) {
    SENS = int64_t(C[1])*65536l+(int64_t(C[3])*dT)/128l;
    OFF = int64_t(C[2])*131072l+(int64_t(C[4])*dT)/64l;
    P = (D1*SENS/(2097152l)-OFF)/(32768l);
  } else {
    SENS = int64_t(C[1])*32768l+(int64_t(C[3])*dT)/256l;
    OFF = int64_t(C[2])*65536l+(int64_t(C[4])*dT)/128l;
    P = (D1*SENS/(2097152l)-OFF)/(8192l);
  }

  // Temp conversion
  TEMP = 2000l+int64_t(dT)*C[6]/8388608LL;

  //Second order compensation
  if ( _model == Barometer_02BA ) {
    if((TEMP/100)<20){         //Low temp
      Serial.println("here");
      Ti = (11*int64_t(dT)*int64_t(dT))/(34359738368LL);
      OFFi = (31*(TEMP-2000)*(TEMP-2000))/8;
      SENSi = (63*(TEMP-2000)*(TEMP-2000))/32;
    }
  } else {
    if((TEMP/100)<20){         //Low temp
      Ti = (3*int64_t(dT)*int64_t(dT))/(8589934592LL);
      OFFi = (3*(TEMP-2000)*(TEMP-2000))/2;
      SENSi = (5*(TEMP-2000)*(TEMP-2000))/8;
      if((TEMP/100)<-15){    //Very low temp
        OFFi = OFFi+7*(TEMP+1500l)*(TEMP+1500l);
        SENSi = SENSi+4*(TEMP+1500l)*(TEMP+1500l);
      }
    }
    else if((TEMP/100)>=20){    //High temp
      Ti = 2*(dT*dT)/(137438953472LL);
      OFFi = (1*(TEMP-2000)*(TEMP-2000))/16;
      SENSi = 0;
    }
  }

  OFF2 = OFF-OFFi;           //Calculate pressure and temp second order
  SENS2 = SENS-SENSi;

  if ( _model == Barometer_02BA ) {
    TEMP = (TEMP-Ti);
    P = (((D1*SENS2)/2097152l-OFF2)/32768l)/100;
  } else {
    TEMP = (TEMP-Ti);
    P = (((D1*SENS2)/2097152l-OFF2)/8192l)/10;
  }
}

float Barometer::pressure(float conversion) {
  return P*conversion;
}

float Barometer::temperature() {
  return TEMP/100.0f;
}

float Barometer::depth() {
  return (pressure(Barometer::Pa)-101300)/(fluidDensity*9.80665);
}

float Barometer::altitude() {
  return (1-pow((pressure()/1013.25),.190284))*145366.45*.3048;
}


uint8_t Barometer::crc4(uint16_t n_prom[]) {
  uint16_t n_rem = 0;

  n_prom[0] = ((n_prom[0]) & 0x0FFF);
  n_prom[7] = 0;

  for ( uint8_t i = 0 ; i < 16; i++ ) {
    if ( i%2 == 1 ) {
      n_rem ^= (uint16_t)((n_prom[i>>1]) & 0x00FF);
    } else {
      n_rem ^= (uint16_t)(n_prom[i>>1] >> 8);
    }
    for ( uint8_t n_bit = 8 ; n_bit > 0 ; n_bit-- ) {
      if ( n_rem & 0x8000 ) {
        n_rem = (n_rem << 1) ^ 0x3000;
      } else {
        n_rem = (n_rem << 1);
      }
    }
  }

  n_rem = ((n_rem >> 12) & 0x000F);

  return n_rem ^ 0x00;
}
