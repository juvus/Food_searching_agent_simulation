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
#include <stdio.h>

/* Program includes: */
#include <info_panel.h>
#include <field_panel.h>
#include <utils.h>
#include <software_rendering.h>
#include <font.h>
#include <simulation_constants.h>

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
        return;
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
    
    sprintf_s(info_panel->caption, INFO_PANEL_MAX_STR_LENGTH, "%s", "Info panel");
    sprintf_s(info_panel->help_str_start_sim, INFO_PANEL_MAX_STR_LENGTH, "%s", "1 - Start simulation");
    sprintf_s(info_panel->help_str_pause_sim, INFO_PANEL_MAX_STR_LENGTH, "%s", "2 - Pause simulation");
    sprintf_s(info_panel->help_str_stop_sim, INFO_PANEL_MAX_STR_LENGTH, "%s", "3 - Stop simulation");
    sprintf_s(info_panel->str_total_moves_capt, INFO_PANEL_MAX_STR_LENGTH, "%s", "Total moves:");
    sprintf_s(info_panel->str_total_points_capt, INFO_PANEL_MAX_STR_LENGTH, "%s", "Total points:");
    sprintf_s(info_panel->str_points_per_move_capt, INFO_PANEL_MAX_STR_LENGTH, "%s", "Points per move:");

    /* Put initial values to the strings, representing performance parameters */
    info_panel_update_str_parameters(info_panel, 100, 50, 345.123);
    
    /* Calculation the position of the bottom-left corner of the Info_Panel object */
    info_panel->BL.x = field_panel->BL.x + field_panel->width + PADDING_WIDTH;
    info_panel->BL.y = field_panel->BL.y + field_panel->height - info_panel->height;
}

void
info_panel_update_str_parameters(Info_Panel_t *info_panel, u32 total_moves, u32 total_points,
    f32 points_per_move)
{
    /* Method for updating the value strings with current values of the given 
       performance parameters. */

    /* Process the total moves parameter */
    info_panel->total_moves = total_moves;
    sprintf_s(info_panel->str_total_moves_val, INFO_PANEL_MAX_STR_LENGTH, "%d", total_moves);

    /* Process the total points parameter */
    info_panel->total_points = total_points;
    sprintf_s(info_panel->str_total_points_val, INFO_PANEL_MAX_STR_LENGTH, "%d", total_points);

    /* Process the points per move parameter */
    info_panel->points_per_move = points_per_move;
    sprintf_s(info_panel->str_points_per_move_val, INFO_PANEL_MAX_STR_LENGTH, "%.3f", points_per_move);
}

void
info_panel_render(Info_Panel_t *info_panel, Font_t *font, Render_Buffer_t *render_buffer)
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

    /* Render the caption text */
    x += 15;
    y += 8;
    font_draw_string(font, info_panel->caption, (s32)info_panel->width, x, y, 2, 0x000000, 
        render_buffer);

    /* Render the help information */
    y -= 60;
    font_draw_string(font, info_panel->help_str_start_sim, (s32)info_panel->width, x, y, 2, 0x000000, 
        render_buffer);

    y -= 30;
    font_draw_string(font, info_panel->help_str_pause_sim, (s32)info_panel->width, x, y, 2, 0x000000, 
        render_buffer);

    y -= 30;
    font_draw_string(font, info_panel->help_str_stop_sim, (s32)info_panel->width, x, y, 2, 0x000000, 
        render_buffer);

    /* Render set of performance metrics */
    /* Render total points */
    y -= 60;
    font_draw_string(font, info_panel->str_total_points_capt, (s32)info_panel->width, x, y, 2, 0x000000, 
        render_buffer);
    y -= 30;
    font_draw_string(font, info_panel->str_total_points_val, (s32)info_panel->width, x, y, 2, 0x0000f0, 
        render_buffer);

    /* Render total moves */
    y -= 30;
    font_draw_string(font, info_panel->str_total_moves_capt, (s32)info_panel->width, x, y, 2, 0x000000, 
        render_buffer);
    y -= 30;
    font_draw_string(font, info_panel->str_total_moves_val, (s32)info_panel->width, x, y, 2, 0x0000f0, 
        render_buffer);

    /* Render points per move */
    y -= 30;
    font_draw_string(font, info_panel->str_points_per_move_capt, (s32)info_panel->width, x, y, 2, 0x000000, 
        render_buffer);
    y -= 30;
    font_draw_string(font, info_panel->str_points_per_move_val, (s32)info_panel->width, x, y, 2, 0x0000f0, 
        render_buffer);
}
