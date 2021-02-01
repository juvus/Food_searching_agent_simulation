/*
===============================================================================
Main logic loop of the game
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
#include <game.h>
#include <software_rendering.h>
#include <utils.h>
#include <input_treatment.h>
#include <file_io.h>
#include <font.h>
#include <dbg.h>
#include <debug_console.h> /* Graphic console on the game screen */
#include <sound_buffer.h>
#include <sound.h>
#include <wav_uncompressor.h>

/* Game classes */
#include <arena.h>
#include <player.h>
#include <blocks.h>
#include <ball.h>
#include <ball_trail.h>
#include <extra_ball.h>
#include <bonuses.h>
#include <misc.h>
#include <game_constants.h>

/* Loaded images */
static Loaded_img_t font_img; /* Image with font symbols */
static Loaded_img_t ball_img; /* Image of the normal game ball */
static Loaded_img_t ball_powered_img; /* Image of the powered ball */
static Loaded_img_t trail_mask_img; /* Mask of the ball trail */
static Loaded_img_t b_life_img; /* Image of the life bonus */ 
static Loaded_img_t b_power_up_img; /* Image of the power up bonus */
static Loaded_img_t b_multishot_img; /* Image of the multishot bonus */
static Loaded_img_t b_block_invis_img; /* Image of the block invis bonus */
static Loaded_img_t b_block_move_img; /* Image of the block invis bonus */
static Loaded_img_t *bonus_images[5]; /* Array with pointers to all bonus images structures */
static Loaded_img_t heart_img; /* Image of heart to display the ammount of life */

/* Loaded sounds */
enum Sounds_enum {e_snd_empty, e_snd_background, e_snd_bounce, e_snd_block_destroy, e_snd_num};
static Sound_t snd_empty = {0}; /* Empty sound designed for mixing purposes */
static Sound_t snd_background = {0}; /* Sound of the background music */
static Sound_t snd_bounce = {0}; /* Sound of the ball bounce from player platform */
static Sound_t snd_block_destroy = {0}; /* Sound of the block destroy */
static Sound_t *sounds[e_snd_num]; /* Array of pointers to sound structures */

/* Define different parameters for game systems  */
static Game_t game = {0};  /* Game object */
static Sound_Buffer_Worker_Data_t sound_buffer_worker_data = {0};  /* Structure with buffer worker data */
static DConsole_t dconsole; /* Debug console with messages */
static Symbol_data_t *font_symbols; /* Pointer to the array of all font symbols */
static LARGE_INTEGER begin_counter;  /* Union for for dtime calculation */
static LARGE_INTEGER end_counter;  /* Union for for dtime calculation */
static LARGE_INTEGER frequency_counter;  /* Union for for dtime calculation */
static LONGLONG begin; /* Variable for dtime calculation */
static LONGLONG end; /* Variable for dtime calculation */
static LONGLONG frequency; /* Variable for dtime calculation */

/* Define different game variables */
static Arena_t arena; /* Structure of the arena */
static Player_t player; /* Structure with player information */
static Ball_t ball; /* Structure with ball information */
static Ball_t *extra_balls; /* Array with additionals balls for the multishots */
static f32 extra_x_vel; /* additional x velocity when ball hits the player */
static u32 hits_num; /* Number of ball hits with the platform */
static Game_Modifiers_t game_modifiers; /* Structure of the game modifiers */
static Block_t *blocks; /* Pointer to the array of blocks */
static Bonus_t *bonuses; /* Pointer to the array of falling bonuses */
static u32 b_array_tail; /* Index of the tail element of the bonuses array */
static V2_f32_t lowest_block_BL; /* Collision check border for blocks */
static b32 first_ball_movement = true;
static u32 num_destroyed; /* Number of the destroyed blocks */
static b32 flag_win_game; /* Flag showing the the game is won */
static u32 game_state = 1; /* Current game state */
static f32 x, y; /* Temporary coordinates */
static u32 i, j, k; /* Temporary indexes */
static u32 b_num; /* Temporary number of the block */
static b32 need_reverse_vel_x; /* Flag to change the ball velocity x */
static b32 need_reverse_vel_y; /* Flag to change the ball velocity y */
static char collision_side; /* Char determining the collision side (t, r, b, l) */
static Game_Mode_t game_mode; /* game mode */
static u32 game_score; /* Game score */
static Ball_trail_t *ball_trails; /* Pointer to array with ball trails */
static u32 trail_index; /* Index of the current trail in ball_trails array */
static f32 trail_timer; /* Timer for the generating next trail */
static f32 left_wall_shake_timer; /* Timer for the left wall shake procedure */
static f32 left_wall_shake_time; /* Time of sinusoidal shaking of the left wall*/
static b32 left_wall_is_shaking; /* Flag to shake the left wall */
static f32 right_wall_shake_timer; /* Timer for the right wall shake procedure */
static f32 right_wall_shake_time; /* Time of sinusoidal shaking of the right wall*/
static b32 right_wall_is_shaking; /* Flag to shake the right wall */
static f32 top_wall_shake_timer; /* Timer for the right wall shake procedure */
static f32 top_wall_shake_time; /* Time of sinusoidal shaking of the right wall*/
static b32 top_wall_is_shaking; /* Flag to shake the right wall */
static f32 top_wall_shake_timer; /* Timer for the top wall shake procedure */ 


