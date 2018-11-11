/**
 * @file	hal_cpu.c
 * @author  
 * @version 
 *
 * @brief CPU part of the Hardware Abstraction Layer 
 *
 */

#include <asf.h>
#include "hal.h"

//systick-related definitions
inline static uint32_t ms_to_ticks(uint32_t time_in_ms){ return (hal_cpu_speed_in_hz()/1000)*(time_in_ms); }

/**
*	HAL CPU Init
*
*	Initializes the CPU. This function must be called before 
*	HAL IO Init. That is: hal_cpu_init(); hal_io_init(); 
*
*/
void hal_cpu_init(void){	
	sysclk_init();  //initialize clocks
}

/**
*	HAL CPU Speed in Hz
*
*	Returns the CPU clock speed in Hz.
*	
*	@return CPU clock speed in Hz
*/
uint32_t hal_cpu_speed_in_hz(void){
	volatile int a = sysclk_get_cpu_hz(); 
	
	return a;
}

/**
*	Systick Start
*
*	Starts the System Timer
*
*	@param tick_freq_in_ms the tick frequency in milliseconds
*	@param callback function to be called when a tick occurs
*/
void hal_systimer_start(uint32_t tick_freq_in_ms, void(*callback)(void)){
	//registers callback 
	//...
	
	//start timer
	//...
}

//The actual handler
//(careful with the capital T in SysTick)
void SysTick_Handler(void){
	//Here the registered callback is "called". Another way of seeing this is that control goes
	//from the HAL "up" to the next layer.
	//(for an example see UART1 in hal_mem.c)
	//...
}

/**
*	Systick Stop
*
*	Stops the system timer
*
*/
void hal_systimer_stop(void){


   
}

/**
*	Systick reestart
*
*	Once started, this function can be used to re-estart the system timer 
*	with the same configuration.
*
*/
void hal_systimer_reestart(void){
	
}


/**
*	CPU Delays
*
*	Busy-waiting delay
*
*	@param delay_in_ms delay in milliseconds
*/
void hal_delay(uint32_t delay_in_ms){
	delay_ms(delay_in_ms);
}