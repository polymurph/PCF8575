#include <msp430.h> 
#include "HAL/hal_i2c.h"
#include "HWO/pcf8575.h"


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // create object
    pcf8575_t gpio;

    // object attributes settup
    gpio.address = pcf8575_addr_0x0;
    gpio.i2c_write = hal_i2c_write;
    gpio.port_0_out = 0;
    gpio.port_1_out = 0;
    gpio.port_0_dir = 0xFF;
    gpio.port_1_dir = 0xFF;
	
    // i2c settup
	hal_i2c_init(i2c_mode_MASTER, i2c_clk_src_SMCLK, 0x0008);



	while(1)
	{
	    pcf8575_write_ports(&gpio, 0xFF, 0x00);
	    __delay_cycles(100000);
	    pcf8575_write_ports(&gpio, 0x00, 0xFF);
	    __delay_cycles(100000);
	}

	return 0;
}
