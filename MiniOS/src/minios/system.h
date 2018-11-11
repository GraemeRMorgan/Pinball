/**
 * @file	system.h
 * @author  
 * @version 
 *
 * @brief System Module header file
 *	Note: system.h must be included before any other MiniOS header file as it
 *	has common includes required by other source code.
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

//
//   ---------   SYSTEM OPTIONS    ---------
// (Configure system by editing this values)
//
#define SYS_VERSION	3
#define SYS_CONF_SERIAL_A_BAUDRATE	115200

void system_init(void);

#endif /* SYSTEM_H_ */