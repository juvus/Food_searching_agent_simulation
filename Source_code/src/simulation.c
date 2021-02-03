/*
===============================================================================
Definition of the simulation class methods. Main logic loop of the simulation.
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
//#include <arena.h> inclides for the simulation objects
#include <misc.h>

/* Loaded images */
static Loaded_img_t font_img;  /* Image with font symbols */
//static Loaded_img_t agent_img;  /* Image of the food searching agent */
//static Loaded_img_t food_img;  /* Image of the food */

/* Define different parameters for game systems  */
static Simulation_t simulation = {0};  /* Simulation object */
static Simulation_State_t simulation_state = SIM_ST_LOAD_RESOURCES;  /* Simulation state */
static DConsole_t dconsole;  /* Debug console with messages */
static Symbol_data_t *font_symbols;  /* Pointer to the array of all font symbols */
static LARGE_INTEGER begin_counter;  /* Union for for dtime calculation */
static LARGE_INTEGER end_counter;  /* Union for for dtime calculation */
static LARGE_INTEGER frequency_counter;  /* Union for for dtime calculation */
static LONGLONG begin;  /* Variable for dtime calculation */
static LONGLONG end;  /* Variable for dtime calculation */
static LONGLONG frequency;  /* Variable for dtime calculation */

/* Define different game variables */
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
            font_symbols = (Symbol_data_t *) calloc (SYM_ROWS * SYM_COLS, sizeof(Symbol_data_t));       

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
            font_extract_symbols(font_symbols, &font_img);
        
            /* Initial render of game elements: */
            clear_full_screen(BKG_COLOR, render_buffer);

            /* Initialization of the debug console */
            dconsole_init(&dconsole, 50, 100, 300);

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
            dconsole_clear_messages(&dconsole);
            dconsole_clear_console(&dconsole, render_buffer);
            sprintf_s(dconsole.str_buffer, DCONSOLE_MAX_MSG_LENGTH, "%s", "Hello, world!!!");
            dconsole_add_message(&dconsole, dconsole.str_buffer, 0x0000ff);
            sprintf_s(dconsole.str_buffer, DCONSOLE_MAX_MSG_LENGTH, "%s%5.3lf", "dtime: ", dtime_orig);
            dconsole_add_message(&dconsole, dconsole.str_buffer, 0xff0000);
            sprintf_s(dconsole.str_buffer, DCONSOLE_MAX_MSG_LENGTH, "%s%5.3lf", "FPS: ", (1.0f / dtime_orig));
            dconsole_add_message(&dconsole, dconsole.str_buffer, 0xff0000);
            dconsole_render(&dconsole, font_symbols, render_buffer);
            
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
