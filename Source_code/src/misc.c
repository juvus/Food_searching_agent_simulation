/*================================================================================*/
/* Realization of misc functions                                                  */
/*================================================================================*/

#define _USE_MATH_DEFINES
#include <misc.h>
#include <utils.h>
#include <stdlib.h>
#include <math.h>

f32
trim(f32 value, f32 low_bnd, f32 hight_bnd)
{
    /* Trim the value to the low and hight bound */
    if (value < low_bnd) {
        return low_bnd;
    }
    if (value > hight_bnd) {
        return hight_bnd;
    }
    return value;
}

u32
rnd_int_range(u32 left_bnd, u32 right_bnd)
{
    /* Function for generation random u32 number from the specific range */
    return (left_bnd + (rand() % (right_bnd - left_bnd)));
}

f32
rnd_f32(void)
{
    /* Function to generate the random number in range [0.0, 1.0) */
    f32 result;
    result = (f32)((rand() % 32767) / (f32)32767);
    return result;
}

f32
rnd_f32_range(f32 left_bnd, f32 right_bnd)
{
    /* Function for generation random f32 number from specific range */
    f32 result;
    result = left_bnd + rnd_f32() * (right_bnd - left_bnd);
    return result;
}

b32
check_collision(V2_f32_t *BL_mv, V2_f32_t *UR_mv, V2_f32_t *BL_st, V2_f32_t *UR_st, char *collision_side)
{
    /* Universal function to check the fact of the collision of obj_mv (moving) with
       obj_st (static) and determining the collision side (r, b, l, t of the static object). */

    /* Calculation the objects widths and heights */
    f32 width_mv = UR_mv->x - BL_mv->x;
    f32 height_mv = UR_mv->y - BL_mv->y;
    f32 width_st = UR_st->x - BL_st->x;
    f32 height_st = UR_st->y - BL_st->y;

    /* Additional parameters */
    b32 is_collision = false;
    f32 xc_mv, yc_mv; /* Coordinates of the center of the moving object */
    f32 xc_st, yc_st; /* Coordinates of the center of the static object */
    f32 alpha; /* Angle between block center and ball center */
    f32 UR_angle; /* Critical up-right angle (with respect to static object)*/
    f32 DR_angle; /* Critical down-right angle (with respect to static object)*/
    f32 UL_angle; /* Critical up-left angle (with respect to static object)*/
    f32 DL_angle; /* Critical down-left angle (with respect to static object)*/

    /* Check the fact of the collision */
    if ((BL_mv->x > (BL_st->x - width_mv)) &&
        (UR_mv->x < (UR_st->x + width_mv)) &&
        (BL_mv->y > (BL_st->y - height_mv)) &&
        (UR_mv->y < (UR_st->y + height_mv))) {
        is_collision = true;
        }

    if (is_collision) {
        /* Calculate the centers coordinates */
        xc_st = BL_st->x + (width_st / 2.0f);
        yc_st = BL_st->y + (height_st / 2.0f);

        xc_mv = BL_mv->x + (width_mv / 2.0f);
        yc_mv = BL_mv->y + (height_mv / 2.0f);

        /* Check the angle and side of the collision */
        alpha = atanf((yc_mv - yc_st) / (xc_mv - xc_st));

        if (alpha > 0) {
            if (xc_mv < xc_st) {
                alpha = alpha + M_PI;
            }
        } else {
            if (xc_mv > xc_st) {
                alpha = alpha + 2.0f * M_PI;
            } else {
                alpha = alpha + M_PI;
            }
        }

        /* Calculate the critical values of angles */
        UR_angle = atanf((height_st + height_mv) / (width_st + width_mv));
        DR_angle = 2 * M_PI - UR_angle;
        UL_angle = M_PI - UR_angle;
        DL_angle = UR_angle + M_PI;

        /* alpha >= DR_angle and alpha < UR_angle */
        if (alpha >= DR_angle) {
            *collision_side = 'r';
        }
        if (alpha < UR_angle) {
            *collision_side = 'r';
        }

        /* alpha >= UR_angle and alpha < UL_angle */
        if ((alpha >= UR_angle) && (alpha < UL_angle)) {
            *collision_side = 't';
        }

        /* alpha >= UL_angle and alpha < DL_angle */
        if ((alpha >= UL_angle) && (alpha < DL_angle)) {
            *collision_side = 'l';
        }

        /* alpha >= DL_angle and alpha < DR_angle */
        if ((alpha >= DL_angle) && (alpha < DR_angle)) {
            *collision_side = 'b';
        }
    }
    return is_collision;
}

