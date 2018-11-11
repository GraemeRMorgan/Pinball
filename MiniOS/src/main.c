/************************************************************************/
/* CPSC 321 Pinball Project                                             */
/************************************************************************/

#include "MiniOS/system.h"
#include "MiniOS/hal/hal.h"

tTime time;

int main(void)
{
	system_init();
	
	time.seconds = 0;
	time.minutes = 30;
	time.hours = 20;
	time.day = 27;
	time.month = 11;
	time.year = 2017;

	hal_clock_write(&time);

	while(1){
		hal_clock_read(&time);
		
		if( time.seconds % 2 == 0 )
			hal_led_write( Led2, LedOn );
		else
			hal_led_write( Led2, LedOff );
	}
}