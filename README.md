# AES-128 EBC Encrypt and Decrypt with ESP32
Firmware para criptografia de dados utilizando AES-128 no ESP32.
Projeto feito no PlatformIO, Core 5.2.5.

Placa: ESP32 Devkit

## Data Input
Os dados entram através da fila xQueue_data_input.
A entrada de dados é uma string de até 200 caracteres.

## Data Output
A saída de dados não está implementada. Apenas imprimindo a informação na tela.

## Zero Padding
Os dados de entrada não precisam ser multiplos de 16 bytes, uma vez que é realizado o zero padding no vApp_aes_128.