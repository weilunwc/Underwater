#include "Underwater_Encoder.h"

/*
 *  Encoder & attach: connects the encoder and activate
 *  SPI communication
 */
Encoder::Encoder(){
    pin = NULL;
    offset = 0;
}


Encoder::Encoder(int pin){
    attach(pin);
}

bool Encoder::attach(int pin){

    if(this->pin != NULL){
        return 0;
    }
    this->pin = pin;
    offset = 0;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV32);
    delay(2000);
    SPI.end();
    return 1;
}


void Encoder::set_offset(int offset){
    this->offset = offset;
}


/*
 *  read_angle - returns the angle of the encoder(-179 - 180)
 */
int Encoder::read_angle(){
    // check if pin is attached
    if(pin == NULL) return -1000;
    int value = read_value() - offset;
    if(value < 0) value = value + 4096;

    int current_angle = (float)(4096 - value) * 360/4096;
    if(current_angle > 180) current_angle = current_angle - 360;
    return current_angle;
}

/*
 * 	initialize_speed - initializes the info to measure speed
 */
void Encoder::initialize_speed(){
    t0 = millis();
    sita_0 = read_angle();
    read_index = 0;
    for(int i = 0;i < 5;i++){
        w[i] = 0;
    }
}

/*
 *	read_speed - returns the speed of the motor (rpm)
 *	note remember to call initialize_speed first at the setup to initialize
 */
float Encoder::read_speed(){
    int sita_1 = read_angle();

    float delta_angle = sita_1 - sita_0;

    // assuming won't run such far during two calls
    if(abs(delta_angle) > 180){
        if(sita_1 < 0) delta_angle = 360.0 + delta_angle;
        else delta_angle = -(360.0 - delta_angle);
    }
    int t1 = millis();
    float dt = t1 - t0;
    float w1 = 1000.0*delta_angle/dt;
    t0 = t1;
    sita_0 = sita_1;
    
    w[read_index] = deg2rpm(w1);
    read_index += 1;
    if(read_index >= 5) read_index = 0;
    
    /* Moving average */
    float w_now = 0;
    for(int i = 0;i < 5;i++){
        w_now += w[i];
    }
    w_now = w_now/5.0;

    return w_now;
}


/*
 *  read_position - returns the value of the encoder(0-4095)
 */
unsigned int Encoder::read_value() {
    // check if pin is attached
    if(pin == NULL) return -1;

    uint8_t temp[2];
    uint8_t recieved = 0;
    uint16_t position = 0;

    // start transmission
    SPI.begin();
    digitalWrite(pin, LOW);

    // issue read command
    SPI_transmit(0x10);

    /* loop while pin is not ready to send */
    while (recieved != 0x10){
        recieved = SPI_transmit(0x00);
        delay(2);
    }

    // receive MSB
    temp[0] = SPI_transmit(0x00);
    // receive LSB
    temp[1] = SPI_transmit(0x00);

    digitalWrite(pin, HIGH);
    SPI.end();

    // mask out first 4 bits
    temp[0] &= ~ 0xF0;

    // shift MSB to correct position
    position = temp[0] << 8;
    // add LSB to position to complete message
    position += temp[1];    // add LSB to abs_position message to complete message

    delay(5);
    //position = position - offset + 4096;
    return position;
}


/*
 *  SPI_transmit : Repetive SPI transmit sequence that sends and receives info
 */
uint8_t Encoder::SPI_transmit(uint8_t msg){
    uint8_t msg_received;
    // select SPI device
    digitalWrite(pin, LOW);
    msg_received = SPI.transfer(msg);
    // deselect SPI device
    digitalWrite(pin, HIGH);
    return msg_received;
}

float Encoder::deg2rad(float deg){
    return deg*pi/180.0;
}

float Encoder::rad2deg(float rad){
    return rad*180.0/pi;
}

// input deg/s
float Encoder::deg2rpm(float deg){
    return deg*60.0/360.0;
}

// input deg/s
float Encoder::rpm2deg(float rpm){
    return rpm*360.0/60.0;
}
