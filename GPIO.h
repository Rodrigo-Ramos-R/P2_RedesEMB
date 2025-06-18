/*
 * File
 * 	GPIO.h
 *
 * Brief
 * 	Libreria para el uso e inicializacion de los puertos y relojes del GPIO
 *
 * Authors
 *  Rodrigo Ramos Romero
 * Date
 *  27/01/2025
 * todo
 *
 */

#ifndef GPIO_H_
#define GPIO_H_

/* TODO: insert other include files here. */
#include <stdint.h>
#include "MK66F18.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"

typedef struct
{
	uint8_t flag_port_a : 1;
	uint8_t flag_port_d : 1;
} gpio_interrupt_flags_t;

/*! Constantes para elegir un puerto en especifico en aplicaciones*/
typedef enum{GPIO_A, /*!< Definition to select GPIO A */
			 GPIO_B, /*!< Definition to select GPIO B */
			 GPIO_C, /*!< Definition to select GPIO C */
			 GPIO_D, /*!< Definition to select GPIO D */
			 GPIO_E /*!< Definition to select GPIO E */
			} gpio_name_t;


/*!
 * \brief Inicializacion de los relojes y puertos de General Purpose Input Output
 *
 * \param[in] void
 * \return void
 */
void GPIO_init(void);

/*!
 	 \brief	 This function allows us to use the A port Handler at will.

 	 What this function does is take the value of the callback that we want to be executed
 	 when port A is interrupted for use.
 	 \return void
 */
void PORTA_IRQHandler(void);

/*!
 	 \brief	 This function allows us to use the D port Handler at will.

 	 What this function does is take the value of the callback that we want to be executed
 	 when port D is interrupted for use.
 	 \return void
 */
void PORTD_IRQHandler(void);

/*!
 * \brief Funcion que se encarga de limpiar los puertos despues de que se utilizaron.
 *
 * \param[in] void
 * \return void
 */
void GPIO_clear_irq_status(gpio_name_t gpio);

/*!
 * \brief Funcion encargada de cambiar la bandera del estado del puerto si es que se llega
 * 		  a interrumpir.
 *
 * \param[in] void
 * \return void
 */
uint8_t GPIO_get_irq_status(gpio_name_t gpio);

void GPIO_callback_init(gpio_name_t gpio, void (*handler));



#endif /* GPIO_H_ */
