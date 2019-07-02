/**
 * @file lv_math.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_math.h"
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static int16_t sin0_90_table[] = {
    0,     572,    1144,   1715,   2286,   2856,   3425,   3993,   4560,   5126,
    5690,  6252,   6813,   7371,   7927,   8481,   9032,   9580,   10126,  10668,
    11207, 11743,  12275,  12803,  13328,  13848,  14364,  14876,  15383,  15886,
    16383, 16876,  17364,  17846,  18323,  18794,  19260,  19720,  20173,  20621,
    21062, 21497,  21925,  22347,  22762,  23170,  23571,  23964,  24351,  24730,
    25101, 25465,  25821,  26169,  26509,  26841,  27165,  27481,  27788,  28087,
    28377, 28659,  28932,  29196,  29451,  29697,  29934,  30162,  30381,  30591,
    30791, 30982,  31163,  31335,  31498,  31650,  31794,  31927,  32051,  32165,
    32269, 32364,  32448,  32523,  32587,  32642,  32687,  32722,  32747,  32762,
	32767
};


/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Convert a number to string
 * @param num a number
 * @param buf pointer to a `char` buffer. The result will be stored here (max 10 elements)
 * @return same as `buf` (just for convenience)
 */
char * lv_math_num_to_str(int32_t num, char * buf)
{
    char * buf_ori = buf;
    if(num == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    } else if(num < 0) {
        (*buf) = '-';
        buf++;
        num = LV_MATH_ABS(num);
    }
    uint32_t output = 0;
    int8_t i;

    for(i = 31; i >= 0; i--) {
        if((output & 0xF) >= 5)
            output += 3;
        if(((output & 0xF0) >> 4) >= 5)
            output += (3 << 4);
        if(((output & 0xF00) >> 8) >= 5)
            output += (3 << 8);
        if(((output & 0xF000) >> 12) >= 5)
            output += (3 << 12);
        if(((output & 0xF0000) >> 16) >= 5)
            output += (3 << 16);
        if(((output & 0xF00000) >> 20) >= 5)
            output += (3 << 20);
        if(((output & 0xF000000) >> 24) >= 5)
            output += (3 << 24);
        if(((output & 0xF0000000) >> 28) >= 5)
            output += (3 << 28);
        output = (output << 1) | ((num >> i) & 1);
    }

    uint8_t digit;
    bool leading_zero_ready = false;
    for(i = 28; i >= 0; i -= 4) {
        digit = ((output >> i) & 0xF) + '0';
        if(digit == '0' && leading_zero_ready == false) continue;

        leading_zero_ready = true;
        (*buf) = digit;
        buf++;
    }

    (*buf) = '\0';

    return buf_ori;
}

/**
 * Return with sinus of an angle
 * @param angle
 * @return sinus of 'angle'. sin(-90) = -32767, sin(90) = 32767
 */
int16_t lv_trigo_sin(int16_t angle)
{
    int16_t ret = 0;
    angle = angle % 360;

    if(angle < 0) angle = 360 + angle;

    if(angle < 90) {
        ret = sin0_90_table[angle];
    } else if(angle >= 90 && angle < 180) {
        angle = 180 - angle;
        ret = sin0_90_table[angle];
    } else if(angle >= 180 && angle < 270) {
        angle = angle - 180;
        ret = - sin0_90_table[angle];
    } else { /*angle >=270*/
        angle = 360 - angle;
        ret = - sin0_90_table[angle];
    }

    return ret;
}

/**
 * Calculate a value of a Cubic Bezier function.
 * @param t time in range of [0..LV_BEZIER_VAL_MAX]
 * @param u0 start values in range of [0..LV_BEZIER_VAL_MAX]
 * @param u1 control value 1 values in range of [0..LV_BEZIER_VAL_MAX]
 * @param u2 control value 2 in range of [0..LV_BEZIER_VAL_MAX]
 * @param u3 end values in range of [0..LV_BEZIER_VAL_MAX]
 * @return the value calculated from the given parameters in range of [0..LV_BEZIER_VAL_MAX]
 */
int32_t lv_bezier3(uint32_t t, int32_t u0, int32_t u1, int32_t u2, int32_t u3)
{
    uint32_t t_rem = 1024 - t;
    uint32_t t_rem2 = (t_rem * t_rem) >> 10;
    uint32_t t_rem3 = (t_rem2 * t_rem) >> 10;
    uint32_t t2 = (t * t) >> 10;
    uint32_t t3 = (t2 * t) >> 10;


    uint32_t v1 = ((uint32_t)t_rem3 * u0) >> 10;
    uint32_t v2 = ((uint32_t)3 * t_rem2 * t * u1) >> 20;
    uint32_t v3 = ((uint32_t)3 * t_rem * t2 * u2) >> 20;
    uint32_t v4 = ((uint32_t)t3 * u3) >> 10;

    return v1 + v2 + v3 + v4;

}

/**********************
 *   STATIC FUNCTIONS
 **********************/


