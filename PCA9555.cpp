	/*

	*/

	#include "Arduino.h"
	#include "PCA9555.h"
	#include "Wire.h"

/**************************************************************************/
	PCA9555::PCA9555(uint8_t address)
	{
	  _address         = address;        // save the address id
	  Wire.begin();                      // start I2C communication
	}
/**************************************************************************/
	bool  PCA9555::begin()
	{
	  //Wire.beginTransmission(_address);
		//Wire.write(0x02); // Test Address
		_error = Wire.endTransmission();
	 if(_error != 0){
		  return false;
		}else{
		  return true;
		}
	}
/**************************************************************************/
/*!
    @name     I2C_wirite_value
    @brief    Funçao para enviar dados pela I2C.
    @param    address - Enderesso I2C do PCA9555.
    @param    reg - Registro do PCA9555 
	@param    value - Dados para envio  
    @return   nothing
*/
 void PCA9555::I2C_wirite_value(uint8_t address, uint8_t reg, uint16_t value){

   _Byte_low  =value & 0xff;
   _Byte_high = (value >> 8);

    Wire.beginTransmission(address);               
    Wire.write(reg);                               
    Wire.write(_Byte_low);                         
	Wire.write(_Byte_high);                        
    _error = Wire.endTransmission();               
  }
/**************************************************************************/
/*!
    @name     polarity
    @brief    Funçao para inverter o estado so I/0 do PCA9555 quando definido como entrada.
    @param    uint16_t value - pinos que serao invertidos.
    @return   nothing
*/
void PCA9555::polarity(uint16_t value){
	I2C_wirite_value(_address, POLARITY_INVERSION_PORT_0, value);
}
/**************************************************************************/
/*!
    @name     pinMode
    @brief    Funçao para definir se o pino e uma entrada ou saida
    @param    pin - pino do PCA9555.
    @param    type - 0 = entrada / 1 = saida.
    @return   nothing
*/
  void PCA9555::pinMode(uint8_t pin, uint8_t type) {

  if (pin <= 15) {                                  
    if(type == OUTPUT){
    _config_port = _config_port & ~(1 << pin);
    }else{
      _config_port = _config_port | (1 << pin);
    }
    }

	I2C_wirite_value(_address, CONFIGURATION_PORT_0, _config_port);
  }
  /**************************************************************************/
/*!
    @name     outputMode
    @brief    Funçao para definir quais pisnos são entrada ou saida
    @param    type - 0 = entrada / 1 = saida.
    @return   nothing
*/
  void PCA9555::outputMode(uint16_t type) {
	_config_port = type;
	I2C_wirite_value(_address, CONFIGURATION_PORT_0, _config_port);
  }

 /**************************************************************************/
 /*!
    @name     digitalWrite
    @brief    Funçao para definir o oestado logico de um pino.
    @param    pin - pino do PCA9555.
    @param    type - 0 = LOW / 1 = HIGH.
    @return   nothing
*/
  void PCA9555::digitalWrite(uint8_t pin, uint8_t value) {
    if (pin > 15 ){
        _error = 255;            // invalid pin
        return;                  // exit
    }
    if (value > 0) {
        _valuePort = _valuePort | (1 << pin);    // and OR bit in register
    } else {
        _valuePort = _valuePort & ~(1 << pin);    // AND all bits
    }

I2C_wirite_value(_address, OUTPUT_PORT_0, _valuePort);
}
 /**************************************************************************/
  /*!
    @name     AlldigitalWrite
    @brief    Funçao para definir o oestado logico de todos os pinos.
    @param    type - 0 = LOW / 1 = HIGH.
    @return   nothing
*/
  void PCA9555::AlldigitalWrite( uint16_t value) {
	_valuePort = value;
	I2C_wirite_value(_address, OUTPUT_PORT_0, _valuePort);
}
 /**************************************************************************/
   /*!
    @name     I2C_Read_value
    @brief    Funçao para ler um parametro na rede I2C.
    @param    address - Enderesso I2C do PCA9555.
    @param    reg - Registro do PCA9555 
    @return   _inputData
*/
uint16_t PCA9555::I2C_Read_value(uint8_t address, uint8_t reg){
 uint16_t _dataread;
 Wire.beginTransmission(address); 
 Wire.write(reg);
_error = Wire.endTransmission();
if (Wire.requestFrom((int)address, 1) != 1)
    {
        return 256; 
    };
	 _inputData = Wire.read();
    return _inputData;
}
 /**************************************************************************/
    /*!
    @name     digitalRead
    @brief    Funçao para ler um pino do PCA9555.
    @param    address - Enderesso I2C do PCA9555.
    @param    reg - Registro do PCA9555 
    @return   _inputData
*/
uint8_t PCA9555::digitalRead(uint8_t pin) {

 if (pin > 15 ) return 255;
  _inputData  = I2C_Read_value(_address, INPUT_PORT_0);
  _inputData |= I2C_Read_value(_address, INPUT_PORT_1) << 8;

if ((_inputData & (1 << pin)) > 0){

        return HIGH;
    } else {
        return LOW;
    }

}
 /**************************************************************************/
    /*!
    @name     AlldigitalRead
    @brief    Funçao para ler todos os pinos do PCA9555.
    @param    nothing
    @return   _inputData
*/
uint16_t PCA9555::AlldigitalRead() {

 if (pin > 15 ) return 255;
  _inputData  = I2C_Read_value(_address, INPUT_PORT_0);
  _inputData |= I2C_Read_value(_address, INPUT_PORT_1) << 8;

   return LOW;
}
