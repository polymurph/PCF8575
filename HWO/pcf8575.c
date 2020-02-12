/*
 * pcf8575.c
 *
 * Created: 18-Jan-18 15:52:16
 *  Author: Edwin
 */ 

#include "pcf8575.h"
#include "i2cmaster.h"

#ifndef FAIL
#define FAIL 1
#endif /*FAIL*/

#ifndef SUCCESS
#define SUCCESS 0
#endif /*FAIL*/
static uint8_t port0Dir = 0x00;
static uint8_t port1Dir = 0x00;

//////////////////////////////////////////////////////////////////////////
uint8_t pcf8575WriteAll(uint8_t address, uint8_t port0, uint8_t port1)
{
	// addrss settup
	address &= 0x07;
	address = address << 1;
	address |= 0x40;
	
	
	port0 = ~(port0|port0Dir);
	port1 = ~(port1|port1Dir);
	
	if(i2c_start(address) == !FAIL)
	{
		i2c_stop();
		return FAIL;
	}
	if(i2c_write(port0) == !FAIL)
	{
		i2c_stop();
		return FAIL;
	}
	if(i2c_write(port1) == !FAIL)
	{
		i2c_stop();
		return FAIL;
	}
	i2c_stop();
	return SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
uint8_t pcf8575ReadAll(uint8_t address, uint8_t* port1, uint8_t* port2)
{
	// addrss settup
	address &= 0x07;
	address = address << 1;
	address |= 0x40;
	
	// setting read bit 
	address |= I2C_READ;
	
	if(i2c_start(address) == !FAIL)
	{
		i2c_stop();
		return FAIL;
	}
	
	
	if(i2c_write(~port0Dir) == FAIL)
	{
		i2c_stop();
		return FAIL;
	}
	if(i2c_write(~port1Dir) == FAIL)
	{
		i2c_stop();
		return FAIL;
	}
	
	*port1 = i2c_readAck();
	*port2 = i2c_readAck();
	i2c_stop();
	return SUCCESS;
}

/*
	set '1' for input and 0 for output!
*/
uint8_t pcf8575Config(uint8_t address,uint8_t port0conf, uint8_t port1conf)
{
	// initialize i2c
	i2c_init();
	port0Dir = port0conf;
	port1Dir = port1conf;
	
	//port0conf = ~port0conf;
	//port1conf = ~port1conf;
	
	pcf8575WriteAll(address,port0conf,port1conf);
	return SUCCESS;
	/*;
	if(pcf8575WriteToDevice(address,port1conf,port2conf))
	{
		return SUCCESS;
	}
	return FAIL;
	*/
}

uint8_t pcf8575ReadPin(uint8_t address,pcf8575Port_t port,pcf8575Pin_t pin)
{
	unsigned char port0;
	unsigned char port1;
	
	//read ports
	pcf8575ReadAll(address,&port0,&port1);
	
	if(port)
	{
		if(port0 &= pin)
		{
			return 1;
		}
		return 0;
	}
	else
	{
		if(port1 &= pin)
		{
			return 1;
		}
		return 0;
	}
}

uint8_t pcf8575ReadIOConfig()
{
	// TODO:
	return SUCCESS;
}