/*
 *  Encoder - AMT203
 *  Sets up a class to read the encoder value that uses SPI transmission
 *  If attached to the encoder failed will return 0, else 1.
 *  Contributer: Wei Lun William Chen. Date: 02/06/2018
 */
#include "Arduino.h"
#include <SPI.h>

#ifndef UNDERWATER_H
#define UNDERWATER_H

const double pi = 3.1415926;

class Encoder{
public:
    Encoder(int);
    Encoder();
    unsigned int read_value();
    int read_angle();

    void initialize_speed();
    float read_speed();
    bool attach(int);
    void set_offset(int);

    /* Useful convert functions */
    float deg2rad(float);
    float rad2deg(float);
    float deg2rpm(float);
    float rpm2deg(float);

private:
    int pin;
    int offset;
    // send SPI commands
    uint8_t SPI_transmit(uint8_t);
    // for measure speed
    int t0;
    int sita_0;
    int w[5];
    int read_index;
};
#endif
