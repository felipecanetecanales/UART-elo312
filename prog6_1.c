#include "msp430_version.h"            // Depende del uC que Ud. esté ocupando.
#include <stdio.h>
#include "uart.h"
#include "display.h"
#include "keyboard.h"
#include "tic.h"
#include "osc.h"


char mensaje[10] = "Hola Mundo";
int i = 0,j = 0;

void main(void) {  
	osc_init_xt2();
	WDTCTL = WDTPW + WDTHOLD;
	P5SEL |= 0x70;                     // Se dispone de los 3 relojes del sistema
	P5DIR |= 0x70;                   // en los bits 4, 5 y 6 de la puerta 5  
        display_init(); 
        display_clear();
        display_set_pos(0x00);
        tic_init();
        keyboard_init();

	uart_0_init_p2();
	_EINT(); 
        
	while(1) {
		uart_0_send(mensaje[i++]);
		while (j < 1000) j++;
		j = 0;
		if (i >= 10)
		i = 0;
    }
       
}
