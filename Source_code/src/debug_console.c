/*================================================================================*/
/* Realization of debug console methods                                           */
/*================================================================================*/

#include <utils.h>
#include <debug_console.h>
#include <software_rendering.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <font.h>
#include <simulation_constants.h>

/* Realization of the interface functions */
void
dconsole_init(DConsole_t *dconsole, u32 x, u32 y, u32 width)
{
    /* Function to initialize the debug console */

    Message_t *messages; 
    char *tmp_msg_str;
    u32 i;
    
    dconsole->x = x;
    dconsole->y = y;
    dconsole->width = width;
    dconsole->height = DCONSOLE_MARGINS * 2 + DCONSOLE_MESSAGES * 7 + \
        (DCONSOLE_MESSAGES - 1) * 7; /* last digit - lines intend in pixels */

    /* Allocate the memory for the array of messages */
    messages = (Message_t *) calloc (DCONSOLE_MESSAGES, sizeof(Message_t));
    dconsole->messages = messages;

    /* Allocate the memory for message strings */
    for (i = 0; i < DCONSOLE_MESSAGES; ++i) {
        tmp_msg_str = (char *) calloc (DCONSOLE_MAX_MSG_LENGTH, sizeof(char));
        dconsole->messages[i].msg_str = tmp_msg_str;
        dconsole->messages[i].msg_str[0] = '\0';
    }
    
    dconsole->message_index = 0;  
}

void
dconsole_add_message(DConsole_t *dconsole, char *msg_str, u32 color)
{
    /* Function to add a string to the debug console */

    /* Length of the msg_str should be less than 100 symbols */
    assert(strlen(msg_str) <= 100);

    u32 index = dconsole->message_index;
    dconsole->messages[index].color = color;
    strcpy_s(dconsole->messages[index].msg_str, DCONSOLE_MAX_MSG_LENGTH, msg_str);
    dconsole->message_index++;
    
    /* For safe in case of adding more messages than possible to store */
    if (dconsole->message_index >= 10) {
        dconsole->message_index = 0;
    }
}

void
dconsole_clear_messages(DConsole_t *dconsole)
{
    /* Function to delete the all messages */

    u32 i;

    for (i = 0; i < DCONSOLE_MESSAGES; ++i) {
        dconsole->messages[i].msg_str[0] = '\0';
    }
    dconsole->message_index = 0;
}

void
dconsole_clear_console(DConsole_t *dconsole, Render_Buffer_t *render_buffer)
{
    /* Function to clear the console from the all messages */      
    
    draw_rect_with_brd(dconsole->x, dconsole->y, dconsole->width, dconsole->height, 1,
                       DCONSOLE_BKG_COLOR, DCONSOLE_BRD_COLOR, render_buffer);   
}

void
dconsole_hide(DConsole_t *dconsole, Render_Buffer_t *render_buffer)
{
    /* Function to hide the console */

    draw_rect(dconsole->x , dconsole->y, dconsole->width, dconsole->height,
              BKG_COLOR, render_buffer);
}

void
dconsole_render(DConsole_t *dconsole, Symbol_data_t *font_symbols, Render_Buffer_t *render_buffer)
{
    /* Function to render the console with all messages */

    u32 x_pos;
    u32 y_pos;
    u32 i;
    u32 max_width;
    
    x_pos = dconsole->x + DCONSOLE_MARGINS; 
    y_pos = dconsole->y + dconsole->height - DCONSOLE_MARGINS - 7;  
    max_width = dconsole->width - DCONSOLE_MARGINS * 2;
    
    dconsole_clear_console(dconsole, render_buffer);
    
    for (i = 0; i < DCONSOLE_MESSAGES; ++i) {
        if (dconsole->messages[i].msg_str[0] != '\0') {

            /* @ Add somehow the possibility to cut the string with .... pass
             to the function the -1 or maximum width in pixels, not the amount of characters!!!*/
            
            font_draw_string(dconsole->messages[i].msg_str, max_width, x_pos, y_pos, 1,
                             dconsole->messages[i].color, font_symbols, render_buffer);
        }
        y_pos -= (7 + 7);
    }
}
