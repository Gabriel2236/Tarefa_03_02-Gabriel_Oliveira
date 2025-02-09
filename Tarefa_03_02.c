#include <stdio.h>
#include "pico/stdlib.h"

// BIBLIOTECAS PARA A MATRIZ LED
#include <math.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

#include "Tarefa_03_02.pio.h"

// Definições da matriz de LEDs
#define NUM_PIXELS 25
#define OUT_PIN 7

//Definição de LED RGB
#define led_g 11
#define led_b 12
#define led_r 13

// Define os push bottons
#define BOTTON_A 5
#define BOTTON_B 6

uint32_t last_time = 0;

void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (current_time - last_time > 300000) {
        if (gpio == BOTTON_A ) {
            
            gpio_put(led_g, !gpio_get(led_g));

        } else if (gpio == BOTTON_B) {

            gpio_put(led_b, !gpio_get(led_b));
           
        }

        last_time = current_time;
    }
}

void setup_gpio_interrupt(uint gpio_pin, gpio_irq_callback_t callback) {
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_IN);
    gpio_pull_up(gpio_pin);
    gpio_set_irq_enabled_with_callback(gpio_pin, GPIO_IRQ_EDGE_FALL, true, callback);
}

uint32_t matrix_rgb(double r, double g, double b, double brightness)
{
    unsigned char R, G, B;
    R = (r * 255) * brightness;
    G = (g * 255) * brightness;
    B = (b * 255) * brightness;
    
    // Certifica-se de que os valores de R, G e B não excedam 255
    R = R > 255 ? 255 : R;
    G = G > 255 ? 255 : G;
    B = B > 255 ? 255 : B;

    return (G << 24) | (R << 16) | (B << 8); // Formato de cor ARGB (com G no MSB)
}

void desenho_pio(double *desenho, PIO pio, uint sm, double r, double g, double b)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho[i] != 0.0) // Verifica se o valor no vetor é diferente de zero
        {
            uint32_t valor_led = matrix_rgb(r, g, b, 0.3);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
        else
        {
            uint32_t valor_led = matrix_rgb(0.0, 0.0, 0.0, 0.0); // Apaga o LED
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}

// Vetores de imagens para a matriz de LEDs
double num0[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

double num1[25] = {
    0.0, 0.0, 0.1, 0.0, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0,
    0.0, 0.1, 0.1, 0.0, 0.0,
    0.0, 0.0, 0.1, 0.0, 0.0};

double num2[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.0, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};


double num3[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

double num4[25] = {
    0.0, 0.1, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0};

double num5[25] = {
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.0, 0.0, 0.2, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0,
    0.0, 0.2, 0.0, 0.0, 0.0,
    0.0, 0.2, 0.2, 0.2, 0.0};

double num6[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.0, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

double num7[25] = {
    0.0, 0.1, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

double num8[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

double num9[25] = {
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0,
    0.0, 0.1, 0.0, 0.1, 0.0,
    0.0, 0.1, 0.1, 0.1, 0.0};

int main()
{
    stdio_init_all();

    gpio_init(led_b);
    gpio_set_dir(led_b, OUT_PIN);
    gpio_put(led_b, 0);

    gpio_init(led_g);
    gpio_set_dir(led_g, OUT_PIN);
    gpio_put(led_g, 0);

    setup_gpio_interrupt(BOTTON_A, gpio_irq_handler);
    setup_gpio_interrupt(BOTTON_B, gpio_irq_handler);

    PIO pio = pio0;
    bool ok;
    uint32_t valor_led;
    double r = 0.5, g = 0.0, b = 0.7; // Escolha a cor desejada (neste exemplo, roxo)

    // Configura o clock para 128 MHz
    ok = set_sys_clock_khz(128000, false);
    printf("Iniciando a transmissão PIO\n");

    // Configurações do PIO
    uint offset = pio_add_program(pio, &Tarefa_03_02_program);
    uint sm = pio_claim_unused_sm(pio, true);
    Tarefa_03_02_program_init(pio, sm, offset, OUT_PIN);

    gpio_set_irq_enabled_with_callback(BOTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);


    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
