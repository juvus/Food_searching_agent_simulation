/*
================================================================================
Filename: field_panel.c
Description: Definition of the Field_Panel class member functions.
================================================================================
*/

#define _USE_MATH_DEFINES

/* Standard includes: */
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/* Program includes: */
#include <field_panel.h>
#include <utils.h>
#include <software_rendering.h>
#include <font.h>
#include <simulation_constants.h>

Field_Panel_t*
field_panel_constructor(void)
{
    /* Constructor of the Field_Panel object */
    Field_Panel_t *field_panel = (Field_Panel_t*) malloc (1 * sizeof(Field_Panel_t)); 
    if (field_panel == NULL)
    {
        assert(0 && "ERROR: Error in memory allocation for the Field_Panel object");
    }
    return field_panel;
}

void
field_panel_destructor(Field_Panel_t *field_panel)
{
    /* Destructor of the Field_Panel object */
    if (field_panel)
    {
        free(field_panel);
        return;
    }
    assert(0 && "ERROR: Memory for Field_Panel object was not previously allocated");
}

void
field_panel_init(Field_Panel_t *field_panel, Render_Buffer_t *render_buffer)
{
    /* Initialization of the Field_Panel object */
   
    field_panel->height = render_buffer->height - PADDING_WIDTH * 2;
    field_panel->width = field_panel->height;
    field_panel->bkg_color = FIELD_PANEL_BKG_COLOR;
    field_panel->brd_width = FIELD_PANEL_BRD_WIDTH;
    field_panel->brd_color = FIELD_PANEL_BRD_COLOR;
    field_panel->caption_height = FIELD_PANEL_CAPTION_HEIGHT;
    field_panel->caption_bkg_color = FIELD_PANEL_CAPTION_BKG_COLOR;
    sprintf_s(field_panel->caption, FIELD_PANEL_MAX_STR_LENGTH, "%s", "Field panel");
    
    /* Calculation the position of the bottom-left corner of the Field_Panel object */
    field_panel->BL.x = PADDING_WIDTH;
    field_panel->BL.y = PADDING_WIDTH;
}

void
field_panel_render(Field_Panel_t *field_panel, Font_t *font, Render_Buffer_t *render_buffer)
{
    /* Method for render the Field_Panel object in the window */
    u32 x, y;  /* Temporary coordinates */
    
    draw_rect_with_brd(field_panel->BL.x, field_panel->BL.y, field_panel->width, field_panel->height, 
        field_panel->brd_width, field_panel->bkg_color, field_panel->brd_color, render_buffer);

    /* Render the caption */
    x = field_panel->BL.x;
    y = field_panel->BL.y + field_panel->height - field_panel->caption_height;
    draw_rect_with_brd(x, y, field_panel->width, field_panel->caption_height, field_panel->brd_width,
        field_panel->caption_bkg_color, field_panel->brd_color, render_buffer);

    /* Render the caption text */
    x += 15;
    y += 8;
    font_draw_string(font, field_panel->caption, field_panel->width, x, y, 2, 0x000000, 
        render_buffer);
}
