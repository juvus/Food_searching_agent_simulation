/*
================================================================================
File with the different simulation global constants.                                  
================================================================================
*/

#ifndef SIMULATION_CONSTANTS_H_
#define SIMULATION_CONSTANTS_H_

/* Program includes: */
#include <utils.h>

/* Colors constant for simulation appearence */
#define BKG_COLOR 0xe0e0e0  /* Background color of the main window */

/* Define the simulation initial constants */
#define WINDOW_WIDTH 1024  /* Main window width */
#define WINDOW_HEIGHT 768  /* Main window height */

/* Font constants */
#define SYM_ROWS 6  /* Amount of symbol rows in font.png */
#define SYM_COLS 20  /* Amount of sumbol columns in font.png */

/* Constants for the debug console */
#define DCONSOLE_MESSAGES 10  /* Amount of the debug messages in debug console */
#define DCONSOLE_MAX_MSG_LENGTH 255  /* Maximum message length */
#define DCONSOLE_BKG_COLOR 0xffffff  /* Background color of the debug console */
#define DCONSOLE_BRD_COLOR 0xb4b4b4  /* Console boarders color */
#define DCONSOLE_MARGINS 10  /* Top, left, bottom and right margins */

#endif  /* SIMULATION_CONSTANTS_H_ */