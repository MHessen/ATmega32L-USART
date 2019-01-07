/*
 * UART.c
 *
 * Author: Engr/M.Hussein
 */

#include "Types.h"
#include "Registers.h"
#include "DIO.h"
#include "UART.h"
#define SetBit(Register,Pin) Register|=(1<<Pin)
#define ClrBit(Register,Pin) Register&=(~(1<<Pin))
#define get_bit(Register,Pin) ((Register >> Pin) & 1)


void UART_vidInit(void)
{
	/*
	DIO_vidSetBitDirction(2,0,0);					// PinD-0 RX Input
	DIO_vidSetBitDirction(2,1,1);					// PinD-1 TX Output

	SetBit(SREG,7);									// Global Interrupt
	SetBit(UCSRB,3);								// Peripheral Flag Interrupt
	SetBit(UCSRB,4);

	SetBit(UCSRC,1);
	SetBit(UCSRC,2);

	UBRRL = MyBRR ;
	UBRRH = 0 ;
	*/
	/*________________________________________________________*/
	/*--------------------------------------------------------*/
	/*________________________________________________________*/

	/*--------------------------------------------------------------*/
	/* GPIO Configuration */
	DIO_vidSetBitDirction(port_D,pin_0,INPUT);					/* PinD-0 RX Input */
	DIO_vidSetBitDirction(port_D,pin_1,OUTPUT);					/* PinD-1 TX Output*/
	/*______________________________________________________________*/
	/* Enable Transmit & Receive */
	UCSRB |= (1<<TXEN);								/* Transmit Enable */
	UCSRB |= (1<<RXEN) ;							/* Receive Enable  */
	/*______________________________________________________________*/
	/* Configuring Specs */
	/* UART_Mode */
	UCSRC &= ~(1<<UMSEL);							/* Asynchronous Mode */
	/* NO parity */
	UCSRC &= ~( (1<<UPM0)|(1<<UPM1) );
	/* One Stop Bit */
	UCSRC &= ~(1<<USBS);
	/* Character Size */
	UCSRC |= (1<<UCSZ0);
	UCSRC |= (1<<UCSZ1);
	UCSRB &= ~(1<<UCSZ2);
	/*______________________________________________________________*/
	/* Baud Rate Value */
	UBRRL = MyBRR ;
	UBRRH = 0x0 ;
	/*______________________________________________________________*/
}

void UART_vidTransData (u16 Data)
{
	/*
	while ( 0 == ( get_bit(UCSRA,5) ) ) ;
	UDR = Data ;
	 */

	/*Polling*/
	while ( 0 == ( (UCSRA)&(1<<UDRE) ) ) ;							/* Stuck here till the TXC_Flag = 1 */
	/*Data Transmission*/
	UDR = Data ;													/* Clear by Write 1 */
	/*Clearing Tx-Flag*/
	UCSRA |= (1<<TXC) ;
}

u16 UART_u8RecData (void)
{
	/*
	while ( 0 == ( get_bit(UCSRA,7) ) );
	return UDR ;
	*/
	/*Polling*/
	while ( 0 == ( (UCSRA)&(1<<RXC) ) ) ;
	/*Receiving Data*/
	return UDR ;
}

void UART_vidFlush (void)
{/* Flushing the Receiver Buffer FIFO */
	u16 dump;
	while ( UCSRA & (1<<RXC) ) /* while condition = 1 "True", dump any received data to Emptied the Receiver Buffer */
	{
		dump = UDR ;
	}
}
