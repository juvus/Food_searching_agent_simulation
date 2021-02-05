/*
================================================================================
Filename: info_panel.c
Description: Definition of the Info_Panel class member functions.
================================================================================
*/

#define _USE_MATH_DEFINES

/* Standard includes: */
#include <stdlib.h>
#include <assert.h>

/* Program includes: */
#include <info_panel.h>
#include <field_panel.h>
#include <utils.h>
#include <simulation_constants.h>
#include <software_rendering.h>

Info_Panel_t*
info_panel_constructor(void)
{
    /* Constructor of the Info_Panel object */
    Info_Panel_t *info_panel = (Info_Panel_t*) malloc (1 * sizeof(Info_Panel_t)); 
    if (info_panel == NULL)
    {
        assert(0 && "ERROR: Error in memory allocation for the Info_Panel object");
    }
    return info_panel;
}

void
info_panel_destructor(Info_Panel_t *info_panel)
{
    /* Destructor of the Info_Panel object */
    if (info_panel)
    {
        free(info_panel);
        return 0;
    }
    assert(0 && "ERROR: Memory for the Info_Panel object was not previously allocated");
}

void
info_panel_init(Info_Panel_t *info_panel, Field_Panel_t *field_panel, Render_Buffer_t *render_buffer)
{
    /* Initialization of the Info_Panel object */
    info_panel->width = render_buffer->width - field_panel->width - 3 * PADDING_WIDTH;
    info_panel->height = INFO_PANEL_HEIGHT;

    info_panel->bkg_color = INFO_PANEL_BKG_COLOR;
    info_panel->brd_color = INFO_PANEL_BRD_COLOR;
    info_panel->brd_width = INFO_PANEL_BRD_WIDTH;
    info_panel->caption_height = INFO_PANEL_CAPTION_HEIGHT;
    info_panel->caption_bkg_color = INFO_PANEL_CAPTION_BKG_COLOR;
    
    /* Calculation the position of the bottom-left corner of the Info_Panel object */
    info_panel->BL.x = field_panel->BL.x + field_panel->width + PADDING_WIDTH;
    info_panel->BL.y = field_panel->BL.y + field_panel->height - info_panel->height;
}

void
info_panel_render(Info_Panel_t *info_panel, Render_Buffer_t *render_buffer)
{
    /* Method for render the Info_Panel object in the window */
    u32 x, y;  /* Temporary coordinates */
    
    /* Render the information table */
    draw_rect_with_brd(info_panel->BL.x, info_panel->BL.y, info_panel->width, info_panel->height, 
        info_panel->brd_width, info_panel->bkg_color, info_panel->brd_color, render_buffer);

    /* Render the caption */
    x = info_panel->BL.x;
    y = info_panel->BL.y + info_panel->height - info_panel->caption_height;
    draw_rect_with_brd(x, y, info_panel->width, info_panel->caption_height, info_panel->brd_width,
        info_panel->caption_bkg_color, info_panel->brd_color, render_buffer);
}