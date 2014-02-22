#ifndef _serial_h
#define _serial_h

#define FOSC 16000000
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1

void UART_Init(unsigned int ubrr)
{

UBRR1H = 0x00;
UBRR1L = ubrr; /* Set baud rate*/
UCSR1B = (1<<RXEN1)|(1<<TXEN1); /* Enable Txn and Rxn*/
UCSR1C = (3<<UCSZ10); /* Set 8, N, 1*/

}

unsigned char UART_Recieve(void)
{

while ( !(UCSR1A & (1<<RXC)) );

return UDR1;

}

void UART_Transmit(unsigned char ch)
{

while ( !(UCSR1A & (1<<UDRE)) );

UDR1 = ch;

}

void print_string(unsigned char *str)
{
	while (*(str) != '\0')
	UART_Transmit((*str++));
}

#endif