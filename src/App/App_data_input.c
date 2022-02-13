#include "App/App_data_input.h"



uint32_t ui32_counter = 0;


void vApp_data_input(void * pvParameters)
{
    QueueHandle_t xQueue_data_input;
    xQueue_data_input = (QueueHandle_t)pvParameters;

    while(1){
        char str[200];
        sprintf(str, "{\"e-mail\":\"ballestrin.rogerio@gmail.com\", \"data\":%d}", ui32_counter++);
        xQueueSend(xQueue_data_input, &str, pdMS_TO_TICKS(0));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}