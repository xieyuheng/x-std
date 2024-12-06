#pragma once

extern color_t blending_table[16][4];

// blending naming:
//     <BG_COLOR>_<AP_COLOR><VARIANT>

typedef enum {
    TR_FG,
    BG_AP,
    BG_SL,
    BG_FG2,

    SL_FG,
    TR_AP,
    SL_SL,
    SL_FG2,

    FG_FG,
    FG_AP,
    TR_SL,
    FG_FG2,

    AP_FG,
    AP_AP,
    AP_SL,
    TR_FG2,
} blending_t;

bool blending_is_transparent(blending_t blending);
