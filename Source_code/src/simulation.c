/*
===============================================================================
Filename: simulation.c
Description: Definition of the simulation class methods. Main logic loop of
    the simulation.
Some additional text
===============================================================================
*/

#define _USE_MATH_DEFINES

/* Standard includes: */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

/* Program includes: */
#include <simulation.h>
#include <software_rendering.h>
#include <utils.h>
#include <input_treatment.h>
#include <file_io.h>
#include <font.h>
#include <dbg.h>  /* Console debug */
#include <debug_console.h>  /* Graphic console debug */
#include <simulation_constants.h>

/* Simulation classes */
#include <field_panel.h>
#include <info_panel.h>
#include <plot_panel.h>
#include <misc.h>

/* Loaded images */
static Loaded_img_t font_img;  /* Image with font symbols */

/* Define different parameters for the simulation */
static Simulation_t simulation = {0};  /* Simulation object */
static Simulation_State_t simulation_state = SIM_ST_LOAD_RESOURCES;  /* Simulation state */
static Debug_Console_t *debug_console;  /* Debug console with messages */
static Font_t *font;  /* Pointer to the font */
static LARGE_INTEGER begin_counter;  /* Union for for dtime calculation */
static LARGE_INTEGER end_counter;  /* Union for for dtime calculation */
static LARGE_INTEGER frequency_counter;  /* Union for for dtime calculation */
static LONGLONG begin;  /* Variable for dtime calculation */
static LONGLONG end;  /* Variable for dtime calculation */
static LONGLONG frequency;  /* Variable for dtime calculation */

/* Define different game variables */
static Field_Panel_t *field_panel;  /* Pointer to the field panel object */
static Info_Panel_t *info_panel;  /* Pointer to the information panel object */
static Plot_Panel_t *plot_panel;  /* Pointer to the plot panel object */
//static Agent_t agent; /* Structure of the searching agent */
static f32 x, y; /* Temporary coordinates */
static u32 i, j, k; /* Temporary indexes */


void 
simulation_calculate_tick(Input_t *user_input, Render_Buffer_t *render_buffer)
{
    /* Main function for the game simulation */
  
    f32 dtime_orig = simulation.dtime;
    //simulation.dtime = 0.001; //for testing

    switch (simulation_state) 
    {
        /* State for loading the different resource data IMAGES */
        case SIM_ST_LOAD_RESOURCES: 
        {    
            /* Symbols of the font */
            font_img.raw_data = read_file_to_memory("data\\font.png");
            uncompress_png_image(&font_img);
            
            /* Agent image */
            //agent_img.raw_data = read_file_to_memory("data\\agent.png");
            //uncompress_png_image(&agent_img);
            
            /* Food image */
            //food_img.raw_data = read_file_to_memory("data\\food.png");
            //uncompress_png_image(&food_img);

            /* Jump to the memory allocation state */
            simulation_state = SIM_ST_MEMORY_ALLOCATION;
            break;
        }

        /* State for dynamic allocation of different objects for the simulation */
        case SIM_ST_MEMORY_ALLOCATION: 
        {
            /* Set of object constructors */       
            font = font_constructor();
            debug_console = debug_console_constructor();
            field_panel = field_panel_constructor();
            info_panel = info_panel_constructor();
            plot_panel = plot_panel_constructor();

            /* Jump to the simulation initialization state */
            simulation_state = SIM_ST_INITIALIZATION;
            break;
        }

        /* State for simulation initialization procedure */    
        case SIM_ST_INITIALIZATION: 
        {
            /* Seed the random numbers */
            srand(time(NULL));      

            /* Prepare the font to use */
            font_init(font, &font_img);
        
            /* Initialization of the different simulation objects */
            field_panel_init(field_panel, render_buffer);
            info_panel_init(info_panel, field_panel, render_buffer);
            plot_panel_init(plot_panel, info_panel, field_panel, render_buffer);
            
            /* Initial render of game elements: */
            clear_full_screen(BKG_COLOR, render_buffer);
            field_panel_render(field_panel, font, render_buffer);
            info_panel_render(info_panel, font, render_buffer);
            plot_panel_render(plot_panel, font, render_buffer);
            
            /* Initialization of the debug console */
            debug_console_init(debug_console, 50, 100, 300);

            /* Function for the thread of main simulation loop */
            QueryPerformanceCounter(&begin_counter);
            QueryPerformanceFrequency(&frequency_counter);
            simulation.dtime = 0.01666f; /* Initial dtime value */
            simulation.cum_time = 0.0f;  /* Initial cumulative time of the game */

            /* Jump to the simulation main loop state */
            simulation_state = SIM_ST_LOGIC_RUN;
            break;
        }

        /* State for the simulation main logic loop */
        case SIM_ST_LOGIC_RUN:
        {
            /* Test of the debug console */
            debug_console_clear_messages(debug_console);
            debug_console_clear_console(debug_console, render_buffer);
            sprintf_s(debug_console->str_buffer, DEBUG_CONSOLE_MAX_MSG_LENGTH, "%s",
                "Hello, world!!!");
            debug_console_add_message(debug_console, debug_console->str_buffer, 0x0000ff);
            sprintf_s(debug_console->str_buffer, DEBUG_CONSOLE_MAX_MSG_LENGTH, "%s%5.3lf", 
                "dtime: ", dtime_orig);
            debug_console_add_message(debug_console, debug_console->str_buffer, 0xff0000);
            sprintf_s(debug_console->str_buffer, DEBUG_CONSOLE_MAX_MSG_LENGTH, "%s%5.3lf", 
                "FPS: ", (1.0f / dtime_orig));
            debug_console_add_message(debug_console, debug_console->str_buffer, 0xff0000);
            debug_console_render(debug_console, font, render_buffer);
            
            /* Some simulation logic code here */

            /* Calculate the delta time */
            QueryPerformanceCounter(&end_counter);
            begin = begin_counter.QuadPart;
            end = end_counter.QuadPart;
            frequency = frequency_counter.QuadPart;
            simulation.dtime = (f32)((end - begin) / (f32)frequency);
            simulation.cum_time += simulation.dtime;
            begin_counter = end_counter;
            break;
        } 

        /* State for the simulation finalization procedure */
        case 5: 
        { 
            /* Jump to the initialization state */
            simulation_state = SIM_ST_INITIALIZATION;
            break;
        } 
    } /* switch (simulation_state) */
}
