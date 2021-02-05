/*
================================================================================
Filename: plot_panel.c
Description: Definition of the Plot_Panel class member functions.
================================================================================
*/

#define _USE_MATH_DEFINES

/* Standard includes: */
#include <stdlib.h>
#include <assert.h>

/* Program includes: */
#include <plot_panel.h>
#include <info_panel.h>
#include <field_panel.h>
#include <utils.h>
#include <simulation_constants.h>
#include <software_rendering.h>

Plot_Panel_t*
plot_panel_constructor(void)
{
    /* Constructor of the Plot_Panel object */
    Plot_Panel_t *plot_panel = (Plot_Panel_t*) malloc (1 * sizeof(Plot_Panel_t)); 
    if (plot_panel == NULL)
    {
        assert(0 && "ERROR: Error in memory allocation for the Plot_Panel object");
    }
    return plot_panel;
}

void
plot_panel_destructor(Plot_Panel_t *plot_panel)
{
    /* Destructor of the Plot_Panel object */
    if (plot_panel)
    {
        free(plot_panel);
        return 0;
    }
    assert(0 && "ERROR: Memory for the Plot_Panel object was not previously allocated");
}

void
plot_panel_init(Plot_Panel_t *plot_panel, Info_Panel_t *info_panel, Field_Panel_t *field_panel, 
    Render_Buffer_t *render_buffer)
{
    /* Initialization of the Plot_Panel object */
    plot_panel->width = render_buffer->width - field_panel->width - 3 * PADDING_WIDTH;
    plot_panel->height = render_buffer->height - info_panel->height - 3 *PADDING_WIDTH;
    
    plot_panel->bkg_color = PLOT_PANEL_BKG_COLOR;
    plot_panel->brd_color = PLOT_PANEL_BRD_COLOR;
    plot_panel->brd_width = PLOT_PANEL_BRD_WIDTH;
    plot_panel->caption_height = PLOT_PANEL_CAPTION_HEIGHT;
    plot_panel->caption_bkg_color = PLOT_PANEL_CAPTION_BKG_COLOR;
    
    /* Calculation the position of the bottom-left corner of the Plot_Panel object */
    plot_panel->BL.x = info_panel->BL.x;
    plot_panel->BL.y = field_panel->BL.y;
}

void
plot_panel_render(Plot_Panel_t *plot_panel, Render_Buffer_t *render_buffer)
{
    /* Method for render the Plot_Panel object in the window */
    u32 x, y;  /* Temporary coordinates */
    
    /* Render the plot panel */
    draw_rect_with_brd(plot_panel->BL.x, plot_panel->BL.y, plot_panel->width, plot_panel->height, 
        plot_panel->brd_width, plot_panel->bkg_color, plot_panel->brd_color, render_buffer);

    /* Render the caption */
    x = plot_panel->BL.x;
    y = plot_panel->BL.y + plot_panel->height - plot_panel->caption_height;
    draw_rect_with_brd(x, y, plot_panel->width, plot_panel->caption_height, plot_panel->brd_width,
        plot_panel->caption_bkg_color, plot_panel->brd_color, render_buffer);
}