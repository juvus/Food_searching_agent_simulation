/*================================================================================*/
/* Header file for the misc functions class.                                      */
/*================================================================================*/

#ifndef MISC_H_
#define MISC_H_

#include <utils.h>
#include <stdlib.h>
#include <file_io.h>

/* Trim the value to the low and hight bound */
f32 trim(f32 value, f32 low_bnd, f32 hight_bnd);

/* Function for generation random u32 number from the specific range */
u32 rnd_int_range(u32 left_bnd, u32 right_bnd);

/* Function to generate the random number in range [0.0, 1.0) */
f32 rnd_f32(void);

/* Function for generation random f32 number from specific range */
f32 rnd_f32_range(f32 left_bnd, f32 right_bnd);

/* Universal function to check the fact of the collision of obj_mv (moving) with
   obj_st (static) and determining the collision side (r, b, l, t of the static object). */
b32 check_collision(V2_f32_t *BL_mv, V2_f32_t *UR_mv, V2_f32_t *BL_st, V2_f32_t *UR_st,
                    char *collision_side);

#endif //MISC_H_
