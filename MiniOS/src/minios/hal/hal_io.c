/**
 * @file	hal_io.c
 * @author  
 * @version 
 *
 * @brief IO part of the Hardware Abstraction Layer 
 *
 */

#include <asf.h>
#include <stdint-gcc.h>	//defs for size-specific primitive data types
#include <stdbool.h>	//defs for true and false
#include "hal.h"

//Time definitions
static void rtc_setup(void);

//Serial definitions

//UART1 (8-bit, no parity, 1 stop bit)
#define UART_SERIAL_MODE    UART_MR_PAR_NO
#define PINS_UART1_PIO      PIOB		  //Rx and Tx pins are in Parallel IO B
#define PINS_UART1_ID       ID_UART1
#define PINS_UART1_TYPE     PIO_PERIPH_A  //UART1 is part of Peripheral A pg. 762 SAM4S Data sheet
#define PINS_UART1_ATTR     PIO_DEFAULT
#define PINS_UART1_MASK     (PIO_PB2A_URXD1| PIO_PB3A_UTXD1 )

static void configure_uart1(uint32_t baudrate);
static void uart1_putc( uint8_t );
static void uart1_getc( uint8_t* );
static void uart1_start( uint32_t );
static void uart1_start_int( uint32_t, void (*) (uint32_t) );
static void (*uart1_callback)(uint32_t);	//UART1 character received callback


/**
*	HAL IO Init
*
*	Initializes the board and IO pins. This function must be called before
*	any other call to an IO device. Example: hal_io_init(); hal_mtimer_start();...
*
*/
void hal_io_init(void){
	board_init();		//initialize board pins
	ioport_init();		//initialize GPIO
}

/**
*	Millisecond Timer Start (poll)
*
*	Starts the millisecond timer without interrupts
*
*   The ms timer counts in steps of 1 ms (with a max of 1000ms). So, for instance,
*	a ms_steps parameter of 2 will make the timer increment every 2 ms. The
*	maximum ms_step is 1000.
*
*	@param ms_steps steps needed to increment the timer by one
*/
void hal_mtimer_start( uint32_t ms_steps ){
	

}

/**
*	Millisecond Timer Start (interrupt)
*
*	Starts the millisecond timer with interrupts
*
*   The ms timer counts in steps of 1 ms (with a MAX of 1000ms). So, for instance,
*	a ms_steps parameter of 2 will make the timer increment every 2 ms. Every time 
*	the timer is incremented the registered callback is called.
*
*	@param ms_steps steps needed to increment the timer by one
*	@param callback the function that will be called on every increment 
*/
void hal_mtimer_start_int( uint32_t ms_steps, void (*callback) (void) ){
	
	
}


/**
*	MIllisecond Timer Stop
*
*	Stops the Timer
*/
void hal_mtimer_stop(void){
	
	
	
}

/**
*	Millisecond Timer Read
*
*	Returns the counter value in the millisecond timer
*
*	@return the count so far
*/
uint32_t hal_mtimer_read( void ){
	
	
	
}

/**
*	LED Start
*
*	Initializes and starts the on-board LEDs
*
*/
void hal_led_start(void){
	//No need to configure anything... 
	//If GPIO is configured so are LEDs
	
	//set LEDs pins directions
	#define DIR_INPUT 0
	#define DIR_OUTPUT 1
	ioport_set_pin_dir( IOPORT_CREATE_PIN(PIOC, 23), DIR_OUTPUT );
	ioport_set_pin_dir( IOPORT_CREATE_PIN(PIOC, 20), DIR_OUTPUT );
	ioport_set_pin_dir( IOPORT_CREATE_PIN(PIOA, 16), DIR_OUTPUT );
	ioport_set_pin_dir( IOPORT_CREATE_PIN(PIOC, 22), DIR_OUTPUT );
	ioport_set_pin_dir( IOPORT_CREATE_PIN(PIOC, 19), DIR_OUTPUT );
}

