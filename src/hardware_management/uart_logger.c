#include "uart_logger.h"
#include "main.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <stdio.h>

/**
 * @brief Inicializa a comunicação UART com os parâmetros definidos.
 *        Configura o pino TX e RX para a função UART.
 *        Configura o formato da UART e desabilita o FIFO.
 *        Aguarda a estabilização do UART antes de prosseguir.
 */
void uart_logger_init() {
    uart_init(UART_ID, UART_BAUD_RATE);  // Inicializa a UART com a taxa de bauds definida
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);  // Configura o pino TX
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);  // Configura o pino RX
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);  // Configura a UART com 8 bits, 1 bit de parada, sem paridade
    uart_set_fifo_enabled(UART_ID, false);  // Desabilita FIFO para uma comunicação simples
    sleep_ms(100);  // Aguarda o tempo de estabilização da UART
    uart_log("UART Inicializada!\n");  // Log de inicialização da UART
}


void uart_log(const char *format, ...) {
    char buffer[128];
    va_list args;
    
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args); // Formata a string
    va_end(args);
    
    printf("%s", buffer); // Envia via UART

}