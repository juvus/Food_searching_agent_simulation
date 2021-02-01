/*================================================================================*/
/* Header file for the different game constants.                                  */
/*================================================================================*/
#ifndef GAME_CONSTANTS_H_
#define GAME_CONSTANTS_H_

#include <utils.h>

/* Colors */
const u32 BKG_COLOR = 0xadcfff;
const u32 MARGINS_COLOR = 0x262e85;
const u32 PLT_COLOR = 0xffffff;
#define LIFES_COLOR 0xff0000
const u32 SCORE_COLOR = 0x262e85;

u32 BLOCKS_COL[5] = {0x6daf43, 0x4870c8, 0xea8036, 0xfdc003, 0xfb34cd};
u32 BLOCKS_DARK_COL[5] = {0x548235, 0x305496, 0xc65911, 0xbf8f00, 0xcc0097};
u32 BONUSES_COL[5] = {0x385624, 0x203763, 0x833d0c, 0xbf8f00, 0xac00ac};

/* Define the game initial constants */
const u32 BLOCK_ROWS = 4; /* total amount of blocks rows */
const u32 BLOCK_COLS =  32; /* total amount of blocks columns (should be even!)*/
const u32 EXTRA_BALL_NUM = 9; /* Number of possible extra balls (expected 3 or 6 at a time) */
const u32 TRAILS_NUM = 30; /* Amount of the trail balls*/
const f32 BALL_INIT_X_VEL = 0.0f; /* Initial ball x velocity (horizontal) */
const f32 BALL_INIT_Y_VEL = -200.0f; /* Initial ball y velocity (vertical) */
const f32 INIT_SPEED_LIMIT = 200.0f; /* Initial ball speed limit */
const f32 BONUS_CHANCE = 0.05f; /* Chance of the bonus to apear in a block */
const f32 BONUS_Y_VEL_MIN = -70.0f; /* Minimum bonus vertical velocity */
const f32 BONUS_Y_VEL_MAX = -130.0f; /* Maximum bonus vertical velocity */
const f32 BONUS_AMPLITUDE_MIN = -30.0f; /* Minimum amplitude of the falling bonus */
const f32 BONUS_AMPLITUDE_MAX = 30.f; /* Maximum amplitude of the falling bonus */
const f32 BONUS_FREQ_MLTP_MIN = 0.0f; /* Minimum frequency multiplier */
const f32 BONUS_FREQ_MLTP_MAX = 0.5f; /* Maximum frequence multiplier */
const f32 PLAYER_WIDTH = 150.0f; /* Width of the player (platform) */
const f32 PLAYER_HEIGHT = 20.0f; /* Height of the player (platform) */
const f32 PLAYER_DIST = 40.0f; /* Player distance from the bottom */
const f32 BALL_WIDTH = 10.0f; /* Ball width */
const f32 BALL_HEIGHT = 10.0f; /* Ball height */
const f32 BLOCK_WIDTH = 20.0f; /* Single block width */
const f32 BLOCK_HEIGHT = 20.0f; /* Single block height */
const f32 BLOCK_DESTROY_TIME = 0.5f; /* Time for the destroy animation */
const u32 HITS_TO_SHIFT = 10; /* How many hits to shift towards the player */
const f32 SHIFT_SPEED = 20.0f; /* Blocks shift speed towards the player */
const f32 ARENA_TOP = 20.0f; /* top margin */
const f32 ARENA_RIGHT = 20.0f; /* top margin */
const f32 ARENA_BOTTOM = 40.0f; /* top margin */
const f32 ARENA_LEFT = 20.0f; /* top margin */
const f32 BALL_TRAIL_LENGTH = 200.0f; /* The total leng of the ball trail */
const f32 WALL_SHAKE_AMPLITUDE = 3.0f; /* Amplitude of the wall shake */
const f32 WALL_SHAKE_TIME = 1.0f; /* Time of the wall shaking time after colision with the ball */
const u32 SYM_ROWS = 6; /* Amount of symbol rows in font.png */
const u32 SYM_COLS = 20; /* Amount of sumbol columns in font.png */
const u32 DCONSOLE_MESSAGES = 10; /* Amount of the debuf messages in debug console */
const u32 DCONSOLE_BKG_COLOR = 0xffffff; /* Background color of the debug console */
const u32 DCONSOLE_BRD_COLOR = 0xb4b4b4; /* Console boarders color */
const u32 DCONSOLE_MARGINS = 10; /* Top, left, bottom and right margins */
const u32 DCONSOLE_MAX_MSG_LENGTH = 100; /* Maximum message length */






#endif //GANE_CONSTANTS_H_
