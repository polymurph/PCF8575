/*
 * pcf8575.h
 *
 *  Created on: Feb 12, 2020
 *      Author: Edwin
 */

#ifndef HWO_PCF8575_H_
#define HWO_PCF8575_H_

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

typedef struct {
    pcf8575_addr_t address;
}pcf8575_t;

void pcf8575_init(pcf8575_t *device, pcf8575_addr_t address, );

#endif /* HWO_PCF8575_H_ */
