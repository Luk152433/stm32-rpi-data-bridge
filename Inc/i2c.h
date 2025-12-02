#ifndef I2C_H_
#define I2C_H_


#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_i2c.h"


int32_t i2c_reg_write(I2C_TypeDef *i2c, uint16_t slave_addr, uint16_t reg_addr, uint8_t *data_ptr, uint16_t size);
int32_t i2c_reg_read(I2C_TypeDef *i2c, uint16_t slave_addr, uint16_t reg_addr, uint8_t *read_data_ptr, uint16_t read_size);

#endif /* I2C_H_ */