/**
*	LED Write
*
*	Write the state of an on-board LED
*
*	@param lednum the LED to be set
*	@param state on or off
*/
void hal_led_write( tLedNum  lednum, tLedState state ){
	uint32_t IOLine = 0;
	
	switch(lednum){
		case Led0: IOLine = IOPORT_CREATE_PIN(PIOC, 23); break;
		case Led1: IOLine = IOPORT_CREATE_PIN(PIOC, 20); break;
		case Led2: IOLine = IOPORT_CREATE_PIN(PIOA, 16); break;
		case Led3: IOLine = IOPORT_CREATE_PIN(PIOC, 22); break;
		case Led4: IOLine = IOPORT_CREATE_PIN(PIOC, 19); break;
		default: /* Error */ ;
	}
	
	//write pin
	ioport_set_pin_level( IOLine, !state );
}

/**
*	LED Read
*
*	Reads the state of the specified LED
*
*	@param	lednum the LED to be read
*
*	@return the state of lednum
*/
tLedState hal_led_read( tLedNum lednum ){
	
	
	
	
	
}

/**
*	Clock Start
*
*	Starts and initializes the system clock's time
*
*/
void hal_clock_start( void ){
	rtc_setup();
}

void rtc_setup(){
	pmc_switch_sclk_to_32kxtal(PMC_OSC_XTAL);
	while (!pmc_osc_is_ready_32kxtal());
	rtc_set_hour_mode(RTC, 0); //24-hrs mode by default
}


/**
*	Clock write
*
*	Write the system clock's time
*
*	@param t a pointer to a tTime structure specifying the time
*/
void hal_clock_write( tTime* t ){
	rtc_set_date( RTC, t->year, t->month, t->day, 0 );
	rtc_set_time( RTC, t->hours, t->minutes, t->seconds );
}

/**
*	Clock read
*
*	Reads the system's clock time
*
*	@param t a pointer to a tTime structure 
*/
void hal_clock_read( tTime* t ){
	uint32_t dummy_week = 0;
	
	rtc_get_time(RTC, &(t->hours), &(t->minutes), &(t->seconds));
	rtc_get_date(RTC, &(t->year), &(t->month), &(t->day), &dummy_week);
}

/**
*	Display Start
*
*	Initializes and starts the board's display
*/
void hal_display_start(void){
	
	
	
}

/**
*	Display putc
*
*	Writes a character to the display
*
*	@param character the character to be printed
*/
void hal_display_putc( uint8_t character ){
	
	
	
	
}

/**
*	Display CLS
*
*	Clears the Display (like the old MS-DOS cls)
*
*	@param string the formatted output
*/
void hal_display_cls(void){
	




}

/**
*	Display Gotoxy
*
*	Sets the cursor in a given coordinate. (Like Borland's gotoxy)
*
*	@param x x coordinate
*	@param y y coordinate
*/
void hal_display_gotoxy( uint32_t x, uint32_t y ){
	
	
	
	
}

/**
*	Display Number of Lines
*
*	Returns the number of lines that fit in the display, as per the driver's font size.
*
*	@return number of lines in display
*/
uint32_t hal_display_numlines( void ){
	
	
	
	
}

/**
*	Sensor Start
*
*	Initializes and starts a sensor
*
*	@param sensor the id of the sensor to be started
*/
void hal_sensor_start( tSensorId sensor_id ){
	
	
	
	
}

/**
*	Sensor Start (Interrupt)
*
*	This is an alternative for those sensors that trigger an interrupt 
*	to signal some event (e.g. In some IMU sensors an INT is raised when they wake up).
*
*	@param sensor the id of the sensor to be started
*	@param callback the function to be called on sensor interrupt
*/
void hal_sensor_start_int( tSensorId sensor_id, void(*callback)(void) ){
	//so far there is none
	//...
}

/**
*	Sensor Read
*
*	Reads the specified sensor. 
*	 - Temperature is returned in degrees Celsius
*	 - Light is returned as a percentage value (0 being the darkest)
*
*	@param sensor the sensor to be read
*
*	@return the sensor reading
*/
uint32_t hal_sensor_read( tSensorId sensor_id ){
	
	
	
	
}



