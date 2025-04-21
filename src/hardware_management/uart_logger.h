#ifndef UART_LOGGER_H
#define UART_LOGGER_H

#include <stdarg.h>

// Inicializa a interface UART para logging
void uart_logger_init();

// Envia uma string formatada pela UART
void uart_log(const char *format, ...);

#endif // UART_LOGGER_H