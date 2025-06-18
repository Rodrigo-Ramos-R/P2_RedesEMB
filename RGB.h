/*
 * File
 * 	RGB.h
 *
 * Brief
 * 	Libreria para la manipulacion de los 3 LEDS RGB de la K66
 *
 * Authors
 *  Rodrigo Ramos Romero
 *
 * Date
 *  27/01/2025
 * todo
 *
 */

#ifndef RGB_H_
#define RGB_H_

/* TODO: insert other include files here. */
#include "stdint.h"

/* Tipo para elegir las 7 combinaciones del RGB */
typedef enum
{
    GREEN,
	BLUE,
	PURPLE,
	RED,
	YELLOW,
	CYAN,
	WHITE,
	NO_COLOR
} colors_t;

/*!
 	 \brief Apaga los 3 LEDs RGBs sin importar cual este prendido

 	 \param[in] void
 	 \return void
 */
void RGB_off(void);

/*!
 	 \brief Prende la combinacion del LED RGB seleccionada

 	 \param[in] colors_t -> con una de las 7 selecciones
 	 \return void
 */
uint16_t RGB_pick_on(colors_t color);

void LED_TOOGLE(void);


#endif /* RGB_H_ */
