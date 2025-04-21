#ifndef RGB_LED_H
#define RGB_LED_H

#include "pico/stdlib.h"

void rgb_led_init();

// Define R, G, B  na escala de (0-255)
void rgb_led_set(uint8_t r, uint8_t g, uint8_t b);

// Atualiza as cores verde e azul com base no Joystick
void rgb_led_update_from_joystick(uint16_t adc_x, uint16_t adc_y);

#endif