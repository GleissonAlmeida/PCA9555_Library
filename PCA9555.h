/*

*/

#ifndef PCA9555_h
#define PCA9555_h

#include "Arduino.h"

#define DEFAUT_I2C_ADDR      0x20
#define INPUT_PORT_0  0
#define INPUT_PORT_1  1
#define OUTPUT_PORT_0 2
#define OUTPUT_PORT_1 3
#define POLARITY_INVERSION_PORT_0 4
#define POLARITY_INVERSION_PORT_1 5
#define CONFIGURATION_PORT_0 6
#define CONFIGURATION_PORT_1 7

#define L_ALL 0x0000
#define H_ALL 0xFFFF
#define OUT  0
#define IN   1
#define ORIGINAL 0x0000
#define INVERTED 0xFFFF


enum {
    P00, P01, P02, P03, P04, P05, P06, P07,
    P10, P11, P12, P13, P14, P15, P16, P17,
};


class PCA9555
{
  public:
    PCA9555(uint8_t address);
    bool  begin();
    void polarity(const uint16_t value);
    void  pinMode(uint8_t pin, uint8_t type);
    void  outputMode(uint16_t type);
    void digitalWrite(uint8_t pin, uint8_t value);
    void AlldigitalWrite( uint16_t value);
    uint8_t digitalRead(uint8_t pin) ;
    uint16_t AlldigitalRead();

  private:
    int _pin;
    uint8_t _address;  
    int _error;  
    uint16_t I2C_Read_value(uint8_t address, uint8_t reg);
    void I2C_wirite_value(uint8_t address, uint8_t reg, uint16_t value);
    uint16_t _config_port = 0xFFFF;
    uint16_t _valuePort = 0x0000;
    uint8_t _Byte_low;
    uint8_t _Byte_high;
    uint8_t _inputData;

};

#endif

