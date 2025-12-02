/*
 * Frame2.h
 *
 *  Created on: Dec 2, 2025
 *      Author: lukas
 */

#ifndef FRAME_H_
#define FRAME_H_

#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint16_t sof;
    uint32_t timestamp;
    int16_t  temp;
    uint16_t press;
    uint16_t hum;
    uint16_t crc;
} DataFrame_t;

uint16_t CRC16_CCITT(const uint8_t *data, uint16_t length);

#endif /* FRAME_H_ */
