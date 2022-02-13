#ifndef APP_AES_128_H_
#define APP_AES_128_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "string.h"
#include "math.h"
#include "freertos/queue.h"
#include "aes/esp_aes.h" 

 typedef enum
    {   SM_AES_128_SET_KEY,
        SM_AES_128_CHECK_QUEUE,
        SM_AES_128_SPLIT_DATA,
        SM_AES_128_ENCRYPT_DATA,
        SM_AES_128_OUTPUT
    }xSm_Aes_128_e;

void vApp_aes_128( void * pvParameters);

#endif /* APP_AES_128_H_ */