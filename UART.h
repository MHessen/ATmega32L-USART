/*
 * UART.h
 *
 * Author: Engr/M.Hussein
 */

#ifndef UART_H_
#define UART_H_

/*--------------------------- UART Registers -----------------------------------*/

enum UCSRA_Reg    { MPCM , U2X , PE , DOR , FE , UDRE , TXC , RXC };
enum UCSRB_Reg    { TXB8 , RXB8 , UCSZ2 , TXEN , RXEN , UDRIE , TXCIE , RXCIE };
enum UCSRC_Reg    { UCPOL , UCSZ0 , UCSZ1 , USBS , UPM0 , UPM1 , UMSEL , URSEL_C };
enum UBRR_H_L_Reg { RESERVED=14 , URSEL_HL };
/*______________________________________________________________________________*/

#define BoRa 9600								// Baud Rate
#define Freq 8000000							// Kit connected Crystal
#define MyBRR ((Freq/16/BoRa)-1)

/*______________________________________________________________________________*/
void UART_vidInit(void) ;
void UART_vidTransData (u16 Data);
u16 UART_u8RecData (void) ;
void UART_vidFlush (void);

#endif /* UART_H_ */
