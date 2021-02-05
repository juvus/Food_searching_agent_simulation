/*
===============================================================================
Filename: font.h
Description: Header file for the font class.
===============================================================================
*/

#ifndef FONT_H_
#define FONT_H_

#include <utils.h>
#include <file_io.h>

/* Structure to store the single symbol information */
struct Symbol_data {
    u8 symbol;  /* ASCII representation of the symbol (for 32 - 126 codes)*/
    u8 symbol_array[42];  /* Array to storing the symbol pixel data */
    u8 shift_left;  /* How much to shift the next symbol to the left */
    u8 shift_bottom;  /* How much to thift the symbol to bottom */
};
typedef struct Symbol_data Symbol_data_t;

/* Structure to the font object */
struct Font
{
    Loaded_img_t *font_img;  /* Pointer to the image containing the font */
    Symbol_data_t *symbols_data;  /* Pointer to the set of symbol_data elements  */
};
typedef struct Font Font_t;

/* Declaration of the Font member fuctions */

/* Constructor of the Font object */
Font_t* font_constructor(void);

/* Destructor of the Font object */
void font_destructor(Font_t *font);

/* Initialization of the Font object */
void font_init(Font_t *font, Loaded_img_t *font_img);

/* Method for drawing an arbitrary string using font */
void font_draw_string(Font_t *font, char *str, s32 str_max_width, u32 x, u32 y, u32 size, u32 color,
    Render_Buffer_t *render_buffer);

#endif // FONT_H_