/**
*	Buttons Start (Interrupt)
*
*	Starts buttons in the board. Every time a button is pressed, the registered callback
*	is called. 
*
*	@param callback Button pressed callback
*/
void hal_button_start_int( void (*callback) (tButtonNum) ){
	
	
	
	
	
}


/**
*	Serial Start (Poll)
*
*	Starts a specified serial interface. By default 8-bit, no parity, 1 stop bit.
*
*	@param serial_id Serial interface Id: SerialA, SerialB, ... 
*	@param baudrate baud rate
*/
void hal_serial_start( tSerialId serial_id, uint32_t baudrate ){
	switch( serial_id ){
		case SerialA:	configure_uart1(baudrate);	break;	//SerialA is UART1
		default:			/*Error*/;
	}
}

/**
*	Serial Start (with Interrupt)
*
*	Starts a specified serial interface (8-bit, no parity, 1 stop bit) 
*	and registers a callback that will be called when data is received
*
*	@param serial_id Serial interface Id: SerialA, SerialB, ... 
*	@param baudrate baud rate
*	@param callback the callback
*/
void hal_serial_start_int( tSerialId serial_id, uint32_t baudrate, void (*callback) (uint32_t) ){
	switch( serial_id ){
		case SerialA:	uart1_start_int(baudrate, callback);	break; //SerialA is UART1
		default:			/*Error*/;
	}
}

/**
*	Serial putc
*
*	Writes a character to the specified Serial interface. Returns
*	until writing has successfully completed.
*
*	@param serial_id Serial interface Id: SerialA, SerialB, ...
*	@param c the character to be sent
*/
void hal_serial_putc( tSerialId serial_id, uint8_t c ){
	switch( serial_id ){
		case SerialA:	uart1_putc(c);	break; //SerialA is UART1
		default:		/*Error*/;
	}
}

/**
*	Serial getc
*
*	Reads a character from the specified Serial Interface. This
*	function will not return until a character is available.
*
*	@return the read character
*/
uint8_t hal_serial_getc( tSerialId serial_id ){
	uint8_t buf = 0;
	
	switch( serial_id ){
		case SerialA:	uart1_getc(&buf);	break;
		default:		/*Error*/;
	}
	
	return buf;
}

void uart1_start_int( uint32_t baudrate, void (*callback) (uint32_t) ){
	configure_uart1(baudrate);	//Configures UART1
	uart1_callback = callback;	//registers callback
	
	//sets interrupt
	uart_enable_interrupt(UART1,UART_IER_RXRDY);
	NVIC_EnableIRQ(UART1_IRQn);
}


void configure_uart1(uint32_t baudrate){
	pio_configure(PINS_UART1_PIO, PINS_UART1_TYPE, PINS_UART1_MASK, PINS_UART1_ATTR);
	pmc_enable_periph_clk(ID_UART1);
	
	const sam_uart_opt_t uart1_sett = { sysclk_get_cpu_hz(), baudrate, UART_SERIAL_MODE };
	uart_init(UART1,&uart1_sett);
	uart_enable_tx(UART1);
	uart_enable_rx(UART1);
}


static void uart1_putc( uint8_t c ){
	while ( !(UART1->UART_SR & UART_SR_TXRDY) ); //wait for Tx to be available
	uart_write( UART1, c );						 //transmit
}


static void uart1_getc( uint8_t* buf ){
	while( !(uart_get_status(UART1) & UART_SR_RXRDY) ); //wait until a character is ready
	uart_read( UART1, buf );							//read
}


//UART1 ISR
void UART1_Handler(){
	uint8_t rx_data;
	uint32_t status = uart_get_status(UART1);
	
	if(status & UART_SR_RXRDY){
		//read data received (1 byte)
		uart_read(UART1, &rx_data);
		
		//pass to upper layer
		uart1_callback(rx_data);
	}
}
