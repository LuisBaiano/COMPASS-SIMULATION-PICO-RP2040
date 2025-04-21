#ifndef BUZZER_H
#define BUZZER_H

// Inicializa ambos os buzzers e toca som de sucesso no buzzer 1.
void buzzer_init();

// Toca a melodia de sucesso no buzzer 1.
void buzzer_play_success();

// Emite um beep curto no buzzer 1 (para o botão do joystick).
void buzzer_joystick_beep();


#endif 