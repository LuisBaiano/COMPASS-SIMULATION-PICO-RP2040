#include "buzzer.h"
#include "main.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "uart_logger.h"
#include <stdbool.h>
#include <stdint.h>
#include "pico/stdlib.h"


#define BUZZER_PIN1 10  
#define BUZZER_PIN2 21  

// Melodia de sucesso
static const uint success_melody[]    = {523, 659, 784}; ///< Frequências C5, E5, G5
static const uint success_durations[] = {150, 150, 300}; ///< Durações correspondentes em ms
static const size_t success_len       = sizeof(success_melody) / sizeof(success_melody[0]);

// Beeps específicos
#define JOYSTICK_BEEP_FREQ 880  ///< Frequência do beep do joystick (A5)
#define JOYSTICK_BEEP_DUR   50  ///< Duração do beep do joystick (ms)
#define NORTH_BEEP_FREQ    1047 ///< Frequência do beep para o norte (C6)
#define NORTH_BEEP_DUR      100 ///< Duração do beep para o norte (ms)

/**
 * @brief Emite um tom em um pino GPIO utilizando PWM.
 *
 * Esta função configura o pino especificado para a função PWM,
 * ajusta a frequência desejada, gera o sinal por um tempo determinado
 * e em seguida desliga o PWM.
 *
 * @param pin Número do pino GPIO.
 * @param freq Frequência do tom em Hz. Use 0 para silêncio.
 * @param duration_ms Duração do tom em milissegundos.
 */
static void play_tone_on_pin(uint pin, uint freq, uint duration_ms) {
    if (freq == 0) {
        if (duration_ms > 0) sleep_ms(duration_ms);
        return;
    }

    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);

    uint32_t clock = clock_get_hz(clk_sys);
    uint32_t wrap_val = clock / freq;
    if (wrap_val < 2) wrap_val = 2;

    pwm_set_wrap(slice_num, wrap_val);
    pwm_set_chan_level(slice_num, channel, wrap_val / 2);
    pwm_set_enabled(slice_num, true);

    if (duration_ms > 0) {
        sleep_ms(duration_ms);
        pwm_set_enabled(slice_num, false);
    }
}

/**
 * @brief Toca uma sequência de tons em um pino especificado.
 *
 * Percorre os arrays de frequências e durações, tocando cada tom
 * por seu respectivo tempo, com pequenas pausas entre eles.
 *
 * @param pin Número do pino GPIO.
 * @param melody Array de frequências (Hz).
 * @param durations Array de durações (ms).
 * @param len Comprimento da sequência.
 */
static void play_sequence(uint pin, const uint *melody, const uint *durations, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        play_tone_on_pin(pin, melody[i], durations[i]);
        if (i < len - 1) sleep_ms(50); // Pausa entre notas
    }

    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_enabled(slice_num, false);
}

/**
 * @brief Inicializa os buzzers e toca a melodia de sucesso no buzzer principal.
 *
 * Configura os pinos dos buzzers como saídas e emite uma melodia indicando
 * que o sistema foi inicializado com sucesso.
 */
void buzzer_init() {
    gpio_init(BUZZER_PIN1);
    gpio_set_dir(BUZZER_PIN1, GPIO_OUT);
    gpio_put(BUZZER_PIN1, 0);

    gpio_init(BUZZER_PIN2);
    gpio_set_dir(BUZZER_PIN2, GPIO_OUT);
    gpio_put(BUZZER_PIN2, 0);

    uart_log("Buzzers inicializados!");
    buzzer_play_success();
}

/**
 * @brief Toca a melodia nos buzzers.
 */

void buzzer_play_success() {
    uart_log("Tocando melodia de sucesso (Buzzer 1)...\n");
    play_sequence(BUZZER_PIN1, success_melody, success_durations, success_len);
}

void buzzer_joystick_beep() {
    play_tone_on_pin(BUZZER_PIN2, JOYSTICK_BEEP_FREQ, JOYSTICK_BEEP_DUR);
}

