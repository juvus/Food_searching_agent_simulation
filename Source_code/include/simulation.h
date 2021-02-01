#ifndef GAME_H_
#define GAME_H_

#include <utils.h>
#include <input_treatment.h>
#include <file_io.h>
#include <sound_buffer.h>

/* Enumerator for the different game modes */
enum Game_Mode {
    GM_NORMAL, /* Normal game mode */
    GM_IMMORTAL /* Immortality mode for testing */
};
typedef enum Game_Mode Game_Mode_t;

/* Structure for current game modifiers */
struct Game_Modifiers {
    /* Positive modifiers: */
    u32 lifes_num; /* Additional lives */
    b32 powerup; /* Ball powerup state */
    u32 powerup_num; /* Amount of power up shots */
    u32 multishot_num; /* Amount of Multi-shots */
    /* Negative modifiers: */
    b32 blocks_invis; /* Invisible blocks */
    u32 blocks_invis_num;
    b32 blocks_move; /* Additional blocks move */
};
typedef struct Game_Modifiers Game_Modifiers_t;

/* Structure of the game class */
struct Game
{
    f32 dtime; /* Time delta between the game ticks (in sec) */
    f32 cum_time;  /* Cumulative time of the game (in sec) */
};
typedef struct Game Game_t; 



/* Main entry point to the game logic procedure */
void simulate_game_tick(Input_t *user_input, Render_Buffer_t *render_buffer,
    Sound_buffer_t *sound_buffer);


#endif // GAME_H_
