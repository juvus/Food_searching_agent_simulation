/*
================================================================================
Filename: field.h
Description: Header file for the field class.
================================================================================
*/

#ifndef FIELD_H_
#define FIELD_H_

#include <utils.h>
#include <stdlib.h>
#include <file_io.h>

/* Structure of the field */
struct Field
{
   V2_u32_t BL;  /* Bottom left corner possition of the field */
   u32 width;  /* Width of the field */
   u32 height;  /* Height of the field */
   u32 brd_width;  /* Width of the borders */
   u32 bkg_color;  /* Color of the background */
   u32 brd_color;  /* Color of the field borders */
};
typedef struct Field Field_t;

/* Declaration of the Field member fuctions */

/* Constructor of the field object */
Field_t* field_constructor(void);

/* Destructor of the field object */
void field_destructor(Field_t *field);

/* Initialization of the field object */
void field_init(Field_t *field, Render_Buffer_t *render_buffer);

/* Method for render the field object */
void field_render(Field_t *field, Render_Buffer_t *render_buffer);

#endif /* FIELD_H_ */
