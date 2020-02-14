/*
 * pcf8575.c
 *
 *  Created on: Feb 12, 2020
 *      Author: Edwin
 */

#include "pcf8575.h"
#include <stdint.h>
#include <stdbool.h>


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

void pcr8575_set_pin(pcf8575_t *device, pcf8575_pin_t pin, bool logic_high)
{
    uint8_t data[2];

    if(pin & 0x80){
        pin &= ~0x80;
        if(logic_high) {
            device->port_1_out |= (1 << pin);
        } else {
            device->port_1_out &= ~(1 << pin);
        }
    } else {
        if(logic_high) {
            device->port_0_out |= (1 << pin);
        } else {
            device->port_0_out &= ~(1 << pin);
        }
    }

    data[0] = ~(device->port_0_dir) | device->port_0_out;
    data[1] = ~(device->port_1_dir) | device->port_1_out;

    device->i2c_write((uint8_t)(device->address), data, 2);
}

void pcf8575_toggle_pin(pcf8575_t *device, pcf8575_pin_t pin)
{
    uint8_t data[2];

    if(pin & 0x80){
        pin &= ~0x80;
        device->port_1_out ^= (1 << pin);
    } else {
        device->port_0_out ^= (1 << pin);
    }

    data[0] = ~(device->port_0_dir) | device->port_0_out;
    data[1] = ~(device->port_1_dir) | device->port_1_out;

    device->i2c_write((uint8_t)(device->address), data, 2);
}

// TODO: test
void pcf8575_set_pin_dir(pcf8575_t *device, pcf8575_pin_t pin, pcf8575_dir_t direction)
{
    uint8_t data[2];

    if(pin & 0x80){
        pin &= ~0x80;
        if(direction){
            device->port_1_dir &= ~(1 << pin);
        } else {
            device->port_1_dir |= (1 << pin);
        }
    } else {
        if(direction){
            device->port_0_dir &= ~(1 << pin);
        } else {
            device->port_0_dir |= (1 << pin);
        }
    }

    data[0] = ~(device->port_0_dir) | device->port_0_out;
    data[1] = ~(device->port_1_dir) | device->port_1_out;

    device->i2c_write((uint8_t)(device->address), data, 2);
}

// TODO: test
bool pcf8575_read_pin(pcf8575_t *device, pcf8575_pin_t pin)
{
    uint8_t data[2];
    device->i2c_read((uint8_t)(device->address), data, 2);

    if(pin & 0x80){
        pin &= ~0x80;
        // TODO: check if this works : return data[2] & (1 << pin)
        return (data[1] & (1 << pin)) ? (true) : (false);
    }
    return (data[0] & (1 << pin)) ? (true) : (false);
}

