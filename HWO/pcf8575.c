/*
 * pcf8575.c
 *
 *  Created on: Feb 12, 2020
 *      Author: Edwin
 */

#include "pcf8575.h"
#include <stdint.h>


void pcf8575_set_directions(pcf8575_t *device, uint8_t port_0_dir, uint8_t port_1_dir)
{
    uint8_t data[2];

    device->port_0_dir = port_0_dir;
    device->port_1_dir = port_1_dir;

    data[0] = ~port_0_dir;
    data[1] = ~port_1_dir;

    device->i2c_write((uint8_t)(device->address), data, 2);
}

void pcf8575_write_ports(pcf8575_t *device, uint8_t port_0, uint8_t port_1)
{
    uint8_t data[2];

    device->port_0_out = port_0;
    device->port_1_out = port_1;

    data[0] = ~(device->port_0_dir) | port_0;
    data[1] = ~(device->port_1_dir) | port_1;

    device->i2c_write((uint8_t)(device->address), data, 2);

}
