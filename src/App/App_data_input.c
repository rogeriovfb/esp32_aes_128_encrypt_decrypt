#include "App/App_data_input.h"



uint32_t snd = 0;
char str[200];

void vApp_data_input(void * pvParameters)
{
    QueueHandle_t xQueue_data_input;//Objeto da queue
    xQueue_data_input = (QueueHandle_t)pvParameters;

    while(1){
        sprintf(str, "{\"e-mail\":\"ballestrin.rogerio@gmail.com\", \"data\":%d}", snd++);
        xQueueSend(xQueue_data_input, &str, pdMS_TO_TICKS(0));//Envia a variavel para queue
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}