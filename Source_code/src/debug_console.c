/*
================================================================================
Filename: debug_console.c
Description: Definition of the DConsole class member functions.
================================================================================
*/

/* Standard includes: */
#include <string.h>
#include <assert.h>
#include <stdlib.h>

/* Program includes: */
#include <debug_console.h>
#include <utils.h>
#include <software_rendering.h>
#include <font.h>
#include <simulation_constants.h>

/* Definition of the Debug_Console member fuctions: */

Debug_Console_t* 
debug_console_constructor(void)
{
    /* Constructor of the Debug_Console object */
    Debug_Console_t *debug_console = (Debug_Console_t*) calloc (1,  sizeof(Debug_Console_t)); 
    if (debug_console == NULL)
    {
        assert(0 && "ERROR: Error in memory allocation for the Debug_Console object");
    }
    return debug_console;
}

void 
debug_console_destructor(Debug_Console_t *debug_console)
{
    /* Destructor of the Debug_Console object */
    if (debug_console)
    {
        free(debug_console);
        return;
    }
    assert(0 && "ERROR: Memory for the Debug_Console object was not previously allocated");
}

void
debug_console_init(Debug_Console_t *debug_console, u32 x, u32 y, u32 width)
{
    /* Initialization of the Debug_Console object */
    debug_console->BL.x = x;
    debug_console->BL.y = y;
    debug_console->width = width;
    debug_console->height = DEBUG_CONSOLE_MARGINS * 2 + DEBUG_CONSOLE_MESSAGES * 7 + \
        (DEBUG_CONSOLE_MESSAGES - 1) * 7; /* last digit - lines intend in pixels */
    debug_console->message_index = 0; 
}

void
debug_console_add_message(Debug_Console_t *debug_console, char *msg_str, u32 color)
{
    /* Function to add a string to the debug console */

    /* Length of the msg_str should be less than 255 symbols */
    assert(strlen(msg_str) < DEBUG_CONSOLE_MAX_MSG_LENGTH);

    u32 index = debug_console->message_index;
    debug_console->messages[index].color = color;
    strcpy_s(debug_console->messages[index].msg_str, DEBUG_CONSOLE_MAX_MSG_LENGTH, msg_str);
    debug_console->message_index++;
    
    /* For safe in case of adding more messages than possible to store */
    if (debug_console->message_index >= DEBUG_CONSOLE_MESSAGES) {
        debug_console->message_index = 0;
    }
}

void
debug_console_clear_messages(Debug_Console_t *debug_console)
{
    /* Function to delete the all messages in the console */
    u32 i;

    for (i = 0; i < DEBUG_CONSOLE_MESSAGES; ++i) {
        debug_console->messages[i].msg_str[0] = '\0';
    }
    debug_console->message_index = 0;
}

void
debug_console_clear_console(Debug_Console_t *debug_console, Render_Buffer_t *render_buffer)
{
    /* Function to clear the console from the all messages */      
    draw_rect_with_brd(debug_console->BL.x, debug_console->BL.y, debug_console->width,
        debug_console->height, 1, DEBUG_CONSOLE_BKG_COLOR, DEBUG_CONSOLE_BRD_COLOR, render_buffer);   
}

void
debug_console_hide(Debug_Console_t *debug_console, Render_Buffer_t *render_buffer)
{
    /* Function to hide the console */
    draw_rect(debug_console->BL.x , debug_console->BL.y, debug_console->width, debug_console->height,
        BKG_COLOR, render_buffer);
}

void
debug_console_render(Debug_Console_t *debug_console, Font_t *font, Render_Buffer_t *render_buffer)
{
    /* Function to render the console with all messages */
    u32 x_pos;
    u32 y_pos;
    u32 i;
    u32 max_width;
    
    x_pos = debug_console->BL.x + DEBUG_CONSOLE_MARGINS; 
    y_pos = debug_console->BL.y + debug_console->height - DEBUG_CONSOLE_MARGINS - 7;  
    max_width = debug_console->width - DEBUG_CONSOLE_MARGINS * 2;
    
    debug_console_clear_console(debug_console, render_buffer);
    
    for (i = 0; i < DEBUG_CONSOLE_MESSAGES; ++i) {
        if (debug_console->messages[i].msg_str[0] != '\0') {
            font_draw_string(font, debug_console->messages[i].msg_str, max_width, x_pos, y_pos, 1,
                debug_console->messages[i].color, render_buffer);
        }
        y_pos -= (7 + 7);
    }
}
