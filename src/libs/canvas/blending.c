#include "index.h"

color_t blending_table[16][4] = {
    { 0, 0, 1, 2 }, // bg bg sl fg tr
    { 0, 1, 2, 3 }, // bg sl fg ap
    { 0, 2, 3, 1 }, // bg fg ap sl
    { 0, 3, 1, 2 }, // bg ap sl fg
    { 1, 0, 1, 2 }, // sl bg sl fg
    { 0, 1, 2, 3 }, // bg sl fg ap tr
    { 1, 2, 3, 1 }, // sl fg ap sl
    { 1, 3, 1, 2 }, // sl ap sl fg
    { 2, 0, 1, 2 }, // fg bg sl fg
    { 2, 1, 2, 3 }, // fg sl fg ap
    { 0, 2, 3, 1 }, // bg fg ap sl tr
    { 2, 3, 1, 2 }, // fg ap sl fg
    { 3, 0, 1, 2 }, // ap bg sl fg
    { 3, 1, 2, 3 }, // ap sl fg ap
    { 3, 2, 3, 1 }, // ap fg ap sl
    { 0, 3, 1, 2 }, // bg ap sl fg tr
};

bool
blending_is_transparent(blending_t blending) {
    return
        (blending == 0x0) ||
        (blending == 0x5) ||
        (blending == 0xa) ||
        (blending == 0xf);
}
