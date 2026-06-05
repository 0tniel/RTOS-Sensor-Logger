# RTOS-Sensor-Logger

A FreeRTOS-based sensor acquisition and logging system developed for the LPC2129 microcontroller. The project demonstrates ADC data acquisition, multitasking, queue-based inter-task communication, semaphore synchronization, and UART logging. :contentReference[oaicite:0]{index=0}

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

## Working Principle

The application consists of three FreeRTOS tasks:

1. **Sensor Acquisition Task**
   - Reads ADC data periodically.
   - Sends raw ADC values to a queue.

2. **Processing Task**
   - Receives ADC values from the queue.
   - Converts them into temperature values.
   - Sends the processed data to another queue.

3. **Logging Task**
   - Receives processed data.
   - Logs the information through UART.
   - Uses a semaphore to ensure safe UART access. :contentReference[oaicite:1]{index=1}

## Features

- FreeRTOS-based multitasking
- ADC data acquisition
- UART communication
- Queue-based inter-task communication
- Semaphore synchronization
- Real-time temperature logging

## Output

![UART Output](UART%20Temp%20Output.png)

## How to Run

1. Open the project in Keil uVision.
2. Add the FreeRTOS source files and headers.
3. Build the project for LPC2129.
4. Flash the program to the LPC2129 Development Board.
5. Open Flash Magic Terminal at the configured baud rate.
6. Observe the temperature readings logged through UART. :contentReference[oaicite:2]{index=2}
