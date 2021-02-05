/*
================================================================================
Filename: debug_console.h
Description: Header file for the debug console class.
================================================================================
*/

#ifndef DEBUG_CONSOLE_H_
#define DEBUG_CONSOLE_H_

/* Program includes: */
#include <utils.h>
#include <font.h>
#include <simulation_constants.h>

/* Structure for a single debug console message */
struct Message 
{
    u8 msg_str[DEBUG_CONSOLE_MAX_MSG_LENGTH]; /* Single message string */
    u32 color; /* Color of the message font */ 
};
typedef struct Message Message_t;

/* Structure for debug console object */
struct Debug_Console 
{
    V2_u32_t BL;  /* Bottom-left corner position of the console */
    u32 width;  /* Width of the debug console */
    u32 height; /* Height will be determined from DCONSOLE_MESSAGES */ 
    u32 message_index;  /* Pointer to the current available message line in the console */
    Message_t messages[DEBUG_CONSOLE_MESSAGES];  /* Array with the debug console messages */
    u8 str_buffer[255];  /* Temporary buffer for the debug string */
};
typedef struct Debug_Console Debug_Console_t;

/* Declaration of the Debug_Console member fuctions: */

/* Constructor of the Debug_Console object */
Debug_Console_t* debug_console_constructor(void);

/* Destructor of the Debug_Console object */
void debug_console_destructor(Debug_Console_t *debug_console);

/* Initialization of the Debug_Console object */
void debug_console_init(Debug_Console_t *debug_console, u32 x, u32 y, u32 width);

/* Function to add a string to the debug console */
void debug_console_add_message(Debug_Console_t *debug_console, char *msg_str, u32 color);

/* Function to delete the all messages */
void debug_console_clear_messages(Debug_Console_t *debug_console);

/* Function to clear the console from the all messages */
void debug_console_clear_console(Debug_Console_t *debug_console, Render_Buffer_t *render_buffer);

/* Function to hide the console */
void debug_console_hide(Debug_Console_t *debug_console, Render_Buffer_t *render_buffer);

/* Function to render the debug console with all messages */
void debug_console_render(Debug_Console_t *debug_console, Font_t *font, 
    Render_Buffer_t *render_buffer);

#endif // DEBUG_CONSOLE_H_
