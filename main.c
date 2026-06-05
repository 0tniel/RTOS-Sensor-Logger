#include <LPC21xx.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// External peripheral driver functions
extern void uart_init(void);
extern int uart_str(char *str);
extern void ADCInit(void);
extern unsigned int ADC_StartCov(void);

// Global RTOS handles
QueueHandle_t xQueue1, xQueue2;
SemaphoreHandle_t xMutex;

// --- TASK 1: SENSOR ACQUISITION ---
void Task1(void *pvParameters) {
 unsigned int adc_val;
 while(1) {
 adc_val = ADC_StartCov();
 xQueueSend(xQueue1, &adc_val, portMAX_DELAY);
 if(xSemaphoreTake(xMutex, portMAX_DELAY)) {
 uart_str("T1: Sensor Read\r\n");
 xSemaphoreGive(xMutex);
 }
 vTaskDelay(pdMS_TO_TICKS(500));
 }
}

// --- TASK 2: PROCESSING ---
void Task2(void *pvParameters) {
 unsigned int adc_val;
 float temp;
 char msg[30];
 while(1) {
 xQueueReceive(xQueue1, &adc_val, portMAX_DELAY);
 temp = (adc_val * 3.3 / 1023) * 100; // ADC to voltage * scale
 temp = temp / 10; // Compensate for LPC2129 gain of 10
 sprintf(msg, "Temp: %.2f C\r\n", temp);
 xQueueSend(xQueue2, msg, portMAX_DELAY);
 vTaskDelay(pdMS_TO_TICKS(500));
 }
}

// --- TASK 3: LOGGING ---
void Task3(void *pvParameters) {
 char msg[30];
 while(1) {
 xQueueReceive(xQueue2, msg, portMAX_DELAY);
 if(xSemaphoreTake(xMutex, portMAX_DELAY)) {
 uart_str("T3: ");
 uart_str(msg);
 xSemaphoreGive(xMutex);
 }
 }
}

// --- MAIN ---
int main(void) {
 uart_init();
 ADCInit();
 uart_str("System Started\r\n");
 xMutex = xSemaphoreCreateBinary();
 xSemaphoreGive(xMutex);
 xQueue1 = xQueueCreate(10, sizeof(unsigned int));
 xQueue2 = xQueueCreate(10, 30);
 xTaskCreate(Task1, "Sensor", 200, NULL, 3, NULL);
 xTaskCreate(Task2, "Process", 200, NULL, 2, NULL);
 xTaskCreate(Task3, "Log", 200, NULL, 1, NULL);
 vTaskStartScheduler();
 while(1);
}
