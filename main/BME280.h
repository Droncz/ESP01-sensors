
#ifndef _BME280_H_
#define _BME280_H_

// #include <c_types.h>
#include <stdint.h>
#include <string.h>

//Device Address
// #define BME280_I2C_ADDR		0xEC	//0xEC or 0xEE
#define BME280_I2C_ADDR		0x76

//Configuration parameters

//Temperature oversampling
#define BME280_OS_T_SKP		0x00
#define BME280_OS_T_1		0x01
#define BME280_OS_T_2		0x02
#define BME280_OS_T_4		0x03
#define BME280_OS_T_8		0x04
#define BME280_OS_T_16		0x05

//Pressure oversampling
#define BME280_OS_P_SKP		0x00
#define BME280_OS_P_1		0x01
#define BME280_OS_P_2		0x02
#define BME280_OS_P_4		0x03
#define BME280_OS_P_8		0x04
#define BME280_OS_P_16		0x05

//Humidity oversampling
#define BME280_OS_H_SKP		0x00
#define BME280_OS_H_1		0x01
#define BME280_OS_H_2		0x02
#define BME280_OS_H_4		0x03
#define BME280_OS_H_8		0x04
#define BME280_OS_H_16		0x05

//Filter coefficient
#define BME280_FILTER_OFF	0x00
#define BME280_FILTER_2		0x01
#define BME280_FILTER_4		0x02
#define BME280_FILTER_8		0x03
#define BME280_FILTER_16	0x04

//Mode
#define BME280_MODE_SLEEP	0x00
#define BME280_MODE_FORCED	0x01
#define BME280_MODE_NORMAL	0x03

//Standby time - ms
#define BME280_TSB_05		0x00	// 0.5
#define BME280_TSB_62		0x01	//62.5
#define BME280_TSB_125		0x02
#define BME280_TSB_250		0x03
#define BME280_TSB_500		0x04
#define BME280_TSB_1000		0x05
#define BME280_TSB_10		0x06
#define BME280_TSB_20		0x07


//User API
uint8_t BME280_Init(uint8_t os_t, uint8_t os_p, uint8_t os_h,
					uint8_t filter, uint8_t mode, uint8_t t_sb);
uint8_t BME280_ReadAll(int32_t* t, uint32_t* p, uint32_t* h);
uint8_t BME280_SetMode(uint8_t mode);

#endif /* _BME280_H_ */
