/*
 * buart_1.c
 *
 * Created: 18.10.2013 12:43:18
 *  Author: �������������
 */

#include "buart_1.h"

//****************************************************************************************
ISR(USART1_RX_vect)
{
	uint8_t byte;
	uint8_t wr = (uart_1_rxwr+1) & UART_BUFEND_1_;
	byte = UDR1;
	if(wr != uart_1_rxrd)
	{
		uart_1_rx[uart_1_rxwr] = byte;
		uart_1_rxwr = wr;
	};
};
//****************************************************************************************
ISR(USART1_UDRE_vect)
{
	uint8_t rd = uart_1_txrd;
	if(rd != uart_1_txwr)
	{
		UDR1 = uart_1_tx[rd];
		uart_1_txrd = (rd+1) & UART_BUFEND_1_;
		return;
	};
	UCSR1B &= ~(1<<UDRIE1);
};
//****************************************************************************************
uint8_t uart_1_rx_count()
{
	return (uart_1_rxwr-uart_1_rxrd) & UART_BUFEND_1_;
};
//****************************************************************************************
uint8_t uart_1_read()
{
	uint8_t rd = uart_1_rxrd;
	uint8_t byte;
	if(rd != uart_1_rxwr)
	{
		byte = uart_1_rx[rd];
		uart_1_rxrd = (rd+1) & UART_BUFEND_1_;
		return byte;
	};
	return 0;
};
//****************************************************************************************
void uart_1_write(uint8_t byte)
{
	uint8_t wr = (uart_1_txwr+1) & UART_BUFEND_1_;
	if(wr != uart_1_txrd)
	{
		uart_1_tx[uart_1_txwr] = byte;
		uart_1_txwr = wr;
		UCSR1B |= (1<<UDRIE1);
	};
};
//****************************************************************************************
void uart_1_init()
{
	UBRR1L = F_CPU/UART_BAUD_RATE_1_/16-1;
	UBRR1H = (F_CPU/UART_BAUD_RATE_1_/16-1)>>8;
	UCSR1B = (1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
	//UCSR1C = (1<<UPM0)|(1<<UPM1);
};
//****************************************************************************************
//****************************************************************************************
//****************************************************************************************