#include <stdio.h>
#include <stdio.h>
#include "display.h"
#include "keyboard.h"
/***************************************************
* Nombre del modulo: keyboard.c
*
* Modulo creado para la asignatura Elo312
* Laboratorio de Estructura de Computadores
* del departamento de Electrónica de la Universidad
* Técnica Federico Santa María. El uso o copia
* está permitido y se agracede mantener el nombre 
* de los creadores.
*
* Escrito inicialmente el 01/01/2004 Por Michael Kusch & Wolfgang Freund
* Modificado el 24/09/2014           Por Mauricio Solís & Andrés Llico.
*
* Descripción del módulo:
* Modulo driver teclado matricial
* Contiene las funciones que permiten manejar el
* teclado matricial.
***************************************************/

/*  Include section
*
***************************************************/
#include "keyboard.h"

/*  Defines section
*
***************************************************/
typedef unsigned char uchar;

/*  Local Function Prototype Section
*
***************************************************/
void keyboard_button_action(char);


/*  Global Variables Section
*
***************************************************/
uchar BUTMAT_CLK = 0;           // cuántas interrupciones se lleva presionado el botón
uchar BUTMAT_PREV = 0xFF;       // tecla de la lectura anterior, FF => ninguna.


////////////////////////////////////////
//       RUTINAS IMPLEMENTADAS        //
//                                    //

/**************************************************
* Nombre    		: void keyboard_init(void)
* returns			: void
* Creada por		: Michael Kusch
* Fecha creación	: 01/01/2004
* Descripción		: Inicializa los puertos del 
* driver del teclado.
**************************************************/
void keyboard_init(void)
{
    PTOUT = 0x00;
    PTDIR = 0x00;
}

/**************************************************
* Nombre    		: void keyboard_tec_matrix(void)
* returns			: void
* Creada por		: Michael Kusch
* Fecha creación	: 01/01/2004
* Descripción		: Lee la matriz de botones y 
* llama a la función keyboard_button_action() cuando
* detecta que se ha presionado una tecla (o se ha mantenido
* presionada una tecla).
* Esta función debe ser llamada cada cierta cantidad de tiempo.
**************************************************/
void keyboard_tec_matrix(void)
{
    uchar BUTMAT = 0xFF;        // tecla de 0 a 15
    uchar k, i, temp;

    temp = 0x00;
    for(PTDIR = 0x10; PTDIR > 0; PTDIR <<= 1) {
        asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP");
        asm("NOP");
        k = (((~PTIN) & 0x0F) | PTDIR);
        if ( (k & 0x0F) )	           // si hay algún bit de columna en 0, entonces if es verdadero
            temp = k;	               // y se guarda el valor de la columna y filas activas
    }

    if (temp) {	                       // hubo tecla presionada?
        switch	(temp & 0xF0) {
        case BIT4:
            BUTMAT = 0;	 // fila 1
            break;
        case BIT5:
            BUTMAT = 4;	 // fila 2
            break;
        case BIT6:
            BUTMAT = 8;	 // fila 3
            break;
        case BIT7:
            BUTMAT = 12; // fila 4
            break;
        }

        switch	(temp & 0x0F) {
        case BIT0:
            asm("NOP");
            BUTMAT += 0; // col 1
            break;
        case BIT1:
            BUTMAT += 1; // col 2
            break;
        case BIT2:
            BUTMAT += 2; // col 3
            break;
        case BIT3:
            BUTMAT += 3; // col 4
            break;
        }

        if (BUTMAT != BUTMAT_PREV) {              // botón presionado es distinto al anterior?
            BUTMAT_PREV = BUTMAT;
            BUTMAT_CLK = 0;
            keyboard_button_action(BUTMAT);
        }
        else {
            if (++BUTMAT_CLK == 100) {            // presionada por más de 100*10[ms] (1 [s])?
                keyboard_button_action(BUTMAT);   // actuar como si se volvió a presionar el botón
                BUTMAT_CLK -= 33;                 // por cada 0.5 [s] que siga presionado el botón
            }
        }
    }
    else
        BUTMAT_PREV = 0xFF;                       // ningún botón presionado
}
//                                    //
////////////////////////////////////////


////////////////////////////////////////
//     RUTINAS NO IMPLEMENTADAS       //
//                                    //

