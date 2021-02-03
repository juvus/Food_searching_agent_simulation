/*
===============================================================================
Declaration of the simulation class data structures and methods
===============================================================================
*/

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <utils.h>
#include <input_treatment.h>
#include <file_io.h>

/* Enumerator for holding simulation states */
enum Simulation_State
{
    SIM_ST_LOAD_RESOURCES,  /* State for load different resources */
    SIM_ST_MEMORY_ALLOCATION,  /* State for dynamic memory allocation */
    SIM_ST_INITIALIZATION,  /* State for simulation initialization procedure */
    SIM_ST_LOGIC_RUN,  /* State for the main logic run of the simulation */
    SIM_ST_FINISH  /* State for the finalizing the simulation */
};
typedef enum Simulation_State Simulation_State_t;

/* Structure of the simulation class */
struct Simulation
{
    f32 dtime; /* Time delta between the game ticks (in sec) */
    f32 cum_time;  /* Cumulative time of the game (in sec) */
};
typedef struct Simulation Simulation_t; 

/* Main entry point to the game logic procedure */
void simulation_calculate_tick(Input_t *user_input, Render_Buffer_t *render_buffer);

#endif /* SIMULATION_H_ */
