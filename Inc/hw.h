/*
 * hw.h
 *
 *  Created on: Dec 2, 2025
 *      Author: lukas
 */

#ifndef HW_H_
#define HW_H_

#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_i2c.h"


extern I2C_TypeDef *g_i2c;
void SystemClock_Config(void);
void    GPIO_Config(void);
void    USART1_Config(void);
void    I2C1_Config(void);
void    DMA_Config(void);

#endif /* HW_H_ */
