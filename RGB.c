/*
 * File
 * 	RGB.c
 *
 * Brief
 * 	Ejecutable para la manipulacion de los 3 LEDS RGB de la K66
 *
 * Authors
 *  Rodrigo Ramos Romero
 *
 * Date
 *  27/01/2025
 * todo
 *
 */

/* TODO: insert other include files here. */
#include "RGB.h"
#include "GPIO.h"
#include "bits.h"
#include <stdint.h>
#include "fsl_gpio.h"

BooleanType HFlag = FALSE;

void RGB_off(void){
	GPIO_PortSet(GPIOC, 1 << 9); //Red
	GPIO_PortSet(GPIOA, 1 << 11); //Blue
	GPIO_PortSet(GPIOE, 1 << 6);//Green
}


uint16_t RGB_pick_on(colors_t color){
    // Apagamos los 3 LEDs para asegurar que prendemos el que queremos
	GPIO_PortSet(GPIOC, 1 << 9); //Red
	GPIO_PortSet(GPIOA, 1 << 11); //Blue
	GPIO_PortSet(GPIOE, 1 << 6);//Green

    switch (color)
    {
    	case GREEN: //Prender Verde
    		GPIO_PortClear(GPIOE, 1 << 6);
    	break;

        case BLUE:  //Prender Azul
        	GPIO_PortClear(GPIOA, 1 << 11);
        break;

        case PURPLE: //Prender Morado, Rojo + Azul
        	GPIO_PortClear(GPIOC, 1 << 9);
        	GPIO_PortClear(GPIOA, 1 << 11);
        break;

        case RED:    //Prender Rojo
        	GPIO_PortClear(GPIOC, 1 << 9);
        break;

        case YELLOW: //Prender Amarillo, Rojo + Verde
        	GPIO_PortClear(GPIOC, 1 << 9);
        	GPIO_PortClear(GPIOE, 1 << 6);
        break;

        case CYAN:  // Prender Cyan, Azul + Verde
        	GPIO_PortClear(GPIOA, 1 << 11);
        	GPIO_PortClear(GPIOE, 1 << 6);
        break;

        case WHITE: // Prender Blanco, Azul + Verde + Rojo
        	RGB_off();
        	GPIO_PortClear(GPIOC, 1 << 9);
        	GPIO_PortClear(GPIOA, 1 << 11);
        	GPIO_PortClear(GPIOE, 1 << 6);
        break;

        case NO_COLOR: // Apagamos los 3 si no queremos seleccionar nada
        	RGB_off();
        break;

        default:    // Si hay algun error en la seleccion, devuelve falso
            return (FALSE);
    }
    return (TRUE);  // Se asigno el color correctamente
}

void LED_TOOGLE(void){

	if(TRUE == HFlag){
		RGB_pick_on(GREEN);
		HFlag = FALSE;
	}else{
		RGB_off();
		HFlag = TRUE;
	}

}
