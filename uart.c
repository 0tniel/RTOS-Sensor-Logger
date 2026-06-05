#include "lpc21xx.h"
#include "stdio.h"

void uart_init(void);
char uart_rcv(void);
int uart_snd(unsigned char ch) ;
int uart_str(char *str) ;                            


void uart_init(void)	  //setting the baud rate for 115200 baud
{
	PINSEL0 = 0x05;	   // Set UART0 Txd and UART0 Rxd
	
	//set the baud rate
	U0LCR = 0x83;	// Line control register :DLAB=1 ; 8 bits ; 1 stop bit ; no parity
	U0DLM = 00;
	U0DLL = 0x61;
	U0LCR = 0x03;	// Line control register :DLAB=0 ; 8 bits ; 1 stop bit ; no parity
	//	U0TER = 0x80;   // Enable Transmission
	//uart_snd('A');
}

char uart_rcv(void)
{
	while(!(U0LSR & 0x1));
	return(U0RBR);
}

int uart_snd(unsigned char Ch)
{
  	while(!(U0LSR & 0x20));
	return( U0THR = Ch);
}

int uart_str(char *str)
{
  	while(*str){
              uart_snd(*str);
              str++;
	}
	return 1;
}

// with the following code, you may also use printf for printing on the terminal
struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;

int fputc(int ch, FILE *f) 
{
  	return (uart_snd(ch));
}
