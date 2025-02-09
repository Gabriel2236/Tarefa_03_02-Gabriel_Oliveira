# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicializar pico_sdk
include(pico_sdk_import.cmake)

project(Tarefa_03_02 C CXX ASM)

# Inicializar Raspberry Pi Pico SDK
pico_sdk_init()

# Adicionar executável
add_executable(Tarefa_03_02 Tarefa_03_02.c inc/ssd1306.c)

pico_set_program_name(Tarefa_03_02 "Tarefa_03_02")
pico_set_program_version(Tarefa_03_02 "0.1")

# Habilitar saída padrão USB
pico_enable_stdio_uart(Tarefa_03_02 1)
pico_enable_stdio_usb(Tarefa_03_02 1)

# Gerar cabeçalho PIO
pico_generate_pio_header(Tarefa_03_02 ${CMAKE_CURRENT_LIST_DIR}/Tarefa_03_02.pio)

# Adicionar bibliotecas padrão
target_link_libraries(Tarefa_03_02
    hardware_uart
    hardware_pio
    hardware_adc
    hardware_i2c
    pico_stdlib
)

# Incluir diretórios padrão
target_include_directories(Tarefa_03_02 PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Adicionar saídas extras
pico_add_extra_outputs(Tarefa_03_02)
