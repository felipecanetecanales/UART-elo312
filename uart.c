/***************************************************
* Nombre del modulo: uart.c
*
* Modulo creado para la asignatura Elo312
* Laboratorio de Estructura de Computadores
* del departamento de Electrónica de la Universidad
* Técnica Federico Santa María. El uso o copia
* está permitido y se agracede mantener el nombre 
* de los creadores.
*
* Escrito inicialmente el 25/11/2013 Por Mauricio Solís
*
* Descripción del módulo:
* Modulo driver UART
* Contiene las funciones que permiten manejar el
* modulo UART.
***************************************************/

/*  Include section
*
***************************************************/
#include "msp430_version.h"// Depende del uC que Ud. esté ocupando.
#include "uart.h"

/*  Defines section
*
***************************************************/

/*  Local Function Prototype Section
*
***************************************************/

/*  Global Variables Section
*
***************************************************/


////////////////////////////////////////
//       RUTINAS IMPLEMENTADAS        //
//                                    //

/**************************************************
* Nombre    		: void uart_0_init_p1(void)
* returns			: void
* Creada por		: Mauricio Solís
* Fecha creación	: 25/11/2013
* Descripción		: Inicializa el modulo UART
* a una velocidad de app 9600 baudios
**************************************************/
void uart_0_init_p1()
{
	P3SEL |= 0x30;
	ME1 |= UTXE0 + URXE0;
	UCTL0 |= CHAR;
	UTCTL0 |= SSEL1;
	//UTCTL0 = 0x10;
	UBR00 = 0x03;
	UBR10 = 0x00;
	UMCTL0 = 0x4A;
	UCTL0 &= ~SWRST;
}

/**************************************************
* Nombre            : void uart_0_init_p2(void)
* returns           : void
* Creada por        : Mauricio Solís
* Fecha creación    : 25/11/2013
* Descripción       : Inicializa el modulo UART
* a una velocidad de 2400 baudios (con iterrupción
* de recepción).
**************************************************/
void uart_0_init_p2()
{
	P3SEL |= 0x30;
	ME1 |= UTXE0 + URXE0;
	UCTL0 |= CHAR;
	UTCTL0 |= SSEL0;
	UBR00 = 0x0D;
	UBR10 = 0x00;
	UMCTL0 = 0x6B;
	UCTL0 &= ~SWRST;
	IE1 |= URXIE0;
}

/**************************************************
* Nombre            : void uart_0_send(char arg1)
* returns           : void
* arg 1             : Caracter a ser enviado
* Creada por        : Mauricio Solís
* Fecha creación    : 25/11/2013
* Descripción       : Envia un caracter por la UART0.
**************************************************/
void uart_0_send(char c)
{
	while (!(IFG1 & UTXIFG0));
	TXBUF0 = c;
}
//                                    //
////////////////////////////////////////


////////////////////////////////////////
//     RUTINAS NO IMPLEMENTADAS       //
//                                    //

/**************************************************
* Nombre    		: __interrupt void uart_uart0_rx(void)
* returns			: void
* Creada por		: Michael Kusch
* Fecha creación	: 01/01/2004
* Descripción		: Vector de interrupciones
del RX del modulo UART.
**************************************************/
#pragma vector=UART0RX_VECTOR
__interrupt void uart_uart0_rx (void)
{
	// fill in
}

