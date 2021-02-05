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
#define PADDING_WIDTH 10  /* Width of the padding between different pannels */

/* Font constants */
#define SYM_ROWS 6  /* Amount of symbol rows in font.png */
#define SYM_COLS 20  /* Amount of sumbol columns in font.png */

/* Constants for the Field_Panel object */
#define FIELD_PANEL_CAPTION_HEIGHT 30  /* Height of the panel caption */
#define FIELD_PANEL_BRD_WIDTH 1  /* Width of the field border */
#define FIELD_PANEL_BKG_COLOR 0xffffff  /* Background color of the field */
#define FIELD_PANEL_BRD_COLOR 0xb4b4b4  /* Color of the field boarders */
#define FIELD_PANEL_CAPTION_BKG_COLOR 0xa5ff7f  /* Color of the panel caption background */
#define FIELD_PANEL_MAX_CAPTION_LENGTH 255  /* Maximum length of the caption */

/* Constants for the Info_Panel object */
#define INFO_PANEL_HEIGHT 540  /* Height of the panel */
#define INFO_PANEL_CAPTION_HEIGHT 30  /* Height of the panel caption */
#define INFO_PANEL_BRD_WIDTH 1  /* Width of the panel borders */
#define INFO_PANEL_BKG_COLOR 0xffffff  /* Color of the panel background */
#define INFO_PANEL_BRD_COLOR 0xb4b4b4  /* Color of the panel boarders */
#define INFO_PANEL_CAPTION_BKG_COLOR 0xa5ff7f  /* Color of the panel caption background */

/* Constants for the Plot_Panel object */
#define PLOT_PANEL_CAPTION_HEIGHT 30  /* Height of the plot panel caption */
#define PLOT_PANEL_BRD_WIDTH 1  /* Width of the plot panel */
#define PLOT_PANEL_BKG_COLOR 0xffffff  /* Background color of the plot panel */
#define PLOT_PANEL_BRD_COLOR 0xb4b4b4  /* Color of the plot panel borders */
#define PLOT_PANEL_CAPTION_BKG_COLOR 0xa5ff7f  /* Color of the plot panel caption background */

/* Constants for the debug console */
#define DEBUG_CONSOLE_MESSAGES 10  /* Amount of the debug messages in debug console */
#define DEBUG_CONSOLE_MAX_MSG_LENGTH 255  /* Maximum message length */
#define DEBUG_CONSOLE_BKG_COLOR 0xffffff  /* Background color of the debug console */
#define DEBUG_CONSOLE_BRD_COLOR 0xb4b4b4  /* Console boarders color */
#define DEBUG_CONSOLE_MARGINS 10  /* Top, left, bottom and right margins */

#endif  /* SIMULATION_CONSTANTS_H_ */