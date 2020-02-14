/*
 * pcf8575.h
 *
 *  Created on: Feb 12, 2020
 *      Author: Edwin
 */

#ifndef HWO_PCF8575_H_
#define HWO_PCF8575_H_

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t (*i2c_rx_cb_t)(uint8_t, uint8_t*, uint8_t);
typedef uint8_t (*i2c_tx_cb_t)(uint8_t, const uint8_t*, uint8_t);

typedef enum {
 pcf8575_addr_0x0 = 0b00100000,
 pcf8575_addr_0x1 = 0b00100001,
 pcf8575_addr_0x2 = 0b00100010,
 pcf8575_addr_0x3 = 0b00100011,
 pcf8575_addr_0x4 = 0b00100100,
 pcf8575_addr_0x5 = 0b00100101,
 pcf8575_addr_0x6 = 0b00100110,
 pcf8575_addr_0x7 = 0b00100111
}pcf8575_addr_t;

typedef enum{
    pcf8575_pin_0_0 = 0x00,
    pcf8575_pin_0_1,
    pcf8575_pin_0_2,
    pcf8575_pin_0_3,
    pcf8575_pin_0_4,
    pcf8575_pin_0_5,
    pcf8575_pin_0_6,
    pcf8575_pin_0_7,
    pcf8575_pin_1_0 = 0x80,
    pcf8575_pin_1_1,
    pcf8575_pin_1_2,
    pcf8575_pin_1_3,
    pcf8575_pin_1_4,
    pcf8575_pin_1_5,
    pcf8575_pin_1_6,
    pcf8575_pin_1_7
}pcf8575_pin_t;

typedef enum {
    pcf8575_dir_IN,
    pcf8575_dir_OUT
}pcf8575_dir_t;

typedef struct {
    pcf8575_addr_t address;
    i2c_rx_cb_t i2c_read;
    i2c_tx_cb_t i2c_write;
    uint8_t port_0_dir;
    uint8_t port_1_dir;
    uint8_t port_0_out;
    uint8_t port_1_out;

}pcf8575_t;

void pcf8575_init(pcf8575_t *device,
                  pcf8575_addr_t address,
                  uint8_t port_0_dir,
                  uint8_t port_1_dir,
                  uint8_t port_0_out,
                  uint8_t port_1_out
                  );

void pcf8575_set_directions(pcf8575_t *device, uint8_t port_0_dir, uint8_t port_1_dir);

void pcf8575_write_ports(pcf8575_t *device, uint8_t port_0, uint8_t port_1);

void pcr8575_set_pin(pcf8575_t *device, pcf8575_pin_t pin, bool logic_high);

void pcf8575_toggle_pin(pcf8575_t *device, pcf8575_pin_t pin);

void pcf8575_set_pin_dir(pcf8575_t *device, pcf8575_pin_t pin, pcf8575_dir_t direction);

bool pcf8575_read_pin(pcf8575_t *device, pcf8575_pin_t pin);

#endif /* HWO_PCF8575_H_ */
