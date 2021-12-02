/*
================================================================================
Filename: info_panel.h
Description: Header file for the information panel class.
================================================================================
*/

#ifndef INFO_PANEL_H_
#define INFO_PANEL_H_

#include <utils.h>
#include <field_panel.h>

/* Structure of the information panel */
struct Info_Panel
{
    V2_u32_t BL;  /* Bottom left corner possition of the panel */
    u32 width;  /* Width of the panel */
    u32 height;  /* Height of the panel */
    u32 brd_width;  /* Width of the borders */
    u32 bkg_color;  /* Color of the background */
    u32 brd_color;  /* Color of the panel borders */
    u32 caption_bkg_color;  /* Color of the panel caption background */
    u32 caption_height;  /* Height if the panel caption */
    char caption[INFO_PANEL_MAX_CAPTION_LENGTH];  /* Caption of the panel */
};
typedef struct Info_Panel Info_Panel_t;

/* Declaration of the Info_Panel member fuctions */

/* Constructor of the Info_Panel object */
Info_Panel_t* info_panel_constructor(void);

/* Destructor of the Info_Panel object */
void info_panel_destructor(Info_Panel_t *info_panel);

/* Initialization of the Info_Panel object */
void info_panel_init(Info_Panel_t *info_panel, Field_Panel_t *field_panel,
    Render_Buffer_t *render_buffer);

/* Method for render the Info_Panel object */
void info_panel_render(Info_Panel_t *info_panel, Font_t *font, Render_Buffer_t *render_buffer);

#endif /* INFO_PANEL_H_ */
