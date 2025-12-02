/*
 * hw.c
 *
 *  Created on: Dec 2, 2025
 *      Author: lukas
 */
#include "hw.h"
  I2C_TypeDef *g_i2c = I2C1;

void SystemClock_Config(void)
{

	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
	LL_RCC_HSE_Enable();
	while (LL_RCC_HSE_IsReady() != 1) {

	}

	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9); //72 Mhz

	LL_RCC_PLL_Enable();
	while (LL_RCC_PLL_IsReady() != 1) {

	}

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);		//AHB

	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);

	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {

	}

	LL_SetSystemCoreClock(72000000);
	LL_Init1msTick(72000000);

	LL_SYSTICK_EnableIT();
}

void    GPIO_Config(void)
{

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

	LL_GPIO_InitTypeDef sVariable;
		sVariable.Pin = LL_GPIO_PIN_5;
		sVariable.Mode = LL_GPIO_MODE_OUTPUT;
		sVariable.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		sVariable.Speed = LL_GPIO_SPEED_FREQ_LOW;
		LL_GPIO_Init(GPIOA, &sVariable);

		LL_GPIO_InitTypeDef s_I2C1_SCL;
		s_I2C1_SCL.Pin = LL_GPIO_PIN_6;
		s_I2C1_SCL.Mode = LL_GPIO_MODE_ALTERNATE;
		s_I2C1_SCL.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
		//s_I2C1_SCL.Pull=;
		s_I2C1_SCL.Speed = LL_GPIO_SPEED_FREQ_LOW;
		LL_GPIO_Init(GPIOB, &s_I2C1_SCL);

		LL_GPIO_InitTypeDef s_I2C1_SDA;
		s_I2C1_SDA.Pin = LL_GPIO_PIN_7;
		s_I2C1_SDA.Mode = LL_GPIO_MODE_ALTERNATE;
		s_I2C1_SDA.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
		//s_I2C1_SDA.Pull=;
		s_I2C1_SDA.Speed = LL_GPIO_SPEED_FREQ_LOW;
		LL_GPIO_Init(GPIOB, &s_I2C1_SDA);

		LL_GPIO_InitTypeDef s_TXuart1;
		s_TXuart1.Pin = LL_GPIO_PIN_9;
		s_TXuart1.Mode = LL_GPIO_MODE_ALTERNATE;
		s_TXuart1.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		s_TXuart1.Speed = LL_GPIO_SPEED_FREQ_HIGH;
		LL_GPIO_Init(GPIOA, &s_TXuart1);

		LL_GPIO_InitTypeDef s_RXuart1;
		s_RXuart1.Pin = LL_GPIO_PIN_10;
		s_RXuart1.Mode = LL_GPIO_MODE_INPUT;
		s_RXuart1.Pull = LL_GPIO_PULL_UP;
		LL_GPIO_Init(GPIOA, &s_RXuart1);

		LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_10, LL_GPIO_PULL_UP);




}

void    USART1_Config(void){
	//LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

	LL_USART_InitTypeDef init = { 0 };

	init.BaudRate = 9600;
	init.DataWidth = LL_USART_DATAWIDTH_8B;
	init.StopBits = LL_USART_STOPBITS_1;
	init.Parity = LL_USART_PARITY_NONE;
	init.TransferDirection = LL_USART_DIRECTION_TX_RX;
	init.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	init.OverSampling = LL_USART_OVERSAMPLING_16;

	LL_RCC_ClocksTypeDef clk;
	LL_RCC_GetSystemClocksFreq(&clk);

	LL_USART_Init(USART1, &init);
	LL_USART_ConfigAsyncMode(USART1);
	LL_USART_SetBaudRate(USART1, clk.PCLK2_Frequency , 9600);

	LL_USART_Enable(USART1);
}

void    I2C1_Config(void)
{
//	  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

	    LL_I2C_Disable(g_i2c);
	    LL_I2C_EnableClockStretching(g_i2c);

	    LL_RCC_ClocksTypeDef clk;
	    LL_RCC_GetSystemClocksFreq(&clk);

	    LL_I2C_ConfigSpeed(g_i2c, clk.PCLK1_Frequency, 400000, LL_I2C_DUTYCYCLE_2);
	    LL_I2C_SetMode(g_i2c, LL_I2C_MODE_I2C);

	    LL_I2C_Enable(g_i2c);

}

void    DMA_Config(void)
{

//	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4,
			LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MEMORY_INCREMENT); // inkrement

	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PDATAALIGN_BYTE);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MDATAALIGN_BYTE);

	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PRIORITY_LOW);

	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_4,
			(uint32_t) LL_USART_DMA_GetRegAddr(USART1));

	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4);
	LL_USART_EnableDMAReq_TX(USART1);
	NVIC_SetPriority(DMA1_Channel4_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}

