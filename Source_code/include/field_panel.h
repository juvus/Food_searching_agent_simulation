/*
================================================================================
Filename: field_panel.h
Description: Header file for the field panel class.
================================================================================
*/

#ifndef FIELD_PANEL_H_
#define FIELD_PANEL_H_

#include <utils.h>
#include <font.h>
#include <simulation_constants.h>

/* Structure of the field panel*/
struct Field_Panel
{
   V2_u32_t BL;  /* Bottom left corner possition of the panel */
   u32 width;  /* Width of the panel */
   u32 height;  /* Height of the panel */
   u32 brd_width;  /* Width of the borders */
   u32 bkg_color;  /* Color of the background */
   u32 brd_color;  /* Color of the field borders */
   u32 caption_bkg_color;  /* Color of the panel caption background */
   u32 caption_height;  /* Height if the panel caption */
   char caption[FIELD_PANEL_MAX_STR_LENGTH];  /* Caption of the panel */
};
typedef struct Field_Panel Field_Panel_t;

/* Declaration of the Field_Panel member fuctions */

/* Constructor of the Field_Panel object */
Field_Panel_t* field_panel_constructor(void);

/* Destructor of the Field_Panel object */
void field_panel_destructor(Field_Panel_t *field_panel);

/* Initialization of the Field_Panel object */
void field_panel_init(Field_Panel_t *field_panel, Render_Buffer_t *render_buffer);

/* Method for render the Field_Panel object */
void field_panel_render(Field_Panel_t *field_panel, Font_t *font, Render_Buffer_t *render_buffer);

#endif /* FIELD_PANEL_H_ */
