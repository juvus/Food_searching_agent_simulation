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
    char caption[INFO_PANEL_MAX_STR_LENGTH];  /* Caption of the panel */
    char help_str_start_sim[INFO_PANEL_MAX_STR_LENGTH];  /* Help string for start simulation */
    char help_str_pause_sim[INFO_PANEL_MAX_STR_LENGTH];  /* Help string for pause simulation */
    char help_str_stop_sim[INFO_PANEL_MAX_STR_LENGTH];  /* Help string for stop simulation */
    char str_total_moves_capt[INFO_PANEL_MAX_STR_LENGTH];  /* String for total moves parameter caption */
    char str_total_moves_val[INFO_PANEL_MAX_STR_LENGTH];  /* String for total moves parameter value */
    u32 total_moves;  /* Number of the total moves */
    char str_total_points_capt[INFO_PANEL_MAX_STR_LENGTH];  /* String for total point parameter caption */
    char str_total_points_val[INFO_PANEL_MAX_STR_LENGTH];  /* String for total point parameter value */
    u32 total_points;  /* Number of the total points */
    char str_points_per_move_capt[INFO_PANEL_MAX_STR_LENGTH];  /* String for the point per move parameter caption */
    char str_points_per_move_val[INFO_PANEL_MAX_STR_LENGTH];  /* String for the point per move parameter value */
    f32 points_per_move;  /* Number of the total points */
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

/* Method for updating the value strings with current values of the given performance parameters. */
void info_panel_update_str_parameters(Info_Panel_t *info_panel, u32 total_moves, u32 total_points,
    f32 points_per_move);

/* Method for render the Info_Panel object */
void info_panel_render(Info_Panel_t *info_panel, Font_t *font, Render_Buffer_t *render_buffer);

#endif /* INFO_PANEL_H_ */
