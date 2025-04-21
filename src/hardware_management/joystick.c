#include "joystick.h"
#include "main.h" 
#include "hardware/adc.h"
#include "uart_logger.h"

/**
 * @brief Inicializa o ADC e os pinos analógicos do joystick.
 */
void joystick_init() {
    adc_init();
    adc_gpio_init(JOYSTICK_ADC_X_PIN);
    adc_gpio_init(JOYSTICK_ADC_Y_PIN);
    uart_log("Joystick Funcionando!\n");
}

/**
 * @brief Lê os valores dos eixos X e Y do joystick.
 *
 * @param x Ponteiro para armazenar o valor do eixo X (0-4095).
 * @param y Ponteiro para armazenar o valor do eixo Y (0-4095).
 */

uint16_t read_adc(uint adc_channel) {
    adc_select_input(adc_channel);
    sleep_us(5);
    return adc_read();
}