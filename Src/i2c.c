#include "i2c.h"

int32_t i2c_reg_write(I2C_TypeDef *i2c, uint16_t slave_addr, uint16_t reg_addr, uint8_t *data_ptr, uint16_t size)
{
	uint8_t data_count = size;
	LL_I2C_GenerateStartCondition(i2c);
	while (!LL_I2C_IsActiveFlag_SB(i2c))
			;

	LL_I2C_TransmitData8(i2c, (slave_addr << 1) | 0);
	while (!LL_I2C_IsActiveFlag_ADDR(i2c))
		;
	LL_I2C_ClearFlag_ADDR(i2c);

	while (LL_I2C_IsActiveFlag_TXE(i2c) == 0)
		;

	LL_I2C_TransmitData8(i2c, reg_addr);

	while (data_count > 0) {
		while (LL_I2C_IsActiveFlag_TXE(i2c) == 0)
			;

		LL_I2C_TransmitData8(i2c, *data_ptr);

		data_ptr++;
		data_count--;
	}
	while (LL_I2C_IsActiveFlag_TXE(i2c) == 0)
			;
	//while (LL_I2C_IsActiveFlag_STOP(i2c) == 0)
	//	;
	LL_I2C_GenerateStopCondition(i2c);
	//LL_I2C_ClearFlag_STOP(i2c);

	return 0;
}

int32_t i2c_reg_read(I2C_TypeDef *i2c, uint16_t slave_addr, uint16_t reg_addr, uint8_t *read_data_ptr, uint16_t read_size)
{

	LL_I2C_GenerateStartCondition(i2c);
	while (!LL_I2C_IsActiveFlag_SB(i2c))
		;

	LL_I2C_TransmitData8(i2c, (slave_addr << 1) | 0);

	while (!LL_I2C_IsActiveFlag_ADDR(i2c))
		;
	LL_I2C_ClearFlag_ADDR(i2c);

	while (!LL_I2C_IsActiveFlag_TXE(i2c))
		;
	LL_I2C_TransmitData8(i2c, reg_addr);

	LL_I2C_GenerateStartCondition(i2c);
	while (!LL_I2C_IsActiveFlag_SB(i2c))
		;

	LL_I2C_TransmitData8(i2c, (slave_addr << 1) | 1);
	while (!LL_I2C_IsActiveFlag_ADDR(i2c))
		;

	LL_I2C_ClearFlag_ADDR(i2c);

	for (uint16_t i = 0; i < read_size; i++) {

		if (i == (read_size - 1))
			LL_I2C_AcknowledgeNextData(i2c, LL_I2C_NACK); // NACK na końcu
		else
			LL_I2C_AcknowledgeNextData(i2c, LL_I2C_ACK);

		while (!LL_I2C_IsActiveFlag_RXNE(i2c))
			;
		read_data_ptr[i] = LL_I2C_ReceiveData8(i2c);

	}

	LL_I2C_GenerateStopCondition(i2c);
	return 0;
}
