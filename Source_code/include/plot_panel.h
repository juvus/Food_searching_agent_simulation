/*
================================================================================
Filename: plot_panel.h
Description: Header file for the plot panel class.
================================================================================
*/

#ifndef PLOT_PANEL_H_
#define PLOT_PANEL_H_

#include <utils.h>
#include <info_panel.h>
#include <field_panel.h>

/* Structure of the plot panel */
struct Plot_Panel
{
    V2_u32_t BL;  /* Bottom left corner possition of the panel */
    u32 width;  /* Width of the panel */
    u32 height;  /* Height of the panel */
    u32 brd_width;  /* Width of the borders */
    u32 bkg_color;  /* Color of the background */
    u32 brd_color;  /* Color of the panel borders */
    u32 caption_bkg_color;  /* Color of the panel caption background */
    u32 caption_height;  /* Height if the panel caption */
    char caption[PLOT_PANEL_MAX_CAPTION_LENGTH];  /* Caption of the panel */
};
typedef struct Plot_Panel Plot_Panel_t;

/* Declaration of the Plot_Panel member fuctions */

/* Constructor of the Plot_Panel object */
Plot_Panel_t* plot_panel_constructor(void);

/* Destructor of the Plot_Panel object */
void plot_panel_destructor(Plot_Panel_t *plot_panel);

/* Initialization of the Plot_Panel object */
void plot_panel_init(Plot_Panel_t *plot_panel, Info_Panel_t *info_panel, Field_Panel_t *field_panel, 
   Render_Buffer_t *render_buffer);

/* Method for render the Plot_Panel object */
void plot_panel_render(Plot_Panel_t *plot_panel, Font_t *font, Render_Buffer_t *render_buffer);

#endif /* PLOT_PANEL_H_ */
