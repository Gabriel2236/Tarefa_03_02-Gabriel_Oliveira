README
Visão Geral
Este projeto interfaceia com um microcontrolador Raspberry Pi Pico, utilizando vários periféricos como um display OLED, um LED RGB, botões de pressão e uma UART para comunicação serial. O código permite que os usuários interajam com o hardware por meio de botões de pressão e entrada serial, exibindo caracteres em uma tela OLED e manipulando os estados dos LEDs.

Requisitos de Hardware
Raspberry Pi Pico

Display OLED SSD1306

Matriz de LED WS2812B

Conexão UART para comunicação serial

I2C para comunicação com o display OLED

Botões de pressão (2x)

LEDs RGB (3x)

Configuração dos Pinos
I2C SDA: GPIO 14

I2C SCL: GPIO 15

Endereço do OLED: 0x3C

UART TX: GPIO 0

UART RX: GPIO 1

LED RGB Verde: GPIO 11

LED RGB Azul: GPIO 12

LED RGB Vermelho: GPIO 13

Botão de Pressão A: GPIO 5

Botão de Pressão B: GPIO 6

Pino de saída da matriz de LED: GPIO 7

Bibliotecas Necessárias
pico/stdlib.h

hardware/pio.h

hardware/clocks.h

hardware/adc.h

hardware/uart.h

hardware/i2c.h

pico/bootrom.h

ssd1306.h

font.h

Funcionalidade
Manipulador de Interrupção GPIO
A função gpio_irq_handler lida com interrupções dos botões de pressão, alternando os estados dos LEDs verde e azul e atualizando a tela OLED conforme necessário.

Configuração de Interrupção GPIO
A função setup_gpio_interrupt inicializa os pinos GPIO e configura manipuladores de interrupção para os botões de pressão.

Função de Matriz RGB
A função matrix_rgb calcula os valores RGB e retorna um valor de cor de 32 bits. A função desenho_pio envia dados de cor do LED para a máquina de estado PIO para exibir imagens na matriz de LEDs.

Loop Principal
O loop principal lê caracteres da UART e USB, exibe-os na tela OLED e atualiza a matriz de LED com base no caractere de entrada.

Uso
Conecte o Raspberry Pi Pico aos periféricos conforme a configuração dos pinos.

Carregue o código no Raspberry Pi Pico.

Use os botões de pressão para alternar os estados dos LEDs e atualizar a tela OLED.

Envie caracteres via UART ou USB para exibi-los na tela OLED e atualizar a matriz de LED.

Video mostrando o código funcionando na placa Bitdoglab: https://drive.google.com/file/d/1xaLt2XZRJdKyB2Ikh9QWqoLPG2QiKhgu/view?usp=sharing