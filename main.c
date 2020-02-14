#include <msp430.h> 
#include <stdbool.h>
#include <stdint.h>
#include "HAL/hal_i2c.h"
#include "HWO/pcf8575.h"


#define read_test

#ifdef read_test

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // create object
    pcf8575_t gpio;

    // object attributes settup
    gpio.address = pcf8575_addr_0x0;
    gpio.i2c_read = hal_i2c_read;
    gpio.i2c_write = hal_i2c_write;
    gpio.port_0_out = 0;
    gpio.port_1_out = 0;
    gpio.port_0_dir = 0xFF;
    gpio.port_1_dir = 0xFF;

    // i2c settup
    hal_i2c_init(i2c_mode_MASTER, i2c_clk_src_SMCLK, 0x0008);

    //pcf8575_set_directions(&gpio, 0xFF, 0xFE);

    pcf8575_write_ports(&gpio, 0xFF, 0xFE);

    while(1)
    {
/*
        if(pcf8575_read_pin(&gpio, pcf8575_pin_1_0)) {

        }*/
        pcf8575_toggle_pin(&gpio, pcf8575_pin_1_3);
        __delay_cycles(1000);
    }

    return 0;
}
#endif // read_test


#ifdef blinki
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // create object
    pcf8575_t gpio;

    // object attributes settup
    gpio.address = pcf8575_addr_0x0;
    gpio.i2c_read = hal_i2c_read;
    gpio.i2c_write = hal_i2c_write;
    gpio.port_0_out = 0;
    gpio.port_1_out = 0;
    gpio.port_0_dir = 0xFF;
    gpio.port_1_dir = 0xFF;
	
    // i2c settup
	hal_i2c_init(i2c_mode_MASTER, i2c_clk_src_SMCLK, 0x0008);



	while(1)
	{
	    //pcf8575_write_ports(&gpio, 0xFF, 0x00);
	    //pcr8575_set_pin(&gpio,pcf8575_pin_1_3, false);
	    pcf8575_toggle_pin(&gpio, pcf8575_pin_1_3);
	    __delay_cycles(100000);
	    //pcf8575_write_ports(&gpio, 0x00, 0xFF);
	    //pcr8575_set_pin(&gpio,pcf8575_pin_1_3, true);
	    //__delay_cycles(100000);
	}

	return 0;
}
#endif // blinki
