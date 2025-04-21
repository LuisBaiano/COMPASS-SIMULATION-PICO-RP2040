#include "main.h"   

// Flag para garantir que o beep de norte toque apenas uma vez por entrada
bool north_beep_played = false; 

// Definição do modo de exibição, com dois modos possíveis
typedef enum {
    DISPLAY_MODE_NORMAL = 0,  // Modo normal (quadrado movendo-se)
    DISPLAY_MODE_LARGE_DIRECTION = 1  // Modo com nome completo da direção
} DisplayMode;

volatile DisplayMode current_display_mode = DISPLAY_MODE_NORMAL; // Inicialmente em modo normal

// Definição das cores da matriz de LEDs
#define MATRIX_COLOR_purple  0x00101010
#define MATRIX_COLOR_RED    0x00100000
#define MATRIX_COLOR_GREEN  0x00001000
#define MATRIX_COLOR_BLUE   0x00001000

volatile uint32_t matrix_color = MATRIX_COLOR_RED;  // Inicializa a cor da matriz como vermelha

// Função auxiliar para obter a direção cardinal a partir das coordenadas do joystick
const char* get_direction_abrev(uint16_t x, uint16_t y) {
    int dx = (int)x - ADC_CENTER;  // Diferença em x: >0 Direita (Leste), <0 Esquerda 
    int dy = ADC_CENTER - (int)y;  // Diferença em y: >0 Cima (Norte), <0 Baixo 

    // Se ambos dx e dy estiverem dentro da zona morta, retorna "C" (Centro)
    if (abs(dx) < ADC_DEADZONE && abs(dy) < ADC_DEADZONE) return "C ";

    // Detecta direções
    bool north = dx > ADC_DEADZONE;    // Vertical PARA CIMA
    bool south = dx < -ADC_DEADZONE;   // Vertical PARA BAIXO
    bool west  = dy > ADC_DEADZONE;    // Horizontal PARA DIREITA 
    bool east  = dy < -ADC_DEADZONE;   // Horizontal PARA ESQUERDA 

    // Primeiramente, verifica as direções diagonais
    if (north && east){
        uart_log("Direção: Nordeste\n");
        return "NE";  // Nordeste
    } 
    if (north && west){
        uart_log("Direção: Noroeste\n");
        return "NO";  // Noroeste
    } 
    if (south && east){
        uart_log("Direção: Sudeste\n");
        return "SE";  // Sudeste
    } 
    if (south && west){
        uart_log("Direção: Sudoeste\n");
        return "SO";  // Sudoeste
    } 
    // Em seguida, verifica as direções primárias
    if (north) {
        uart_log("Direção: Norte!\n");
        return "N ";
    }
    if (south) {
        uart_log("Direção: Sul!\n");
        return "S ";
    }
    if (east) {
        uart_log("Direção: Leste!\n");
        return "L ";
    }
    if (west) {
        uart_log("Direção: Oeste!\n"); 
        return "O ";
    }

    //Usado para quando o joystick estiver centralizado (algo que não acontece com uma bussola verdadeira, que sempre aponta para algum lado)
    uart_log("Direção: Centro (joystick no centro)!");
    return "C ";
}
// Função auxiliar para mapear a sigla da direção para o nome completo
const char* direction_full_word(const char* abrev) {
    // Compara a sigla e retorna o nome completo
    if (strcmp(abrev, "N ") == 0) return "NORTE";
    if (strcmp(abrev, "S ") == 0) return "SUL";
    if (strcmp(abrev, "L ") == 0) return "LESTE";
    if (strcmp(abrev, "O ") == 0) return "OESTE";
    if (strcmp(abrev, "NE") == 0) return "NORDESTE";
    if (strcmp(abrev, "NO") == 0) return "NOROESTE";
    if (strcmp(abrev, "SE") == 0) return "SUDESTE";
    if (strcmp(abrev, "SO") == 0) return "SUDOESTE";
    if (strcmp(abrev, "C ") == 0) return "CENTRO";
}