/**************************************************
* Nombre    		: void keyboard_button_action(char arg1)
* returns			: void
* arg1				: Tecla presionada
* Creada por		: Michael Kusch
* Fecha creación	: 01/01/2004
* Descripción		: Realiza una accion segun la
tecla que ha sido presionada.
**************************************************/
void keyboard_button_action(char tecla)
{
  int p_anterior;
  //////EDITOR 1 ///////
  /*if ((int)tecla==3){ 
    switch (tecla){
      case 0:
        printf("A");
      case 1:
        printf("B");
      case 2:
        printf("C");
      case 4:
        printf("D");
      case 5: 
        printf("E");
      case 6:
        printf("F");
      case 8:
        printf("G");
      case 9:
        printf("H");
      case 10:
        printf("I");
    }
  }
  
  else if ((int)tecla==7){ 
    switch (tecla){
      case 0:
        printf("J");
      case 1:
        printf("K");
      case 2:
        printf("L");
      case 4:
        printf("M");
      case 5: 
        printf("N");
      case 6:
        printf("O");
      case 8:
        printf("P");
      case 9:
        printf("Q");
      case 10:
        printf("R");
    }
  }
  
  else if ((int)tecla==11){ 
    switch (tecla){
      case 0:
        printf("S");
      case 1:
        printf("T");
      case 2:
        printf("U");
      case 4:
        printf("V");
      case 5: 
        printf("W");
      case 6:
        printf("X");
      case 8:
        printf("Y");
      case 9:
        printf("Z");
    }     
  }

  else if ((int)tecla==11){ 
    switch (tecla){
      case 0:
        printf("1");
      case 1:
        printf("2");
      case 2:
        printf("3");
      case 4:
        printf("4");
      case 5: 
        printf("5");
      case 6:
        printf("6");
      case 8:
        printf("7");
      case 9:
        printf("8");
      case 10:
        printf("9");
      case 12:
        printf("\b");
      case 14:
        printf("\n");
  }
  }
   
  //////EDITOR 2 ///////
  if ((int)tecla == 0){printf("0");}
  if ((int)tecla == 1){printf("1");}
  if ((int)tecla == 2){printf("2");}
  if ((int)tecla == 3){printf("3");}
  if ((int)tecla == 4){printf("4");}
  if ((int)tecla == 5){printf("5");}
  if ((int)tecla == 6){printf("6");}
  if ((int)tecla == 7){printf("7");}
  if ((int)tecla == 8){printf("8");}
  if ((int)tecla == 9){printf("9");}
  if ((int)tecla == 10){printf("10");}
  if ((int)tecla == 11){printf("11");}
  if ((int)tecla == 12){printf("12");}
  if ((int)tecla == 13){printf("13");}
  if ((int)tecla == 14){printf("14");}
  if ((int)tecla == 15){printf("15");}
  
  */
   
  /////EDITOR 3 ///////
  if ((int)tecla == 0){
    p_anterior = 0;
    printf("0");
    }
  if ((int)tecla == 1){
    p_anterior = 1;
    printf("1");
  }
  if ((int)tecla == 2){
    p_anterior = 2;
    printf("2");
  }
  if ((int)tecla == 3){
    if (p_anterior == 3){
      p_anterior = 16;
      printf("A");
    }
    else {
      p_anterior = 3;
      printf("A");
    }
  }
  if ((int)tecla == 4){
    p_anterior = 4;
    printf("cuatro");
  }
  if ((int)tecla == 5){
    p_anterior = 5;
    printf("5");
  }
  if ((int)tecla == 6){
    p_anterior = 6;
    printf("6");
  }
  if ((int)tecla == 7){
    if (p_anterior == 7){
      p_anterior = 17;
      printf("B");
    }
    else {
      p_anterior = 17;
      printf("7");
    }
  }
  if ((int)tecla == 8){
    p_anterior = 8;
    printf("8");
    }
  if ((int)tecla == 9){
    p_anterior = 9;
    printf("9");
  }
  if ((int)tecla == 10){
    p_anterior = 10;
    printf("10");
  }
  if ((int)tecla == 11){
    if(p_anterior == 11){
      p_anterior = 18;
      printf("C");
    }
    else{
      p_anterior = 11;
      printf("11");
    }
  }
  if ((int)tecla == 12){
    p_anterior = 12;
    printf("12");
  }
  if ((int)tecla == 13){
    p_anterior = 13;
    printf("13");
  }
  if ((int)tecla == 14){
    p_anterior = 14;
    printf("14");
  }
  if ((int)tecla == 15){
    if(p_anterior == 15){
      p_anterior = 19;
      printf("D");
    }
    else {
      p_anterior = 15;
      printf("15");
    }
  }
}

