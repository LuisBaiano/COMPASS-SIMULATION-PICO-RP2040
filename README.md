# Projeto Integrador BitDogLab - Bussola com Rosa dos Ventos

## Índice

1. [Objetivos](#objetivos)
2. [Descrição do Projeto](#descricao-do-projeto)
3. [Funcionalidades Implementadas](#funcionalidades-implementadas)
4. [Requisitos Técnicos Atendidos](#requisitos-tecnicos-atendidos)
5. [Como Executar](#como-executar)
6. [Estrutura do Código](#estrutura-do-codigo)
7. [Referências](#referencias)
8. [Demonstrativo em Vídeo](#demonstrativo-em-video)

## Objetivos

* Revisar e consolidar os conhecimentos sobre o microcontrolador RP2040 e a placa BitDogLab.
* Integrar múltiplos periféricos da placa: Joystick (ADC), Botões (GPIO/IRQ), LED RGB (PWM), Matriz de LEDs (PIO/WS2812), Buzzer (GPIO), Display SSD1306 (I2C) e UART.
* Aplicar conceitos de leitura analógica, controle digital, comunicação serial (I2C, UART), controle de tempo (PWM, PIO), interrupções e tratamento de debounce.
* Desenvolver um sistema embarcado funcional e interativo em um ambiente VS Code configurado para o RP2040.

## Descrição do Projeto

Este projeto implementa um "Dashboard Interativo" na placa BitDogLab utilizando o microcontrolador RP2040. O sistema lê continuamente a posição do joystick analógico e o estado de três botões físicos (A, B e o do próprio joystick).

A posição do joystick é usada para:

1. Controlar a posição de um quadrado 8x8 exibido no display OLED SSD1306.
2. Modular a cor e a intensidade do LED RGB integrado, utilizando PWM para uma transição suave.

Os botões físicos, com tratamento de debounce e gerenciamento por interrupções, controlam outras funcionalidades:

* **Botão A:** Liga/desliga um padrão visual na matriz de LEDs 5x5 (controlada via PIO).
* **Botão B:** Muda a cor do led da matriz de LEDs.
* **Botão do Joystick:** Aciona um beep curto no buzzer.

O display OLED (128x64) exibe o quadrado móvel e informações de status em tempo real, como os valores lidos do ADC do joystick e o estado da matriz de LEDs e do buzzer.

A comunicação UART é utilizada para enviar mensagens de log e depuração para um terminal serial no computador, facilitando o acompanhamento da execução e o diagnóstico de problemas.

## Funcionalidades Implementadas

✅ Leitura analógica dos eixos X e Y do joystick via ADC.
✅ Movimentação proporcional de um quadrado 8x8 no display SSD1306 (Comunicação I2C).
✅ Controle de cor e intensidade do LED RGB via PWM, baseado na posição do joystick.
✅ Leitura dos botões A, B e Joystick com tratamento de debounce via software.
✅ Uso de interrupções (IRQ) para detecção eficiente do acionamento dos botões.
✅ Acionamento de um padrão visual na Matriz de LEDs (5x5 WS2812) via Botão A (Controle PIO).
✅ Acionamento de beep no Buzzer via Botão do Joystick.
✅ Mudança de cor na Matriz através do Botão B.
✅ Exibição de informações de status (Valores ADC, Estados Matrix/Buzzer) no display SSD1306.
✅ Envio de mensagens de log e status via interface UART para depuração.
✅ Código estruturado em múltiplos módulos para melhor organização e clareza.

## Requisitos Técnicos Atendidos

1. **Leitura Analógica (ADC):** Utilizada para capturar os valores X e Y do potenciômetro do joystick.
2. **Leitura de Botões (GPIO/IRQ):** Implementada com tratamento de debounce e uso de interrupções para os botões A, B e Joystick.
3. **Saídas Visuais e Sonoras:** Utilização da Matriz de LEDs (PIO), LED RGB (PWM) e Buzzer (GPIO) como feedback.
4. **Display Gráfico (SSD1306/I2C):** Exibição do quadrado móvel obrigatório e de informações adicionais em tempo real via I2C.
5. **Comunicação Serial (UART):** Transmissão de dados e mensagens de depuração para um terminal serial.
6. **Interrupções:** Empregadas para o tratamento eficiente dos eventos dos botões.
7. **Estrutura do Projeto:** Organizado em múltiplos arquivos `.c` e `.h` no ambiente VS Code.
8. **Código Comentado:** O código fonte possui comentários para facilitar o entendimento.

## Como Executar

### Requisitos de Hardware

* Placa de desenvolvimento **BitDogLab** (com RP2040).
* Cabo Micro-USB para conexão e alimentação.

### Requisitos de Software

* **VS Code** com a extensão Pico-W-Go ou configuração manual do toolchain ARM e Pico SDK.
* **Pico SDK** instalado e configurado no ambiente de desenvolvimento.
* **Git** (opcional, para clonar o repositório).
* Um **Terminal Serial** (ex: Monitor Serial do VS Code, Putty, Minicom, Tera Term) para visualizar os logs da UART.

### Passos

1. **Clonar o Repositório:**
   ```bash
   git clone <URL_DO_SEU_REPOSITORIO>
   cd <NOME_DA_PASTA_DO_PROJETO>
   ```
2. **Configurar o Projeto:** Abra a pasta do projeto no VS Code. Certifique-se que o `CMakeLists.txt` está correto e que o SDK do Pico está acessível.
3. **Compilar (Build):** Utilize a função de build do VS Code (geralmente Ctrl+Shift+B ou o botão "Build" na barra de status do CMake Tools).
4. **Carregar o Firmware:**
   * Coloque a BitDogLab em modo BOOTSEL (pressione o botão BOOTSEL ao conectar o cabo USB).
   * Arraste o arquivo `.uf2` gerado (geralmente na pasta `build`) para o drive RPI-RP2 que aparece no seu computador.
   * A placa reiniciará automaticamente.
5. **Visualizar Logs:** Abra o terminal serial, conecte à porta COM correspondente à sua BitDogLab com a taxa de **115200 baud**. Você deverá ver as mensagens de inicialização e os logs de eventos.
6. **Testar:** Interaja com o joystick e os botões para verificar todas as funcionalidades descritas.

## Estrutura do Código

**📂 projeto_bitdoglab/**
├── src/
│ ├── hardware_config.h # Definições de pinos e constantes globais
│ ├── uart_logger.c # Implementação do logger UART
│ ├── uart_logger.h # Interface do logger UART
│ ├── joystick.c # Implementação da leitura do Joystick (ADC)
│ ├── joystick.h # Interface do Joystick
│ ├── rgb_led.c # Implementação do controle do LED RGB (PWM)
│ ├── rgb_led.h # Interface do LED RGB
│ ├── led_matrix.c # Implementação do controle da Matriz LED (PIO)
│ ├── led_matrix.h # Interface da Matriz LED
│ ├── buzzer.c # Implementação do controle do Buzzer
│ ├── buzzer.h # Interface do Buzzer
│ ├── buttons.c # Implementação dos botões e interrupções
│ ├── buttons.h # Interface dos botões
│ ├── display.c # Implementação do controle do Display SSD1306
│ ├── display.h # Interface do Display
│ ├── debouncer.c # Implementação do Debounce (Seu arquivo)
│ ├── debouncer.h # Interface do Debounce (Seu arquivo)
│ └── pio/
│ └── led_matrix.pio # Programa PIO para a matriz WS2812
├── lib/
│ └── ssd1306/ # Biblioteca do display SSD1306 (Seus arquivos)
│ ├── ssd1306.c
│ ├── ssd1306.h
│ └── font.h
├── CMakeLists.txt # Arquivo de configuração do CMake
├── pico_sdk_import.cmake # Importação do SDK (Padrão Pico)
└── main.c # Ponto de entrada e loop principal da aplicação

## Referências

* [Documentação do RP2040](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
* [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk)
* [Documentação Pico C/C++ SDK](https://raspberrypi.github.io/pico-sdk-doxygen/)
* [BitDogLab - Informações da Placa](https://www.bitdoglab.com/) (Link genérico, adicione link específico se disponível)

## Demonstrativo em Vídeo

**[📹 Assista a Demostração](https://drive.google.com/file/d/1ZBec6HQRQYw-virNI-GePUEuZMBT6z-b/view?usp=sharing)**
*(Substitua este link pelo link real do seu vídeo no YouTube ou Google Drive)*
