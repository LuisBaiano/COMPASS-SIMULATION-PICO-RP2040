#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "pico/stdlib.h"

// Inicializa o PIO para a matriz
void led_matrix_init();

// Define a cor de um único led (x, y de 0 a MATRIX_DIM-1)
// Esta função atualiza conforme o movimento do joystick
void led_matrix_set_pixel(uint8_t x, uint8_t y, uint32_t color);

// Limpa (apaga) toda a matriz
void led_matrix_clear();

#endif