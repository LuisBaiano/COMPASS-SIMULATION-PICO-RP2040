#ifndef DISPLAY_H
#define DISPLAY_H

#include "pico/stdlib.h"

// Inicializa o display (I2C e SSD1306).
void display_init();

// Preenche todo o buffer interno com 0 (apaga os pixeis do display).
void display_clear();

// Desenha um quadrado preenchido no buffer.
void display_draw_square(int x_horiz, int y_vert);

// Desenha uma string de texto (fonte 8x8 padrão) no buffer.
void display_draw_text(const char *text, int x, int y);

// Desenha os textos de forma centralizada
void display_draw_centered_text_block(const char *lines[], int num_lines, int line_spacing);

// Envia o conteúdo do buffer para o display físico.
void display_update();

// (Opcional) Desenha uma borda retangular sem preenchimento.
void display_draw_rect();

#endif