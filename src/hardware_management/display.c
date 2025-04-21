#include "display.h"
#include "main.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "uart_logger.h"
#include "lib/ssd1306/ssd1306.h"
#include "lib/ssd1306/font.h"

#include <string.h>

// Instância estática do display
static ssd1306_t ssd;

/**
 * @brief Inicializa o display OLED via I2C.
 */
void display_init() {
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    ssd1306_init(&ssd, DISPLAY_WIDTH, DISPLAY_HEIGHT, false, DISPLAY_ADDR, I2C_PORT);
    ssd1306_config(&ssd);
    display_clear();
    display_update();
    uart_log("Display Inicializado!");
}

/**
 * @brief Limpa o conteúdo do display.
 */
void display_clear() {
    ssd1306_fill(&ssd, false);
}

/**
 * @brief Desenha um quadrado preenchido nas coordenadas especificadas.
 *
 * @param x_horiz Coordenada X.
 * @param y_vert  Coordenada Y.
 */
void display_draw_square(int x_horiz, int y_vert) {
    ssd1306_rect(&ssd, x_horiz, y_vert, SQUARE_SIZE, SQUARE_SIZE, true, true);
}

/**
 * @brief Desenha texto no display nas coordenadas fornecidas.
 *
 * @param text Texto a ser exibido.
 * @param x    Posição X.
 * @param y    Posição Y.
 */
void display_draw_text(const char *text, int x, int y) {
    if (x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) return;
    ssd1306_draw_string(&ssd, text, x, y);
}

/**
 * @brief Desenha um retângulo na borda da tela (sem preenchimento).
 */
void display_draw_rect() {
    ssd1306_rect(&ssd, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, true, false);
}

/**
 * @brief Desenha bloco de texto centralizado vertical e horizontalmente.
 *
 * @param lines        Array de strings (linhas).
 * @param num_lines    Quantidade de linhas.
 * @param line_spacing Espaçamento entre as linhas.
 */
void display_draw_centered_text_block(const char *lines[], int num_lines, int line_spacing) {
    int font_width = 8;
    int font_height = 8;

    display_clear();

    int total_text_height = (num_lines * font_height) + ((num_lines - 1) * line_spacing);
    int start_y = (DISPLAY_HEIGHT - total_text_height) / 2;

    for (int i = 0; i < num_lines; i++) {
        int len = strlen(lines[i]);
        int text_width = len * font_width;
        int x = (DISPLAY_WIDTH - text_width) / 2;
        int y = start_y + i * (font_height + line_spacing);

        if (x < 0) x = 0;
        if (y < 0) y = 0;

        display_draw_text(lines[i], x, y);
    }

    display_update();
}

/**
 * @brief Atualiza o display com o conteúdo do buffer.
 */
void display_update() {
    ssd1306_send_data(&ssd);
}
