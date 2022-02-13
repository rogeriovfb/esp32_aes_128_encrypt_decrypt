#ifndef APP_DATA_INPUT_H_
#define APP_DATA_INPUT_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "freertos/queue.h"

void vApp_data_input( void * pvParameters);

#endif /* APP_DATA_INPUT_H_ */