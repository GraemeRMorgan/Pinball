/**
 * @file	hal.h
 * @author  
 * @version 
 *
 * @brief Header file for the HAL (IO, CPU and MEM)
 *
 */


#ifndef HAL_H_
#define HAL_H_

#include <stdint-gcc.h>	//defs for size-specific primitive data types
#include <stdbool.h>	//defs for true and false

typedef uint32_t tLedNum;		/**< Led number type */
typedef bool tLedState;			/**< Led state type */
typedef uint32_t tButtonNum;	/**< Button number type */
typedef uint32_t tSensorId;		/**< Sensor ID type */
typedef uint32_t tSerialId;		/**< Serial ID type */
typedef uint32_t tMemoryId;		/**< Memory ID type */

enum tLedState	{ LedOff=false, LedOn };								/**< enumeration for LED states */
enum tLedNum	{ Led0 = 0, Led1, Led2, Led3, Led4 };					/**< enumeration for LEDs in the board */
enum tButtonNum	{ Button0 = 0, Button1, Button2, Button3, Button4 };	/**< enumeration for buttons in the board*/
enum tSensorId	{ SensorLight = 0, SensorTemp };						/**< enumeration for supported sensors */
enum tSerialId	{ SerialA = 0, SerialB };								/**< enumeration for supported serial interfaces */
enum tMemoryId	{ MemSDCard = 0, MemSDCardFAT = 1, MemFlash = 2 };		/**< enumeration for non-volatile memories */	
	
#define MEM_FAT_MAX_FNAME_LENGTH	30	/**< max file name size for the FAT file system */

/**
* A structure to represent time
*/
typedef struct{
	uint32_t seconds; /**< seconds */
	uint32_t minutes; /**< minutes */
	uint32_t hours;   /**< hours */
	uint32_t day;     /**< day */
	uint32_t month;   /**< month */
	uint32_t year;    /**< year */
}tTime;

//Init
void hal_io_init( void );
void hal_cpu_init();
void hal_mem_init(); 

//Millisecond Timer
void hal_mtimer_start( uint32_t );
void hal_mtimer_start_int( uint32_t, void(*)(void) );
void hal_mtimer_stop( void );
uint32_t hal_mtimer_read( void );

//Sensor
void hal_sensor_start( tSensorId );
void hal_sensor_start_int( tSensorId, void(*)(void) );
uint32_t hal_sensor_read( tSensorId );

//Display
void hal_display_start( void );
void hal_display_putc( uint8_t );
void hal_display_cls( void );
void hal_display_gotoxy( uint32_t, uint32_t );
uint32_t hal_display_numlines( void );

//LED
void hal_led_start( void );
void hal_led_write( tLedNum, tLedState );
tLedState hal_led_read( tLedNum );

//Clock
void hal_clock_start( void );
void hal_clock_write( tTime* );
void hal_clock_read( tTime* );

//Buttons
void hal_button_start_int( void(*)(tButtonNum) );

//Serial
void hal_serial_start( tSerialId, uint32_t );
void hal_serial_start_int( tSerialId, uint32_t, void(*)(uint32_t) );
void hal_serial_putc( tSerialId, uint8_t );
uint8_t hal_serial_getc( tSerialId );

//System Timer
void hal_systimer_start(uint32_t, void(*)(void));
void hal_systimer_stop(void);
void hal_systimer_reestart(void);

//CPU Speed
uint32_t hal_cpu_speed_in_hz(void);

//Delays
void hal_delay(uint32_t);

//Non-volatile Memory
bool hal_mem_start( tMemoryId );
double hal_mem_capacity( tMemoryId );
uint32_t hal_mem_fat_file_size( uint8_t* );
uint32_t hal_mem_fat_file_read( uint8_t*, uint8_t* , uint32_t );
bool hal_mem_fat_file_write( uint8_t*, uint8_t*, uint32_t );
uint32_t hal_mem_fat_file_list( uint8_t list[][MEM_FAT_MAX_FNAME_LENGTH+1], uint32_t );

#endif /* HAL_H_ */