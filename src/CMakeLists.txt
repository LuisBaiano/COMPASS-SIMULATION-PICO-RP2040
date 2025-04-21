# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
# (Copied from your template)
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0) # Make sure this matches your installed SDK version if needed
set(toolchainVersion 13_3_Rel1) # Make sure this matches your installed toolchain version if needed
set(picotoolVersion 2.1.0) # Make sure this matches your installed picotool version if needed
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

# Set the board type (use 'pico', 'pico_w', or your specific custom board if defined)
# Using 'pico' as a general RP2040 base if 'bitdoglab' isn't a defined board.
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(main C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable sources
add_executable(main
            main.c
            hardware_management/joystick.c
            hardware_management/uart_logger.c
            hardware_management/rgb_led.c
            hardware_management/led_matrix.c
            hardware_management/buzzer.c
            hardware_management/buttons.c
            hardware_management/display.c
            hardware_management/debouncer.c           
            lib/ssd1306/ssd1306.c)

# Set program name and version (using template style)
pico_set_program_name(main "main")
pico_set_program_version(main "0.1")

# Modify the below lines to enable/disable output over UART/USB
# Disable UART stdio if using UART0 for our custom logger
pico_enable_stdio_uart(main 0)
# Enable USB stdio for debugging via Serial Monitor
pico_enable_stdio_usb(main 1)

# Generate the PIO header from our .pio file
# Ensure the path to the .pio file is correct
pico_generate_pio_header(main ${CMAKE_CURRENT_LIST_DIR}/pio/led_matrix.pio)

# Add include directories
# Include the root, the hardware source/header directory, the debouncer dir, and the SSD1306 lib dir
target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}          
)

# Link required Pico SDK hardware libraries
# Make sure ALL necessary libraries are listed here
target_link_libraries(main PRIVATE
    pico_stdlib
    hardware_adc
    hardware_pwm
    hardware_i2c
    hardware_uart
    hardware_pio
    hardware_clocks
    hardware_irq
    hardware_gpio
)

# Add any user requested libraries (leave empty if none)
# target_link_libraries(main PRIVATE
#         )

# Create UF2 file, etc.
pico_add_extra_outputs(main)
