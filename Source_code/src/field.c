/*
================================================================================
Filename: field.c
Description: Definition of the field class member functions.
================================================================================
*/

#define _USE_MATH_DEFINES

/* Standard includes: */
#include <stdlib.h>
#include <assert.h>

/* Program includes: */
#include <field.h>
#include <utils.h>
#include <simulation_constants.h>
#include <software_rendering.h>

Field_t*
field_constructor(void)
{
    /* Constructor of the field object */
    Field_t *field = (Field_t*) malloc (1 * sizeof(Field_t)); 
    if (field == NULL)
    {
        assert(0 && "ERROR: Error in memory allocation for the field object");
    }
    return field;
}

void
field_destructor(Field_t *field)
{
    /* Destructor of the field object */
    if (field)
    {
        free(field);
        return 0;
    }
    assert(0 && "ERROR: Memory for field object was not previously allocated");
}

void
field_init(Field_t *field, Render_Buffer_t *render_buffer)
{
    /* Initialization of the field object */
    field->height = render_buffer->height - PADDING_WIDTH * 2;
    field->width = field->height;
    field->bkg_color = FIELD_BKG_COLOR;
    field->brd_width = FIELD_BRD_WIDTH;
    field->brd_color = FIELD_BRD_COLOR;
    
    /* Calculation the position of the bottom-left corner of the field object */
    field->BL.x = PADDING_WIDTH;
    field->BL.y = PADDING_WIDTH;
}

void
field_render(Field_t *field, Render_Buffer_t *render_buffer)
{
    /* Method for render the field object in the window */
    draw_rect_with_brd(field->BL.x, field->BL.y, field->width, field->height, 
        field->brd_width, field->bkg_color, field->brd_color, render_buffer);
}