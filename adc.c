#include "lpc21xx.h"

void ADCInit(void)
{
	PINSEL1 = 0x05000000;
}

unsigned int ADC_StartCov()
{
	static unsigned int adc_data;
	ADCR = (1<<21) | (3<<8) | (1<<1) | 1<<24;				   		
	while(!((adc_data=ADDR) & 0x80000000));		//Check DONE bit
	adc_data = (adc_data & 0x0000FFC0)>>6;		//Assign ADC result to ad1_data n display in mV		 
	return adc_data;
}
