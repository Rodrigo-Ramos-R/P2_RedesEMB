/*
 * File
 * 	GPIO.c
 *
 * Brief
 * 	Ejecutable para el uso e inicializacion de los puertos y relojes del GPIO
 *
 * Authors
 *  Rodrigo Ramos Romero
 * Date
 *  27/01/2025
 * todo
 *
 */

/* TODO: insert other include files here. */
#include "GPIO.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include <stdbool.h>

volatile static gpio_interrupt_flags_t g_intr_status_flag = {0};

static void (*gpio_D_callback)(void) = 0;
static void (*gpio_A_callback)(void) = 0;

void GPIO_init(void){

	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

	gpio_pin_config_t gpio_input_config = {
			        kGPIO_DigitalInput,
			        0,
			    };

	gpio_pin_config_t gpio_output_config = {
			        kGPIO_DigitalOutput,
			        1,
			    };

	const port_pin_config_t button_config = {
			kPORT_PullUp,                 /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,           /* Fast slew rate is configured */
			kPORT_PassiveFilterEnable,    /* Passive filter is disabled */
			kPORT_OpenDrainDisable,       /* Open drain is disabled */
			kPORT_HighDriveStrength,      /* High drive strength is configured */
			kPORT_MuxAsGpio,              /* Pin is configured as PTA4 */
			kPORT_UnlockRegister          /* Pin Control Register fields [15:0] are not locked */
		  };


	/*Switch 3*/
	PORT_SetPinConfig(PORTA, 10u, &button_config);
	PORT_SetPinInterruptConfig(PORTA, 10u, kPORT_InterruptFallingEdge);
	GPIO_PinInit(GPIOA, 10u, &gpio_input_config);

	/*Switch 2*/
	PORT_SetPinConfig(PORTD, 11u, &button_config);
	PORT_SetPinInterruptConfig(PORTD, 11u, kPORT_InterruptFallingEdge);
	GPIO_PinInit(GPIOD, 11u, &gpio_input_config);

	/*LED Azul*/
	PORT_SetPinMux(PORTA, 11u, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOA, 11u, &gpio_output_config);

	/*LED Rojo*/
	PORT_SetPinMux(PORTC, 9u, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOC, 9u, &gpio_output_config);

	/*LED Verde*/
	PORT_SetPinMux(PORTE, 6u, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOE, 6u, &gpio_output_config);

	/* PORTB16 (pin 62) is configured as UART0_RX */
	PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt3);

	/* PORTB17 (pin 63) is configured as UART0_TX */
	PORT_SetPinMux(PORTB, 17U, kPORT_MuxAlt3);

	PORT_SetPinMux(PORTE, 24U, kPORT_PinDisabledOrAnalog);

}

void PORTA_IRQHandler(void)
{
	if(gpio_A_callback)
	{
		gpio_A_callback();
	}

	GPIO_PortClearInterruptFlags(GPIOA, 0xFFFFFFFF);
}

void PORTD_IRQHandler(void)
{
	if(gpio_D_callback)
	{
		gpio_D_callback();
	}

	GPIO_PortClearInterruptFlags(GPIOD, 0xFFFFFFFF);
}

void GPIO_callback_init(gpio_name_t gpio, void (*handler))
{
	if(GPIO_A == gpio)
	{
		gpio_A_callback = handler;
	}
	else
	{
		gpio_D_callback = handler;
	}

}


void GPIO_clear_irq_status(gpio_name_t gpio)
{
	switch(gpio){
		case GPIO_A:
			g_intr_status_flag.flag_port_a = false;
			break;
		case GPIO_D:
			g_intr_status_flag.flag_port_d = false;
			break;
		default:
			g_intr_status_flag.flag_port_a = false;
		break;
		}
}

uint8_t GPIO_get_irq_status(gpio_name_t gpio)
{
	uint8_t status = 0;

	switch(gpio){
	case GPIO_A:
		status = g_intr_status_flag.flag_port_a;
		break;
	case GPIO_D:
		status = g_intr_status_flag.flag_port_d;
		break;
	default:
	status = g_intr_status_flag.flag_port_a;
	break;
	}

	return(status);
}

