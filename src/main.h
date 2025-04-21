#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hardware_management/uart_logger.h"
#include "hardware_management/joystick.h"
#include "hardware_management/rgb_led.h"
#include "hardware_management/led_matrix.h"
#include "hardware_management/buzzer.h"
#include "hardware_management/buttons.h"
#include "hardware_management/display.h"

// --- Definições de Pinos ---

#define JOYSTICK_ADC_X_PIN  26
#define JOYSTICK_ADC_Y_PIN  27
#define JOYSTICK_BTN_PIN    22
#define JOYSTICK_ADC_X_CHAN 0
#define JOYSTICK_ADC_Y_CHAN 1

#define BUTTON_A_PIN    5
#define BUTTON_B_PIN    6

#define LED_RED_PIN     13
#define LED_GREEN_PIN   11
#define LED_BLUE_PIN    12

#define MATRIX_WS2812_PIN 7
#define MATRIX_SIZE       25
#define MATRIX_DIM        5  

#define BUZZER_PIN1 10 
#define BUZZER_PIN2 21 

#define I2C_PORT        i2c1
#define I2C_SDA_PIN     14
#define I2C_SCL_PIN     15
#define DISPLAY_ADDR    0x3C
#define DISPLAY_WIDTH   128
#define DISPLAY_HEIGHT  64

#define UART_ID         uart0
#define UART_BAUD_RATE  115200
#define UART_TX_PIN     0
#define UART_RX_PIN     1

// --- Constantes ---
#define DEBOUNCE_TIME_US 200000
#define LED_PWM_WRAP     255
#define ADC_MAX_VALUE    4095
#define ADC_CENTER       (ADC_MAX_VALUE / 2)
#define ADC_DEADZONE     180
#define SQUARE_SIZE      8

#endif 