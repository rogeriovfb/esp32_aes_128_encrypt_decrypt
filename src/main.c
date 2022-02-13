#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_spi_flash.h"


#include "App/App_aes_128.h"
#include "App/App_data_input.h"


QueueHandle_t xQueue_data_input;
QueueHandle_t xQueue_data_output;

void print_chip_information(void);

void app_main()
{
    xQueue_data_input = xQueueCreate(10, 180);
    print_chip_information();
    xTaskCreate(&vApp_data_input, "vApp_data_input", 8192, (void*) xQueue_data_input,tskIDLE_PRIORITY, NULL);
    xTaskCreate(&vApp_aes_128, "vApp_aes_128", 8192, (void*) xQueue_data_input,tskIDLE_PRIORITY, NULL);
}


void print_chip_information(){
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
    printf("silicon revision %d, ", chip_info.revision);
    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
}

    