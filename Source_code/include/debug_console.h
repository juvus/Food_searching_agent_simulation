/*================================================================================*/
/* Header file for the debug console class                                        */
/*================================================================================*/

#ifndef DEBUG_CONSOLE_H_
#define DEBUG_CONSOLE_H_

#include <utils.h>
#include <font.h>

struct Message {
    char *msg_str; /* Message string */
    u32 color; /* Font color */ 
};
typedef struct Message Message_t;

struct DConsole {
    u32 x;  /* BL corner x coordinate of the console */
    u32 y;  /* BL corner y coordinate of the console */
    u32 height; /* Height will be determined from DCONSOLE_MESSAGES */ 
    u32 width;  /* Width of the debug console */
    u32 message_index;  /* Pointer to the current available message line in the console */
    Message_t *messages;  /* Pointer to the debug console message */
    char str_buffer[255];  /* Temporary buffer for the debug string */
};
typedef struct DConsole DConsole_t;
/* Function to initialize the debug console */
void dconsole_init(DConsole_t *dconsole, u32 x, u32 y, u32 width);

/* Function to add a string to the debug console */
void dconsole_add_message(DConsole_t *dconsole, char *msg_str, u32 color);

/* Function to delete the all messages */
void dconsole_clear_messages(DConsole_t *dconsole);

/* Function to clear the console from the all messages */
void dconsole_clear_console(DConsole_t *dconsole, Render_Buffer_t *render_buffer);

/* Function to hide the console */
void dconsole_hide(DConsole_t *dconsole, Render_Buffer_t *render_buffer);

/* Function to render the console with all messages */
void dconsole_render(DConsole_t *dconsole, Symbol_data_t *font_symbols, Render_Buffer_t *render_buffer);

#endif // DEBUG_CONSOLE_H_
