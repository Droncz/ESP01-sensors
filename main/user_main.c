#include <stdio.h>
#include <stdint.h>
// #include <stddef.h>
// #include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <esp_system.h>
// #include "esp_sta.h"
// #include "esp_wifi.h"

#include "driver/i2c_master.h"
#include "driver/gpio.h"

#include "I2C.h"
#include "BME280.h"
// #include "wifi_state_machine.h"
#include "wifi_station.h"

/******************************************************************************
 * Tato funkce je třeba k překladu. Nevím přesně proč...
*******************************************************************************/
uint32_t user_rf_cal_sector_set(void)
{
    flash_size_map size_map = system_get_flash_size_map();
    uint32_t rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}


/***********************************************************************
**** PROGRAM START *****************************************************
***********************************************************************/
void task_scan_I2C()
{
    i2c_master_gpio_init();
	printf("I2C started\r\n");
	printf("I2C_MASTER_SDA_GPIO = %d\r\n", I2C_MASTER_SDA_GPIO);
	printf("I2C_MASTER_SCL_GPIO = %d\r\n", I2C_MASTER_SCL_GPIO);


	int i;

	printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
	printf("00:         ");
	for (i=3; i< 0x78; i++) {
        i2c_master_start();
        i2c_master_writeByte((i << 1) | I2C_MASTER_WRITE);

        uint8_t espRc = i2c_master_getAck();
		i2c_master_stop();

		if (i%16 == 0) {
			printf("\n%.2x:", i);
		}
		if (espRc == 0) {
			printf(" %.2x", i);
		} else {
			printf(" --");
		}
    }

	printf("\n");

	vTaskDelete(NULL);
}

void task_setup_sensors_reading()
{
	int8_t init_status;
    int32_t temperature;
	uint32_t pressure, humidity;

    i2c_master_gpio_init();
	// printf("I2C started\r\n");
	// printf("I2C_MASTER_SDA_GPIO = %d\r\n", I2C_MASTER_SDA_GPIO);
	// printf("I2C_MASTER_SCL_GPIO = %d\r\n", I2C_MASTER_SCL_GPIO);


	init_status = BME280_Init(BME280_OS_T_16, BME280_OS_P_16, BME280_OS_H_16,
					BME280_FILTER_16, BME280_MODE_NORMAL, BME280_TSB_05);
    // printf("BME280 init status = %d.\r\n", init_status);
    if (init_status)
    	printf("BME280 init error.\r\n");
    else
    	printf("BME280 init OK.\r\n");



    while (1) {
		if(BME280_ReadAll(&temperature, &pressure, &humidity))
			printf("Sensor read error!\r\n");
		else
		{
			printf("TEPLOTA=%d.%02u\r\nTLAK=%u.%02u\r\nVLKHOST=%u.%02u\r\n",
					temperature / 100, temperature % 100,							//C
					//pressure >> 8, ((pressure & 0x000000FF) * 100) >> 8,			//Pa
					(pressure >> 8) / 100, (pressure >> 8) % 100,					//hPa
					humidity >> 10, ((humidity & 0x000003FF) * 100) >> 10);			//rH
		}
        vTaskDelay(1000);  //Delay for ... milliseconds
    }
    vTaskDelete(NULL);
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void)
{
    printf("SDK version:%s %d\n", system_get_sdk_version(), system_get_free_heap_size());
	
	// xTaskCreate(task_WiFi_connect, "task_WiFi_connect", 200, NULL, 4, NULL);
    Wifi_init();
	
    // xTaskCreate(task_scan_I2C, "task_scan_I2C", 200, NULL, 3, NULL);
	xTaskCreate(task_setup_sensors_reading, "task_setup_sensors_reading", 200, NULL, 3, NULL);

} 
