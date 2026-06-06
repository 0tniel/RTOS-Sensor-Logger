# RTOS-Sensor-Logger

A FreeRTOS-based sensor acquisition and logging system developed for the LPC2129 microcontroller. This project demonstrates ADC-based temperature sensing using the LM35 sensor, multitasking with FreeRTOS, queue-based inter-task communication, semaphore synchronization, and UART-based real-time logging.

## Project Structure

```text
RTOS-Sensor-Logger/
├── main.c
├── adc.c
├── uart.c
├── FreeRTOSConfig.h
├── UART Temp Output.png
└── README.md
```

## Hardware Used

- LPC2129 Development Board
- LM35 Temperature Sensor

## Working Principle

The application is divided into three FreeRTOS tasks:

### 1. Sensor Acquisition Task
- Periodically reads analog temperature data from the LM35 sensor using the ADC.
- Sends raw ADC values to a queue for further processing.

### 2. Processing Task
- Receives ADC values from the acquisition queue.
- Converts ADC readings into temperature values in degrees Celsius (°C).
- Sends the processed temperature data to another queue.

### 3. Logging Task
- Receives processed temperature values.
- Logs temperature readings through UART.
- Uses a semaphore to ensure safe and synchronized UART access.

## Features

- FreeRTOS-based multitasking
- LM35 temperature sensing via ADC
- Queue-based inter-task communication
- Semaphore synchronization for UART resource protection
- Real-time temperature monitoring and logging
- Modular driver-based implementation

## Output

### UART Terminal Output

![UART Output](UART%20Temp%20Output.png)

## How to Run

1. Open the project in Keil uVision.
2. Add the required FreeRTOS source files and header files.
3. Build the project for the LPC2129 microcontroller.
4. Flash the generated HEX file to the LPC2129 board using Flash Magic.
5. Connect the board to a PC through a serial interface.
6. Open a serial terminal (Flash Magic Terminal / PuTTY / Tera Term).
7. Configure the terminal with the correct baud rate used in the project.
8. Observe the real-time temperature readings displayed through UART.
