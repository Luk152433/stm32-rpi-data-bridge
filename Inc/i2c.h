#ifndef I2C_H_
#define I2C_H_

#include "main.h"


int32_t i2c_reg_write(I2C_TypeDef *i2c, uint16_t slave_addr, uint16_t reg_addr, uint8_t *data_ptr, uint16_t size);
int32_t i2c_reg_read(I2C_TypeDef *i2c, uint16_t slave_addr, uint16_t reg_addr, uint8_t *read_data_ptr, uint16_t read_size);

#endif /* I2C_H_ */
