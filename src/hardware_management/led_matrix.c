#include "led_matrix.h"
#include "main.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "uart_logger.h"
#include "led_matrix.pio.h"


static PIO pio = pio0;
static uint sm = 0;

/**
 * @brief Inicializa a matriz de LEDs WS2812 usando PIO.
 *        Carrega o programa PIO e limpa a matriz.
 */
void led_matrix_init() {
    uint offset = pio_add_program(pio, &led_matrix_program);
    led_matrix_program_init(pio, sm, offset, MATRIX_WS2812_PIN);
    led_matrix_clear();
    uart_log("Matriz de Led inicializada!\n");
}

/**
 * @brief Define um único pixel na matriz com a cor especificada.
 *        Todos os outros pixels são apagados.
 *
 * @param x     Posição X do pixel (0 até MATRIX_DIM - 1).
 * @param y     Posição Y do pixel (0 até MATRIX_DIM - 1).
 * @param color Cor no formato 0x00RRGGBB (usado por WS2812).
 */
void led_matrix_set_pixel(uint8_t x, uint8_t y, uint32_t color) {
    if (x >= MATRIX_DIM || y >= MATRIX_DIM) {
        led_matrix_clear(); // Coordenadas inválidas apagam a matriz
        return;
    }

    int target_index = y * MATRIX_DIM + x;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        if (i == target_index) {
            pio_sm_put_blocking(pio, sm, color);
        } else {
            pio_sm_put_blocking(pio, sm, 0);
        }
    }
    sleep_us(50); // Atraso para garantir escrita correta nos LEDs
}

/**
 * @brief Apaga todos os pixels da matriz de LED.
 */
void led_matrix_clear() {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        pio_sm_put_blocking(pio, sm, 0);
    }
    sleep_us(50); // Atraso após escrita
}
