#include "App/App_aes_128.h"

char c_queue_buffer[170], input_string[20][16]={0};
 uint8_t ui8_chuncks=0, ui8_ciphertext[20][16]={0}, ui8_decrypted[20][16]={0};

xSm_Aes_128_e xSm_Aes_128 = SM_AES_128_SET_KEY;
esp_aes_context aes;
    
const uint8_t ui8_key[16] = {
    0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70
};

void vApp_aes_128( void * pvParameters)
{
    QueueHandle_t xQueue_data_input;//Objeto da queue
    xQueue_data_input = (QueueHandle_t)pvParameters;


    while(1){
        switch (xSm_Aes_128)
        {
        case SM_AES_128_SET_KEY:
            printf("Setting encrypt key\n");
            esp_aes_init(&aes);
            esp_aes_setkey(&aes, (const unsigned char*) ui8_key, 128);
            xSm_Aes_128 = SM_AES_128_CHECK_QUEUE;
            break;

        case SM_AES_128_CHECK_QUEUE:

            if (xQueueReceive(xQueue_data_input, &c_queue_buffer, pdMS_TO_TICKS(100)) == true){
                xSm_Aes_128 = SM_AES_128_SPLIT_DATA;
                continue;
            }
            else{
                break;
            }
                
        case SM_AES_128_SPLIT_DATA:
            ui8_chuncks = (int)ceil(((float)strlen(c_queue_buffer))/16);
            for (int i=0; i<ui8_chuncks; i++){
                for (int k=0; k<16; k++){
                        if(strlen(c_queue_buffer) >= 16*i+k){
                            input_string[i][k] = c_queue_buffer[16*i+k];
                        }
                        else{
                            input_string[i][k] =0x00;
                        }
                }
            }
            xSm_Aes_128 = SM_AES_128_ENCRYPT_DATA;
            continue;

        case SM_AES_128_ENCRYPT_DATA:
            for (int i=0; i<ui8_chuncks; i++){
                esp_aes_crypt_ecb(&aes, ESP_AES_ENCRYPT, (const unsigned char*)input_string[i], ui8_ciphertext[i]);
            }
            xSm_Aes_128 = SM_AES_128_OUTPUT;
            continue;

        case SM_AES_128_OUTPUT:
        
            for (int i=0; i<ui8_chuncks; i++){
                esp_aes_crypt_ecb(&aes, ESP_AES_DECRYPT, (const unsigned char*)ui8_ciphertext[i], ui8_decrypted[i]);
            }

            printf("\nEncrypted: ");
            for (int i=0; i<ui8_chuncks; i++){
                for (int k=0; k<16; k++){
                    printf("%02X", ui8_ciphertext[i][k]);
                }
            }

            printf("\nDecrypted: ");
            for (int i=0; i<ui8_chuncks; i++){
                for (int k=0; k<16; k++){
                    printf("%c", ui8_decrypted[i][k]);
                }
            }
            xSm_Aes_128 = SM_AES_128_CHECK_QUEUE;
            break;
        default:
            break;
        }
    }
}