void simulate_game_tick(Input_t *user_input, Render_Buffer_t *render_buffer,
    Sound_buffer_t *sound_buffer)
{
    /* Main function for the game simulation */
  
    f32 dtime_orig = game.dtime;
    
    //game.dtime = 0.001; //for testing

    switch (game_state) {
    case 1: {    
        /*
        ========================================================================
        Loading the different resource data IMAGES
        ========================================================================
        */
                 
        /* Additional life bonus image */
        b_life_img.raw_data = read_file_to_memory("data\\b_life.png");
        uncompress_png_image(&b_life_img);              
        /* Power up bonus image */
        b_power_up_img.raw_data = read_file_to_memory("data\\b_power_up.png");
        uncompress_png_image(&b_power_up_img);
        /* Multishot bonus image */
        b_multishot_img.raw_data = read_file_to_memory("data\\b_multishot.png");
        uncompress_png_image(&b_multishot_img);
        /* Block invis bonus image */
        b_block_invis_img.raw_data = read_file_to_memory("data\\b_block_invis.png");
        uncompress_png_image(&b_block_invis_img);
        /* Block move bonus image */
        b_block_move_img.raw_data = read_file_to_memory("data\\b_block_move.png");
        uncompress_png_image(&b_block_move_img);
             
        /* Pack all the images to an array */
        bonus_images[0] = &b_life_img;
        bonus_images[1] = &b_power_up_img;
        bonus_images[2] = &b_multishot_img;
        bonus_images[3] = &b_block_invis_img;
        bonus_images[4] = &b_block_move_img;

         /* Symbols of the font */
        font_img.raw_data = read_file_to_memory("data\\font.png");
        uncompress_png_image(&font_img);
        /* Heart image */
        heart_img.raw_data = read_file_to_memory("data\\heart.png");
        uncompress_png_image(&heart_img);
        /* Normal ball image */
        ball_img.raw_data = read_file_to_memory("data\\ball.png");
        uncompress_png_image(&ball_img);
        /* Powered ball image */
        ball_powered_img.raw_data = read_file_to_memory("data\\ball_powered.png");
        uncompress_png_image(&ball_powered_img);
        /* Ball trail mask image */
        trail_mask_img.raw_data = read_file_to_memory("data\\trail_mask.png");
        uncompress_png_image(&trail_mask_img);

        /* =========================================================================================== */
        /* Loading the different resource data SOUNDS                                                  */
        /* =========================================================================================== */      

        /* Prepare empty sound */
        strcpy(snd_empty.sound_name, "empty");
        sound_prepare_empty_sound(&snd_empty);
        
        /* Sound of the background music */
        strcpy(snd_background.sound_name, "background");       
        snd_background.raw_data = read_file_to_memory("data\\background.wav");
        uncompress_wav_sound(&snd_background);    

        /* Sound of the ball bounce from player platform */
        strcpy(snd_bounce.sound_name, "bounce");
        snd_bounce.raw_data = read_file_to_memory("data\\bounce.wav");
        uncompress_wav_sound(&snd_bounce);

        /* Sound of the block destroy */
        strcpy(snd_block_destroy.sound_name, "block_destroy");
        snd_block_destroy.raw_data = read_file_to_memory("data\\block_destroy.wav");
        uncompress_wav_sound(&snd_block_destroy);

        /* Form the array of pinters to sounds */
        sounds[e_snd_empty] = &snd_empty;
        sounds[e_snd_background] = &snd_background; 
        sounds[e_snd_bounce] = &snd_bounce;
        sounds[e_snd_block_destroy] = &snd_block_destroy;
        
        /* Preparing the buffer worker data */
        sound_buffer_worker_data.sound_buffer = sound_buffer;
        sound_buffer_worker_data.sounds = sounds;
        sound_buffer_worker_data.e_sound_num = e_snd_num;

        game_state = 2;
        break;
    }
    case 2: {
        /* =========================================================================================== */
        /* Dynamic allocation of different objects                                                     */
        /* =========================================================================================== */

        ball_trails = (Ball_trail_t *) calloc (TRAILS_NUM, sizeof(Ball_trail_t));
        blocks = (Block_t *) calloc ((BLOCK_ROWS * BLOCK_COLS), sizeof(Block_t));
        bonuses = (Bonus_t *) calloc ((BLOCK_ROWS * BLOCK_COLS), sizeof(Bonus_t));
        extra_balls = (Ball_t *) calloc (EXTRA_BALL_NUM, sizeof(Ball_t));
        font_symbols = (Symbol_data_t *) calloc (SYM_ROWS * SYM_COLS, sizeof(Symbol_data_t));       

        game_state = 3;
        break;
    }
    case 3: {
        /* =========================================================================================== */
        /* Game initialization procedure                                                               */
        /* =========================================================================================== */
           
        /* Seed the random numbers */
        srand(time(NULL));      

        /* Prepare the font to use */
        font_extract_symbols(font_symbols, &font_img);
       
        /* Initialization of arena  */
        arena_init(&arena, &heart_img, render_buffer);
	    arena_render_all_margins(&arena, render_buffer);
        
        /* Initialization of player platform */
        player_init(&player, &arena);

        /* Initialization of ball */
	    ball_init(&ball, &arena, &ball_img);
        
        /* Initialization of the array with ball trails */
        ball_trail_init(ball_trails, &trail_timer, &trail_index, &trail_mask_img);

        /* Initialization of the array with extra balls */
        extra_balls_init(extra_balls, &ball_powered_img);

        /* Initialization of blocks */    
        blocks_init(blocks, &arena, &lowest_block_BL);        
        blocks_seed_bonuses(blocks);
	
        /* Initialization of bonuses array*/
	    bonuses_array_init(bonuses, &b_array_tail);
        
        /* Initialization of the debug console */
        dconsole_init(&dconsole, 50, 100, 300);
        
        /* Initialization of some game parameters */
        game_mode = GM_NORMAL; /* Game mode (GM_NORMAL, GM_IMMORTAL) */
        num_destroyed = 0;
        hits_num = 0;
        game_score = 0;
        first_ball_movement = true;
        flag_win_game = false;
        
        /* Initialize the game modifiers */
        game_modifiers.lifes_num = 3;
        game_modifiers.powerup = false;
        game_modifiers.powerup_num = 0;
        game_modifiers.multishot_num = 0;
        game_modifiers.blocks_invis = false;
        game_modifiers.blocks_invis_num = 0;
        game_modifiers.blocks_move = false;

        /* Initial render of game elements: */
        clear_full_screen(BKG_COLOR, render_buffer);
        arena_render_score(&arena, game_score, render_buffer);
        arena_render_lifes(&arena, game_modifiers.lifes_num, render_buffer);       
        blocks_render(blocks, render_buffer);
        
        /* Init wall shake parameters */
        left_wall_shake_timer = 0.0f;
        left_wall_shake_time = 0.0f;
        left_wall_is_shaking = false;
        right_wall_shake_timer = 0.0f;
        right_wall_shake_time = 0.0f;
        right_wall_is_shaking = false;
        top_wall_shake_timer = 0.0f;
        top_wall_shake_time = 0.0f;
        top_wall_is_shaking = false;

        /* Play the sound buffer */
        sound_buffer_clear_buffer(sound_buffer);
        sound_buffer_play(sound_buffer);

        /* Play the background music */
        sound_play_sound_continiously(&snd_empty, S_PAN_BOTH, 1.0f);
        //snd_empty.is_playing = false; //test
        sound_play_sound_continiously(&snd_background, S_PAN_BOTH, 1.0f);
        //snd_background.is_playing = false; //test   
        
        /* Make a separate thread to update the sounds in sound buffer */
        CreateThread(0, 0, sound_buffer_worker_proc, &sound_buffer_worker_data, 0, 0);

        /* Function for the thread of main game loop */
        QueryPerformanceCounter(&begin_counter);
        QueryPerformanceFrequency(&frequency_counter);
        game.dtime = 0.01666f; /* Initial dtime value */
        game.cum_time = 0.0f;  /* Initial cumulative time of the game */

        /* Test drawing of the images */
        //font_draw_string(test_str, -1, 100, 100, 2, 0x000000, font_symbols, render_buffer);
        //draw_bitmap(200, 200, &font_img, 2, render_buffer);
        //draw_bitmap(250, 200, &b_power_up_img, 2, render_buffer);
        //draw_bitmap(300, 200, &b_multishot_img, 2, render_buffer);
        //draw_bitmap(350, 200, &b_block_invis_img, 2, render_buffer);
        //draw_bitmap(400, 200, &b_block_move_img, 2, render_buffer);
        //draw_bitmap(200, 200, &heart_img, 3, render_buffer);

        /* Jump to the next game stage */
	    game_state = 4;
        break;
    }       
    case 4: {
        /* =========================================================================================== */
        /* Game run logic procedure                                                                        */
        /* =========================================================================================== */

        /* Test of the debug console */
        sconsole_clear_messages(&dconsole);
        dconsole_clear_console(&dconsole, render_buffer);
        sprintf(dconsole.str_buffer, "%s%5.3lf", "dtime: ", dtime_orig);
        dconsole_add_message(&dconsole, dconsole.str_buffer, 0xff0000);
        sprintf(dconsole.str_buffer, "%s%5.3lf", "FPS: ", (1.0f / dtime_orig));
        dconsole_add_message(&dconsole, dconsole.str_buffer, 0xff0000);
        dconsole_render(&dconsole, font_symbols, render_buffer);
        
        /* Calculate the player new position */
        player_hide(&player, render_buffer);
        player_get_velocity(&player, user_input->mouse.x, game.dtime);
        player_set_position(&player, user_input->mouse.x, player.BL.y);
        player_apply_squeeze(&player);
        player_render(&player, render_buffer);

        /* Render the arena margins (taking into account the shaking)*/
        arena_hide_left_margin(&arena, render_buffer);
        arena_hide_right_margin(&arena, render_buffer);
        arena_hide_top_margin(&arena, render_buffer);
        
        if (left_wall_is_shaking) {
            arena_shake_left_margin(&arena, &left_wall_is_shaking, &left_wall_shake_timer,
                &left_wall_shake_time, game.dtime);
        }
        if (right_wall_is_shaking) {
            arena_shake_right_margin(&arena, &right_wall_is_shaking, &right_wall_shake_timer,
                &right_wall_shake_time, game.dtime, render_buffer);
        }
        if (top_wall_is_shaking) {
            arena_shake_top_margin(&arena, &top_wall_is_shaking, &top_wall_shake_timer,
                &top_wall_shake_time, game.dtime, render_buffer);
        }
        arena_render_all_margins(&arena, render_buffer);
        
	    /* Hide the previous position of the wall */
        ball_hide(&ball, render_buffer);

        /* Animate the destroy of necessary blocks */
        blocks_animate_destroy(blocks, game.dtime, BKG_COLOR, render_buffer);
              
        /* Calculate the new position of the ball */
        x = ball.BL.x + ball.velocity.x * game.dtime;
	    y = ball.BL.y + ball.velocity.y * game.dtime;

	    /* Check the collision of the ball with platform */
	    if (ball_is_collision_vs_platform(&ball, &player, &collision_side)) {
	        ball_reverse_velocity(&ball, "y");
            /* Time solution - teleport ball to top of player, when collide with side */
	        /* Change the x component of the ball velocity due to the velocity of the player */
            y = player.BL.y + player.height; 
            extra_x_vel = ball_calc_extra_x_vel(x, &ball, &player);
            ball_set_velocity(&ball, "x", (ball.velocity.x + extra_x_vel + player.velocity * 0.3));
            first_ball_movement = false;
            hits_num += 1;
            blocks_shift(blocks, hits_num, &lowest_block_BL, render_buffer);
            /* Reduce the amount of game_score */
            if (game_score > 0) {
                game_score--;
                arena_render_score(&arena, game_score, render_buffer);
            }  

            /* Play the bounce sound */
            sound_play_sound_once(&snd_bounce, S_PAN_BOTH, 1.0f);
	    }
        
        /* Check the collision of the ball with LEFT wall */
        if (x <= arena.BL.x) {
            ball_reverse_velocity(&ball, "x");
            x = arena.BL.x;
            left_wall_is_shaking = true;
            left_wall_shake_timer = WALL_SHAKE_TIME;
            left_wall_shake_time = 0.0f;
        }

        /* Check the collision of the ball with RIGHT wall */
        if ((x + ball.width) >= arena.UR.x) {
            ball_reverse_velocity(&ball, "x");
            x = arena.UR.x - ball.width;
            right_wall_is_shaking = true;
            right_wall_shake_timer = WALL_SHAKE_TIME;
            right_wall_shake_time = 0.0f;
        }

        /* Check the collision of the ball with UP wall */
        if ((y + ball.height) >= arena.UR.y) {
            ball_reverse_velocity(&ball, "y");
            y = arena.UR.y - ball.height;
                top_wall_is_shaking = true;
                top_wall_shake_timer = WALL_SHAKE_TIME;
                top_wall_shake_time = 0.0f;
        }

        /* Check the collision of the ball with BOTTOM wall */
        if (y <= arena.BL.y) {
            if (game_mode == GM_IMMORTAL) {
            ball_reverse_velocity(&ball, "y");
            y = arena.BL.y;
            }
            if (game_mode == GM_NORMAL) {
                if (game_modifiers.lifes_num > 0) {
                    ball_reverse_velocity(&ball, "y");
                    y = arena.BL.y;
                    game_modifiers.lifes_num -= 1;
                    if (game_modifiers.lifes_num == 0) {
                        game_state = 5; /* Go to game over */
                    }
                    arena_render_lifes(&arena, game_modifiers.lifes_num, render_buffer);
                    first_ball_movement = false;
                }
            }
        }

        /* Hide bonuses and update their positions*/
        bonuses_hide_all(bonuses, &b_array_tail, render_buffer);
	    bonuses_update_positions(bonuses, game.dtime, &b_array_tail);

        /* While first_ball_movement, render blocks every frame */
        /* While bonus in upper then lowes_block_BL.y, render blocks every frame */
        if ((first_ball_movement) ||
            (bonuses_is_higher_lowest_block(bonuses, &b_array_tail, &lowest_block_BL))) {
            blocks_render(blocks, render_buffer);
        }

        /* Render the bonuses */
        bonuses_render(bonuses, &b_array_tail, render_buffer);
        
        /* Procedure for the colision of the normal ball with the blocks */
        need_reverse_vel_x = false;
        need_reverse_vel_y = false;
        if ((ball.UR.y >= lowest_block_BL.y) && !(first_ball_movement))  {
            /* Check the collision of the ball with the blocks */
            b_num = 0;
            for (i = 0; i < BLOCK_ROWS; i++) {
            for (j = 0; j < BLOCK_COLS; j++) {
                /* If there is no block then continue */
                if (blocks[b_num].is_exist == true) {
                /* Check the collision of the ball with BOTTOM part of the block */
                if(ball_is_collision_vs_block(&ball, &blocks[b_num], &collision_side) == true) {
                                
                    /* Collision happened with the bottom side of the block */
                    if (collision_side == 'b') {
                                    need_reverse_vel_y = true;                                                               
                    } /* if */

                    /* Collision happened with the top side of the block */
                    if (collision_side == 't') {
                                    need_reverse_vel_y = true;                              
                    } /* if */

                    /* Collision happened with the left side of the block */
                    if (collision_side == 'l') {
                                    need_reverse_vel_x = true;
                    } /* if */

                    /* Collision happened with the right side of the block */
                    if (collision_side == 'r') {
                                    need_reverse_vel_x = true;
                    } /* if */

                    blocks[b_num].is_exist = false;
                    blocks[b_num].is_destroying = true;
                    blocks_destroy_one(blocks, &ball, b_num, render_buffer);
                    bonuses_try_to_spawn(bonuses, &b_array_tail, blocks, b_num, bonus_images);
                    num_destroyed += 1;                         
                    game_score++;
                    arena_render_score(&arena, game_score, render_buffer);

                    /* Play block destroy sound */
                    sound_play_sound_once(&snd_block_destroy, S_PAN_BOTH, 1.0f);

                } /* if */
                } /* if */
                b_num++; /* Check the next block */
            }  /* for j */
            } /* for i */
        } /* if */

        /* Apply the powerup game modifier for the shot */
        if (ball_is_collision_vs_platform(&ball, &player, &collision_side)) {
            //sound_buffer_play(sound_buffer, &sound_1);
                            
            if (game_modifiers.powerup_num > 0) {
                game_modifiers.powerup = true;
                ball.image = &ball_powered_img; /* Red image of the ball */
                game_modifiers.powerup_num -= 1;
            }
            else {
                game_modifiers.powerup = false;
                ball.image = &ball_img; /* Normal image of the ball */
            }
        }
        if (game_modifiers.powerup) {
            need_reverse_vel_y = false;
	    need_reverse_vel_x = false;
            /* Try to spawn a new ball trail */
            ball_trail_spawn_one(ball_trails, &ball, game.dtime, &trail_timer, &trail_index);
        }
        /* Render the trails and then decay */
        ball_trail_render(ball_trails, &ball, render_buffer);
        ball_trail_decay(ball_trails, &ball, game.dtime);

        /* Apply the extra balls game modifier for the shot */
        if (ball_is_collision_vs_platform(&ball, &player, &collision_side)) {
            if (game_modifiers.multishot_num > 0) {
                extra_balls_spawn_3_balls(extra_balls, &ball, &player);
                game_modifiers.multishot_num -= 1;
            }
        }

        /* Apply the blocks hide game modifier for the invisibility mode */
        if (ball_is_collision_vs_platform(&ball, &player, &collision_side)) {
            if (game_modifiers.blocks_invis_num > 0) {
                game_modifiers.blocks_invis = true;
                game_modifiers.blocks_invis_num -= 1;
            }
            else {
                game_modifiers.blocks_invis = false;
            }
        }
        if (game_modifiers.blocks_invis) {
            blocks_hide(blocks, render_buffer);
        }

        /* Apply the blocks move game modifier */
        if (game_modifiers.blocks_move) {
            if (!blocks_is_destroying(blocks)) {
                hits_num = HITS_TO_SHIFT;
                blocks_shift(blocks, hits_num, &lowest_block_BL, render_buffer);
                game_modifiers.blocks_move = false;
            }
        }
        
	/* Apply the change in ball velocity */
	if (need_reverse_vel_y) {
	    ball_reverse_velocity(&ball, "y");
	}
	if (need_reverse_vel_x) {
	    ball_reverse_velocity(&ball, "x");
	}

	/* Update the ball position and redraw the ball */
	ball_set_position(&ball, x, y);
        ball_render(&ball, render_buffer);

        /* Calculate the extra_balls new positions and redraw them*/
        extra_balls_hide(extra_balls, render_buffer);
        for (i = 0; i < EXTRA_BALL_NUM; ++i) {
            if (extra_balls[i].is_exist) {
                x = extra_balls[i].BL.x + extra_balls[i].velocity.x * game.dtime;
                y = extra_balls[i].BL.y + extra_balls[i].velocity.y * game.dtime;

                /* Check the collision of the extra balls with LEFT wall */
                if (x <= arena.BL.x) {
                    ball_reverse_velocity(&extra_balls[i], "x");
                    x = arena.BL.x;
                    left_wall_is_shaking = true;
                    left_wall_shake_timer = WALL_SHAKE_TIME;
                    left_wall_shake_time = 0.0f;
                }

                /* Check the collision of the ball with RIGHT wall */
                if ((x + extra_balls[i].width) >= arena.UR.x) {
                    ball_reverse_velocity(&extra_balls[i], "x");
                    x = arena.UR.x - extra_balls[i].width;
                    right_wall_is_shaking = true;
                    right_wall_shake_timer = WALL_SHAKE_TIME;
                    right_wall_shake_time = 0.0f;
                }

                /* Check the collision of the ball with UP wall */
                if ((y + extra_balls[i].height) >= arena.UR.y) {
                    extra_ball_delete(extra_balls, i);
                    top_wall_is_shaking = true;
                    top_wall_shake_timer = WALL_SHAKE_TIME;
                    top_wall_shake_time = 0.0f;
                }

                /* Check the collision of extra balls with blocks */
                if (extra_balls[i].UR.y >= lowest_block_BL.y) {
                    b_num = 0;
                    for (j = 0; j < BLOCK_ROWS; j++) {
                        for (k = 0; k < BLOCK_COLS; k++) {
                            if (blocks[b_num].is_exist == true) {
                                if(ball_is_collision_vs_block(&extra_balls[i], &blocks[b_num],
                                    &collision_side) == true)
                                {
                                    /* Destroy the block */
                                    blocks[b_num].is_exist = false;
                                    blocks[b_num].is_destroying = true;

                                    blocks_destroy_one(blocks, &ball, b_num, render_buffer);
                                    bonuses_try_to_spawn(bonuses, &b_array_tail, blocks, b_num, bonus_images);
                                    num_destroyed += 1;

                                    /* Increase the score */
                                    game_score++;
                                    arena_render_score(&arena, game_score, render_buffer);

                                    /* Destroy the extra ball */
                                    extra_ball_delete(extra_balls, i);

                                    /* Play block destroy sound */
                                    sound_play_sound_once(&snd_block_destroy, S_PAN_BOTH, 1.0f);
                                }                                
                            }
                            b_num++; /* Check the next block */
                        } /* for k */
                    } /* for j */
                } /* if */
             
                /* Set the position of extra ball */
                ball_set_position(&extra_balls[i], x, y);
            }
        }
        extra_balls_render(extra_balls, render_buffer);

	/* Check the bonuses to reach the bottom or collide with the platform */
	for (i = 0; i <= b_array_tail; ++i) {
	    if (bonus_is_reached_bottom(&bonuses[i], &arena)) {
		bonuses_delete_bonus(bonuses, i, &b_array_tail);
		bonuses_hide_one(bonuses, i, render_buffer);
	    }
	}

	/* Check the bonuses to collide with the player platform and apply them */
        for (i = 0; i <= b_array_tail; ++i) {
            if (bonus_is_collision_vs_platform(&bonuses[i], &player)) {
		        bonus_apply_bonus(&bonuses[i], &game_modifiers);
                arena_render_lifes(&arena, game_modifiers.lifes_num, render_buffer);
		        bonuses_delete_bonus(bonuses, i, &b_array_tail);
		        bonuses_hide_one(bonuses, i, render_buffer);
	        }
	    }

	/* Check the flag to win the game */
        if (num_destroyed == (BLOCK_ROWS * BLOCK_COLS)) {
            game_state = 6; /* The game was won */
            flag_win_game = true;
        } 
    
	/* Increase the game difficulty */
        if (ball.velocity.y >= 0) {
	        ball_set_velocity(&ball, "y", ball.speed_limit);
	    } else {
	        ball_set_velocity(&ball, "y", -ball.speed_limit);
	    }

        
        /* Calculate the delta time */
        QueryPerformanceCounter(&end_counter);
        begin = begin_counter.QuadPart;
        end = end_counter.QuadPart;
        frequency = frequency_counter.QuadPart;
        game.dtime = (f32)((end - begin) / (f32)frequency);
        /* Save guard to dtime (if the window is hold, so there is no large value for dtime) */
        game.dtime = (game.dtime > 0.01666f)? 0.01666f : game.dtime;
        game.cum_time += game.dtime;
        begin_counter = end_counter;

        break;
    } 

    case 5: { /* Game over */
	printf("Game over\n");
	game_state = 3;
        break;
    } 
        
    case 6: { /* Game won */
	printf("Congratulations!\n");
	game_state = 3;
        break;
    }}

    /* Render the debug messages */
    //render_messages(messages, render_buffer);
}
