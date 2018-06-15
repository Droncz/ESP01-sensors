#ifndef DRIVER_I2C_H_
#define DRIVER_I2C_H_

#include "driver/i2c_master.h"
#include <stdint.h>
// #include <c_types.h>


#define    I2C_MASTER_WRITE 0x0   /*!< I2C write data */
#define    I2C_MASTER_READ 0x1   /*!< I2C read data */



uint8_t I2C_WriteData(uint8_t device_addr,
						uint8_t register_addr,
						uint8_t* data,
						uint8_t length);
uint8_t I2C_ReadData(uint8_t device_addr,
						uint8_t register_addr,
						uint8_t* data,
						uint8_t length);

#endif /* DRIVER_I2C_H_ */
