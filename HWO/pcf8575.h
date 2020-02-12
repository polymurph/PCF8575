/*
 * pcf8575.h
 *
 * Created: 18-Jan-18 15:52:33
 *  Author: Edwin
 */ 
#ifndef PCF8575_H_
#define PCF8575_H_

#include <avr/io.h>
#include <stdint.h>
#include "i2cmaster.h"

typedef enum pcf8575Port_e{
	pcfPORT0 = 1,
	pcfPORT1 = 0
}pcf8575Port_t;

typedef enum pcf8575Pin_e{
	pcfPIN0 = 0x01,
	pcfPIN1 = 0x02,
	pcfPIN2 = 0x04,
	pcfPIN3 = 0x08,
	pcfPIN4 = 0x10,
	pcfPIN5 = 0x20,
	pcfPIN6 = 0x40,
	pcfPIN7 = 0x80
}pcf8575Pin_t;

/**
 * \brief Writes to device.
 *		  Only pass the address setting A0-A2 starting from LSB (e.g. 0bxxxxx A2 A1 A0). This function will
 *		  automatically add the needed rest of the address.
 *		  Both registers are written. If an I/O pin is configured as a input this function will automatic
 *		  write a logic "1" to the pin (see data sheet for further information).
 *		  The output settings for port1 and 2 is to be passed over with the parameters "port1, port2".
 * 
 * \param address
 * \param port1
 * \param port2
 * 
 * \return int
 */
uint8_t pcf8575WriteAll(uint8_t address, uint8_t port1, uint8_t port2);

/**
 * \brief Reads both ports.
 *		  Only pass the address setting A0-A2 starting from LSB (e.g. 0bxxxxx A2 A1 A0). This function will
 *		  automatically add the needed rest of the address.
 *		  Both registers are read. The content is then returned by writing the read content to the pointed
 *	      location of port1 and port2.	
 *	
 * \param address
 * \param port1
 * \param port2
 * 
 * \return int
 */
uint8_t pcf8575ReadAll(uint8_t address, uint8_t* port1, uint8_t* port2);

/**
 * \brief 
 * 
 * \param address
 * \param port1conf
 * \param port2conf
 * 
 * \return int
 */
uint8_t pcf8575Config(uint8_t address,uint8_t port0conf, uint8_t port1conf);

/**
 * \brief 
 * 
 * \param address
 * \param port
 * \param pin
 * 
 * \return int
 */
uint8_t pcf8575ReadPin(uint8_t address,pcf8575Port_t port,pcf8575Pin_t pin);

#endif /* PCF8575_H_ */