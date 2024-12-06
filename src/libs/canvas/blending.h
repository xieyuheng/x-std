#pragma once

extern uint8_t blending_table[16][4];

typedef enum {
    BG_BG_SL_FG_TR,
    BG_SL_FG_AP,
    BG_FG_AP_SL,
    BG_AP_SL_FG,
    SL_BG_SL_FG,
    BG_SL_FG_AP_TR,
    SL_FG_AP_SL,
    SL_AP_SL_FG,
    FG_BG_SL_FG,
    FG_SL_FG_AP,
    BG_FG_AP_SL_TR,
    FG_AP_SL_FG,
    AP_BG_SL_FG,
    AP_SL_FG_AP,
    AP_FG_AP_SL,
    BG_AP_SL_FG_TR,
} blending_t;

bool blending_is_transparent(uint8_t blending);
