#include <stdio.h>
#include "pico/stdlib.h"


#include <math.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/i2c.h"


#include "Tarefa_03_02.pio.h"
#include "inc/ssd1306.h"
#include "inc/font.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
ssd1306_t ssd;

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1 

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

    if (current_time - last_time > 200000) {
        if (gpio == BOTTON_A ) {

            gpio_put(led_g, !gpio_get(led_g));
            if(gpio_get(led_g) == true){
            printf("LED verde ligado\n");
            ssd1306_fill(&ssd, false); // Limpa o display
            ssd1306_draw_string(&ssd, "LED G on", 10, 30); // Escreve no display (posição X=10, Y=30)
            ssd1306_send_data(&ssd);

            }
            else{
            printf("LED verde desligado\n");

            ssd1306_fill(&ssd, false); // Limpa o display
            ssd1306_draw_string(&ssd, "LED G off", 10, 30); // Escreve no display (posição X=10, Y=30)
            ssd1306_send_data(&ssd);

            }


        } else if (gpio == BOTTON_B) {

            gpio_put(led_b, !gpio_get(led_b));
            if(gpio_get(led_b) == true){
            printf("LED azul ligado\n");
            ssd1306_fill(&ssd, false); // Limpa o display
            ssd1306_draw_string(&ssd, "LED B on", 10, 30); // Escreve no display (posição X=10, Y=30)
            ssd1306_send_data(&ssd);

            }
            else{
            printf("LED azul desligado\n");

            ssd1306_fill(&ssd, false); // Limpa o display
            ssd1306_draw_string(&ssd, "LED B off", 10, 30); // Escreve no display (posição X=10, Y=30)
            ssd1306_send_data(&ssd);

            }
           
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

double numnull[25] = {
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0};



    
int main()
{
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    
    printf("Iniciando a comunicação serial...\n");
    fflush(stdout);

    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Define a função GPIO para I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Define a função GPIO para I2C
    gpio_pull_up(I2C_SDA); // Puxa a linha de dados
    gpio_pull_up(I2C_SCL); // Puxa a linha de relógio

     // Inicializa a estrutura do display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);


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

     // Buffer para armazenar a string digitada

     uart_puts(UART_ID, "Digite um caractere");
     uart_puts(UART_ID, "\r\n");

while (true) {
    char c;

    if(uart_is_readable(UART_ID)){
        int i =0;

        if(i>0){
            uart_puts(UART_ID, "Digite um caractere");
            uart_puts(UART_ID, "\r\n");
        }

        

        c = uart_getc(UART_ID);

        // Exibe o caractere no display OLED
        ssd1306_draw_char(&ssd, c, 20, 30);
        ssd1306_send_data(&ssd);

        // Envia a tecla pressionada de volta pela UART
        uart_puts(UART_ID, "Tecla pressionada: ");
        uart_putc(UART_ID, c);
        uart_puts(UART_ID, "\r\n");

        switch (c)
        {
        case '0':
           desenho_pio(num0, pio, sm, r, g, b); 
            break;

        case '1':
           desenho_pio(num1, pio, sm, r, g, b); 
            break;

        case '2':
           desenho_pio(num2, pio, sm, r, g, b); 
            break;
            
        case '3':
           desenho_pio(num3, pio, sm, r, g, b); 
            break; 

        case '4':
           desenho_pio(num4, pio, sm, r, g, b); 
            break;

        case '5':
           desenho_pio(num5, pio, sm, r, g, b); 
            break;
        case '6':
           desenho_pio(num6, pio, sm, r, g, b); 
            break;
            
        case '7':
           desenho_pio(num7, pio, sm, r, g, b); 
            break;

        case '8':
           desenho_pio(num8, pio, sm, r, g, b); 
            break;

        case '9':
           desenho_pio(num9, pio, sm, r, g, b); 
            break;   

        default:
        desenho_pio(numnull, pio, sm, r, g, b);
            break;
        }
        
        
    }

    if(stdio_usb_connected()){
    printf("Digite um caractere: \n");
    
    char c;

    if (scanf("%c", &c) == 1){

    printf("Tecla pressionada %c \n", c);
    

    ssd1306_fill(&ssd, false); // Limpa o display
    ssd1306_draw_char(&ssd, c, 10, 30); // Escreve no display (posição X=10, Y=30)
    ssd1306_send_data(&ssd); // Atualiza o display

    switch (c)
        {
        case '0':
           desenho_pio(num0, pio, sm, r, g, b); 
            break;

        case '1':
           desenho_pio(num1, pio, sm, r, g, b); 
            break;

        case '2':
           desenho_pio(num2, pio, sm, r, g, b); 
            break;
            
        case '3':
           desenho_pio(num3, pio, sm, r, g, b); 
            break; 

        case '4':
           desenho_pio(num4, pio, sm, r, g, b); 
            break;

        case '5':
           desenho_pio(num5, pio, sm, r, g, b); 
            break;
        case '6':
           desenho_pio(num6, pio, sm, r, g, b); 
            break;
            
        case '7':
           desenho_pio(num7, pio, sm, r, g, b); 
            break;

        case '8':
           desenho_pio(num8, pio, sm, r, g, b); 
            break;

        case '9':
           desenho_pio(num9, pio, sm, r, g, b); 
            break;   

        default:
        desenho_pio(numnull, pio, sm, r, g, b);
            break;
        }

    }

    }
    sleep_ms(200);
}
}