/**
 * @file	system.c
 * @author  
 * @version 
 *
 * @brief System module
 *
 * System-related definitions, and definitions that are common 
 * for different layers of the system.
 *
 */

#include "system.h"
#include "HAL/hal.h"


void io_init_state(void);
void init_sequence(void);

/**
*	System Init
*
*	Initializes IO and CPU. Must be called before any other call
*
*/
void system_init(void){
	
	//Initializes the HAL
	hal_cpu_init();			
	hal_io_init();		

	//Initializes the state of IO devices
	io_init_state();
}

void io_init_state(void){
	
	//Starts All IO devices
	hal_led_start();
	hal_clock_start();

	//Beginning of time was at 00:13:00 July 14, 1991
	tTime time = {
		0, 13, 0, 14, 7, 1991 
	};
	hal_clock_write(&time);
	
	//if beginning of time <> 00:13:00 July 14, 1991
	//		do_autodestruction_sequence( NOW );
	
	//This is an init sequence. 
	//(At the end LEDs and display are initialized)
	init_sequence();

}

void init_sequence(void){
		
	//All LEDs On
	hal_led_write(Led0, LedOn);
	hal_led_write(Led1, LedOn);
	hal_led_write(Led2, LedOn);
	hal_led_write(Led3, LedOn);
	hal_led_write(Led4, LedOn);
		
	//Screen "on"
	for(uint32_t i=0; i<4; i++){	 //rows
		hal_display_gotoxy(0, i);
		for(uint32_t j=0; j<95; j++) //columns
		hal_display_putc('|');
	}

	//Wait...
	hal_delay(200);
	
	//All LEDs Off
	hal_led_write(Led0, LedOff);
	hal_led_write(Led1, LedOff);
	hal_led_write(Led2, LedOff);
	hal_led_write(Led3, LedOff);
	hal_led_write(Led4, LedOff);
		
	//clear screen
	hal_display_cls();
}