int main() {
    // Inicializações de periféricos e sistemas
    stdio_init_all();
    sleep_ms(1000); 
    uart_logger_init();
    joystick_init();
    buttons_init();
    rgb_led_init();   
    led_matrix_init(); 
    buzzer_init();   
    display_init();   
    uart_log("Bussola iniciada!\n");

    // Exibe a mensagem de inicialização no display
    uart_log("Mostrando mensagem de inicializacao no display...\n");
    const char *welcome_lines[] = {
        "EMBARCATECH",
        "PROJETO BUSSOLA"};
    display_draw_centered_text_block(welcome_lines, 2, 4);
    
    // Mantém a mensagem visível por 2 segundos
    sleep_ms(2000); 

    // Limpa a tela do display
    display_clear();
    display_update();
    uart_log("Mensagem de inicializacao finalizada. Entrando no loop principal.\n");

    while (true) {
        display_draw_rect();
        // Lê os valores do joystick (eixos X e Y)
        uint16_t joy_x = read_adc(0);  // Leitura do canal ADC para o eixo X
        uint16_t joy_y = read_adc(1);  // Leitura do canal ADC para o eixo Y
        
        // Processa os botões A e B
        if (buttons_a_pressed()) {
            // Alterna o modo de exibição entre normal e direção grande
            current_display_mode = (current_display_mode == DISPLAY_MODE_NORMAL) ?
            DISPLAY_MODE_LARGE_DIRECTION : DISPLAY_MODE_NORMAL;
            uart_log("Botão A pressionado, modo de exibição atual: %d\n", current_display_mode);
        }
        
        if (buttons_b_pressed()) {
            // Alterna entre as cores da matriz de LEDs (vermelho, verde, azul)
            if (matrix_color == MATRIX_COLOR_RED) {
                matrix_color = MATRIX_COLOR_purple;
                uart_log("Botão B pressionado, matriz na cor roxa!\n");
            } else if (matrix_color == MATRIX_COLOR_purple) {
                matrix_color = MATRIX_COLOR_BLUE;
                uart_log("Botão B pressionado, matriz na cor azul!\n");
            } else {
                matrix_color = MATRIX_COLOR_RED;
                uart_log("Botão B pressionado, matriz na cor vermelha!\n");
            }
        }

        if (buttons_joystick_pressed()) {
            // Botão joystick toca o beep
            buzzer_joystick_beep(); // Toca o beep (Buzzer 1)
        }

        // Atualiza os LEDs RGB com base no joystick
        rgb_led_update_from_joystick(joy_x, joy_y);

        // Atualiza a matriz de LEDs com um único pixel
        uint8_t matrix_x = ((ADC_MAX_VALUE - joy_y) * MATRIX_DIM) / (ADC_MAX_VALUE + 1);
        uint8_t matrix_y = (joy_x * MATRIX_DIM) / (ADC_MAX_VALUE + 1);
        // Clamping para garantir que as coordenadas estejam dentro dos limites
        if (matrix_x >= MATRIX_DIM) matrix_x = MATRIX_DIM - 1;
        if (matrix_y >= MATRIX_DIM) matrix_y = MATRIX_DIM - 1;
        led_matrix_set_pixel(matrix_x, matrix_y, matrix_color);

        // Atualiza o display, desenhando bordas
        display_clear();
        display_draw_rect();

        const char* direction_abrev = get_direction_abrev(joy_x, joy_y);

        if (current_display_mode == DISPLAY_MODE_NORMAL) {
            // Mapeia os valores do joystick para posições no display
            int pos_x = ((4095 - joy_x)* (DISPLAY_HEIGHT - SQUARE_SIZE)) / 4095;
            int pos_y = (joy_y * (DISPLAY_WIDTH - SQUARE_SIZE)) / 4095;
            
            // Limita as posições para que o quadrado não ultrapasse os limites
            if (pos_x < 0) pos_x = 0;
            if (pos_x > DISPLAY_HEIGHT - SQUARE_SIZE) pos_x = DISPLAY_HEIGHT - SQUARE_SIZE;
            if (pos_y < 0) pos_y = 0;
            if (pos_y > DISPLAY_WIDTH - SQUARE_SIZE) pos_y = DISPLAY_WIDTH - SQUARE_SIZE;

            display_draw_square(pos_x, pos_y);

            // Desenha a sigla da direção no canto inferior direito
            int dir_abbr_len = strlen(direction_abrev);
            int dir_x_pos_small = DISPLAY_WIDTH - (dir_abbr_len * 8);
            if (dir_x_pos_small < 0) dir_x_pos_small = 0;
            int dir_y_pos_small = DISPLAY_HEIGHT - 8;
            display_draw_text(direction_abrev, dir_x_pos_small, dir_y_pos_small);

        } else {
            display_draw_rect();
            const char *dir_line[] = { direction_full_word(direction_abrev) };
            display_draw_centered_text_block(dir_line, 1, 0);
        }

        display_update();  // Atualiza o display
        sleep_ms(25);  // Pausa de 25 ms
    }

    return 0;
}
