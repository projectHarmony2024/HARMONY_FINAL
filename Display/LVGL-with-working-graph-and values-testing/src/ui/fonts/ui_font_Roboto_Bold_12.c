/*******************************************************************************
 * Size: 12 px
 * Bpp: 4
 * Opts: --bpp 4 --size 12 --font C:/Users/Raizen/Documents/SquareLine/assets/Roboto-Bold.ttf -o C:/Users/Raizen/Documents/SquareLine/assets\ui_font_Roboto_Bold_12.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_ROBOTO_BOLD_12
#define UI_FONT_ROBOTO_BOLD_12 1
#endif

#if UI_FONT_ROBOTO_BOLD_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x3f, 0x83, 0xf8, 0x2f, 0x72, 0xf7, 0x1f, 0x61,
    0xf6, 0x6, 0x21, 0xe6, 0x1e, 0x60,

    /* U+0022 "\"" */
    0xa8, 0xb7, 0xa8, 0xb6, 0xa6, 0xb5, 0x52, 0x52,

    /* U+0023 "#" */
    0x0, 0x5b, 0x1f, 0x0, 0x8, 0x85, 0xb0, 0x3f,
    0xff, 0xff, 0xe0, 0x1e, 0x4b, 0x71, 0x0, 0xf0,
    0xd3, 0x9, 0xff, 0xff, 0xf7, 0x17, 0xc4, 0xe2,
    0x10, 0x89, 0x4c, 0x0, 0xa, 0x67, 0xa0, 0x0,

    /* U+0024 "$" */
    0x0, 0xd, 0x10, 0x0, 0x7, 0xe8, 0x10, 0xb,
    0xfd, 0xfc, 0x1, 0xfb, 0x8, 0xf3, 0xf, 0xc0,
    0x15, 0x10, 0x9f, 0xd5, 0x0, 0x0, 0x6d, 0xfa,
    0x1, 0x40, 0xa, 0xf3, 0x5f, 0x60, 0x7f, 0x40,
    0xef, 0xbf, 0xe0, 0x2, 0x9f, 0x92, 0x0, 0x0,
    0xe0, 0x0,

    /* U+0025 "%" */
    0xb, 0xf9, 0x0, 0x0, 0x6, 0xd2, 0xf3, 0x3a,
    0x0, 0x6c, 0xf, 0x3d, 0x40, 0x1, 0xdf, 0xb7,
    0xa0, 0x0, 0x0, 0x11, 0xe1, 0x0, 0x0, 0x0,
    0xb7, 0xae, 0xa0, 0x0, 0x4c, 0x4e, 0x3e, 0x40,
    0xd, 0x34, 0xd2, 0xe4, 0x0, 0x10, 0xb, 0xfb,
    0x0,

    /* U+0026 "&" */
    0x2, 0xcf, 0xb1, 0x0, 0xb, 0xf9, 0xf8, 0x0,
    0xc, 0xc0, 0xd8, 0x0, 0x6, 0xfd, 0xd1, 0x0,
    0x7, 0xff, 0x32, 0x81, 0x4f, 0x8e, 0xe7, 0xf1,
    0x8f, 0x23, 0xff, 0xd0, 0x5f, 0xb6, 0xdf, 0xa0,
    0x7, 0xef, 0xcb, 0xf5,

    /* U+0027 "'" */
    0xa9, 0xa9, 0xa8, 0x53,

    /* U+0028 "(" */
    0x0, 0x0, 0x0, 0x5d, 0x1, 0xf5, 0x9, 0xc0,
    0xe, 0x70, 0x1f, 0x40, 0x3f, 0x30, 0x4f, 0x20,
    0x3f, 0x30, 0xf, 0x50, 0xc, 0x90, 0x6, 0xe0,
    0x0, 0xc9, 0x0, 0x19,

    /* U+0029 ")" */
    0x10, 0x0, 0xa8, 0x0, 0x2f, 0x40, 0x9, 0xc0,
    0x4, 0xf2, 0x1, 0xf6, 0x0, 0xf8, 0x0, 0xf8,
    0x0, 0xf7, 0x2, 0xf5, 0x6, 0xf1, 0xc, 0xa0,
    0x6e, 0x10, 0x73, 0x0,

    /* U+002A "*" */
    0x0, 0xc5, 0x0, 0x42, 0xb4, 0x40, 0x8f, 0xfe,
    0xe3, 0x4, 0xfc, 0x0, 0x1e, 0x4d, 0x60, 0x4,
    0x3, 0x20,

    /* U+002B "+" */
    0x0, 0x6c, 0x0, 0x0, 0x8, 0xf1, 0x0, 0x0,
    0x8f, 0x10, 0xa, 0xff, 0xff, 0xf3, 0x7a, 0xdf,
    0xba, 0x20, 0x8, 0xf1, 0x0, 0x0, 0x8f, 0x10,
    0x0,

    /* U+002C "," */
    0x2f, 0x43, 0xf3, 0x6e, 0x7, 0x50,

    /* U+002D "-" */
    0x2, 0x22, 0x5f, 0xff, 0x15, 0x54,

    /* U+002E "." */
    0x1e, 0x62, 0xe7,

    /* U+002F "/" */
    0x0, 0x1, 0xf2, 0x0, 0x6, 0xd0, 0x0, 0xb,
    0x80, 0x0, 0xf, 0x30, 0x0, 0x5e, 0x0, 0x0,
    0xa9, 0x0, 0x0, 0xf4, 0x0, 0x4, 0xf0, 0x0,
    0x9, 0xa0, 0x0, 0xe, 0x50, 0x0,

    /* U+0030 "0" */
    0x3, 0xcf, 0xc2, 0x0, 0xee, 0x8e, 0xd0, 0x4f,
    0x50, 0x8f, 0x26, 0xf4, 0x6, 0xf4, 0x7f, 0x40,
    0x6f, 0x56, 0xf4, 0x6, 0xf4, 0x4f, 0x60, 0x7f,
    0x20, 0xee, 0x8e, 0xd0, 0x3, 0xcf, 0xc2, 0x0,

    /* U+0031 "1" */
    0x0, 0x39, 0xa0, 0xdf, 0xfb, 0x9, 0x4f, 0xb0,
    0x0, 0xfb, 0x0, 0xf, 0xb0, 0x0, 0xfb, 0x0,
    0xf, 0xb0, 0x0, 0xfb, 0x0, 0xf, 0xb0,

    /* U+0032 "2" */
    0x5, 0xdf, 0xc3, 0x3, 0xfc, 0x8f, 0xe0, 0x8f,
    0x20, 0x9f, 0x10, 0x0, 0xc, 0xe0, 0x0, 0x7,
    0xf6, 0x0, 0x5, 0xf9, 0x0, 0x4, 0xfa, 0x0,
    0x3, 0xff, 0x87, 0x73, 0x6f, 0xff, 0xff, 0x60,

    /* U+0033 "3" */
    0x6, 0xef, 0xc3, 0x4, 0xfc, 0x8f, 0xe0, 0x37,
    0x10, 0x9f, 0x20, 0x1, 0x3d, 0xe0, 0x0, 0xbf,
    0xf3, 0x0, 0x3, 0x5d, 0xe1, 0x5a, 0x10, 0x7f,
    0x45, 0xfc, 0x8e, 0xf1, 0x7, 0xef, 0xc4, 0x0,

    /* U+0034 "4" */
    0x0, 0x6, 0xf9, 0x0, 0x1, 0xef, 0x90, 0x0,
    0x9f, 0xf9, 0x0, 0x2f, 0x7f, 0x90, 0xb, 0xc1,
    0xf9, 0x4, 0xf5, 0x3f, 0xa1, 0xaf, 0xff, 0xff,
    0x93, 0x55, 0x6f, 0xb2, 0x0, 0x1, 0xf9, 0x0,

    /* U+0035 "5" */
    0xb, 0xff, 0xff, 0x10, 0xdd, 0x88, 0x80, 0xf,
    0x90, 0x0, 0x1, 0xfe, 0xff, 0x60, 0x19, 0x85,
    0xdf, 0x10, 0x0, 0x5, 0xf5, 0x3a, 0x30, 0x6f,
    0x51, 0xfd, 0x8e, 0xf1, 0x4, 0xdf, 0xd4, 0x0,

    /* U+0036 "6" */
    0x0, 0x4c, 0xf2, 0x0, 0x5f, 0xe9, 0x10, 0xe,
    0xc1, 0x0, 0x4, 0xfd, 0xff, 0x80, 0x5f, 0xc6,
    0xcf, 0x36, 0xf4, 0x4, 0xf6, 0x4f, 0x60, 0x5f,
    0x60, 0xde, 0x8e, 0xf1, 0x2, 0xbf, 0xd4, 0x0,

    /* U+0037 "7" */
    0xaf, 0xff, 0xff, 0x64, 0x77, 0x7c, 0xf2, 0x0,
    0x0, 0xdc, 0x0, 0x0, 0x4f, 0x50, 0x0, 0xb,
    0xe0, 0x0, 0x2, 0xf8, 0x0, 0x0, 0x9f, 0x10,
    0x0, 0x1f, 0xb0, 0x0, 0x7, 0xf4, 0x0, 0x0,

    /* U+0038 "8" */
    0x4, 0xdf, 0xc3, 0x1, 0xfe, 0x8f, 0xe0, 0x3f,
    0x70, 0x9f, 0x11, 0xfb, 0x3d, 0xe0, 0x6, 0xff,
    0xf4, 0x2, 0xfb, 0x5d, 0xe1, 0x6f, 0x40, 0x6f,
    0x43, 0xfd, 0x8e, 0xf1, 0x6, 0xdf, 0xd5, 0x0,

    /* U+0039 "9" */
    0x4, 0xdf, 0xb1, 0x1, 0xfd, 0x8f, 0xc0, 0x6f,
    0x50, 0x9f, 0x17, 0xf3, 0x7, 0xf3, 0x4f, 0xa2,
    0xbf, 0x30, 0xbf, 0xfe, 0xf2, 0x0, 0x22, 0xcd,
    0x0, 0x19, 0xdf, 0x50, 0x3, 0xfc, 0x50, 0x0,

    /* U+003A ":" */
    0x2e, 0x71, 0xe6, 0x0, 0x0, 0x0, 0x0, 0x1,
    0xe6, 0x2e, 0x70,

    /* U+003B ";" */
    0x3f, 0x52, 0xe5, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x83, 0xf, 0x52, 0xf3, 0x7c, 0x0, 0x10,

    /* U+003C "<" */
    0x0, 0x0, 0x0, 0x0, 0x2, 0x95, 0x3, 0xbf,
    0xf4, 0x9f, 0xe7, 0x10, 0xaf, 0xb5, 0x0, 0x5,
    0xdf, 0xf4, 0x0, 0x4, 0xb5, 0x0, 0x0, 0x0,

    /* U+003D "=" */
    0x3f, 0xff, 0xff, 0x1, 0x88, 0x88, 0x80, 0x18,
    0x88, 0x88, 0x3, 0xff, 0xff, 0xf0,

    /* U+003E ">" */
    0x4a, 0x20, 0x0, 0x3f, 0xfb, 0x40, 0x1, 0x7d,
    0xfb, 0x0, 0x5b, 0xfc, 0x3e, 0xfd, 0x60, 0x4c,
    0x50, 0x0, 0x0, 0x0, 0x0,

    /* U+003F "?" */
    0x9, 0xee, 0x90, 0x7f, 0xac, 0xf5, 0x69, 0x3,
    0xf7, 0x0, 0xa, 0xf3, 0x0, 0x8f, 0x50, 0x0,
    0xea, 0x0, 0x0, 0x21, 0x0, 0x0, 0xd8, 0x0,
    0x0, 0xe9, 0x0,

    /* U+0040 "@" */
    0x0, 0x7, 0xdf, 0xea, 0x20, 0x0, 0xb, 0xc4,
    0x12, 0x7e, 0x20, 0x7, 0xc0, 0x0, 0x0, 0x7b,
    0x0, 0xe4, 0x7, 0xed, 0x40, 0xf0, 0x4e, 0x5,
    0xe4, 0xb8, 0xd, 0x36, 0xb0, 0xc8, 0xc, 0x60,
    0xc3, 0x7a, 0xe, 0x50, 0xd5, 0xe, 0x16, 0xb0,
    0xd8, 0x4f, 0x66, 0xc0, 0x3e, 0x5, 0xeb, 0x6e,
    0xc2, 0x0, 0xe6, 0x0, 0x0, 0x0, 0x0, 0x4,
    0xf8, 0x32, 0x52, 0x0, 0x0, 0x3, 0xbe, 0xfc,
    0x30, 0x0,

    /* U+0041 "A" */
    0x0, 0xe, 0xf0, 0x0, 0x0, 0x5, 0xff, 0x60,
    0x0, 0x0, 0xae, 0xdb, 0x0, 0x0, 0xf, 0x98,
    0xf1, 0x0, 0x5, 0xf4, 0x3f, 0x70, 0x0, 0xbf,
    0x98, 0xfc, 0x0, 0x1f, 0xff, 0xff, 0xf2, 0x6,
    0xf5, 0x0, 0x4f, 0x80, 0xcf, 0x10, 0x0, 0xfd,
    0x0,

    /* U+0042 "B" */
    0x3f, 0xff, 0xea, 0x10, 0x3f, 0xc8, 0xbf, 0xa0,
    0x3f, 0x80, 0xe, 0xd0, 0x3f, 0x81, 0x4f, 0xa0,
    0x3f, 0xff, 0xff, 0x20, 0x3f, 0xa4, 0x5e, 0xd0,
    0x3f, 0x80, 0xb, 0xf1, 0x3f, 0xc8, 0xaf, 0xd0,
    0x3f, 0xff, 0xfb, 0x20,

    /* U+0043 "C" */
    0x1, 0x9e, 0xeb, 0x20, 0xc, 0xfb, 0xaf, 0xd0,
    0x3f, 0x90, 0x7, 0xf5, 0x6f, 0x50, 0x0, 0x20,
    0x7f, 0x40, 0x0, 0x0, 0x6f, 0x50, 0x0, 0x10,
    0x3f, 0x90, 0x7, 0xf5, 0xc, 0xfa, 0xaf, 0xd0,
    0x1, 0xaf, 0xeb, 0x20,

    /* U+0044 "D" */
    0x3f, 0xff, 0xd5, 0x0, 0x3f, 0xc9, 0xdf, 0x60,
    0x3f, 0x80, 0xe, 0xe0, 0x3f, 0x80, 0x9, 0xf3,
    0x3f, 0x80, 0x8, 0xf4, 0x3f, 0x80, 0x9, 0xf3,
    0x3f, 0x80, 0xe, 0xe0, 0x3f, 0xc9, 0xdf, 0x60,
    0x3f, 0xff, 0xd5, 0x0,

    /* U+0045 "E" */
    0x3f, 0xff, 0xff, 0x73, 0xfc, 0x88, 0x84, 0x3f,
    0x80, 0x0, 0x3, 0xf9, 0x22, 0x20, 0x3f, 0xff,
    0xfe, 0x3, 0xfa, 0x55, 0x40, 0x3f, 0x80, 0x0,
    0x3, 0xfc, 0x88, 0x84, 0x3f, 0xff, 0xff, 0x70,

    /* U+0046 "F" */
    0x3f, 0xff, 0xff, 0x53, 0xfc, 0x88, 0x82, 0x3f,
    0x80, 0x0, 0x3, 0xfc, 0x88, 0x70, 0x3f, 0xff,
    0xfe, 0x3, 0xf8, 0x0, 0x0, 0x3f, 0x80, 0x0,
    0x3, 0xf8, 0x0, 0x0, 0x3f, 0x80, 0x0, 0x0,

    /* U+0047 "G" */
    0x0, 0x9e, 0xfc, 0x30, 0xb, 0xfb, 0x9e, 0xf2,
    0x3f, 0xb0, 0x4, 0xb4, 0x6f, 0x60, 0x11, 0x10,
    0x7f, 0x50, 0xdf, 0xf8, 0x6f, 0x60, 0x47, 0xf8,
    0x2f, 0xb0, 0x4, 0xf8, 0xb, 0xfc, 0x9d, 0xf7,
    0x0, 0x9e, 0xfd, 0x70,

    /* U+0048 "H" */
    0x3f, 0x80, 0x0, 0xfb, 0x3f, 0x80, 0x0, 0xfb,
    0x3f, 0x80, 0x0, 0xfb, 0x3f, 0xc8, 0x88, 0xfb,
    0x3f, 0xff, 0xff, 0xfb, 0x3f, 0x80, 0x0, 0xfb,
    0x3f, 0x80, 0x0, 0xfb, 0x3f, 0x80, 0x0, 0xfb,
    0x3f, 0x80, 0x0, 0xfb,

    /* U+0049 "I" */
    0x2f, 0xa2, 0xfa, 0x2f, 0xa2, 0xfa, 0x2f, 0xa2,
    0xfa, 0x2f, 0xa2, 0xfa, 0x2f, 0xa0,

    /* U+004A "J" */
    0x0, 0x0, 0xcf, 0x0, 0x0, 0xcf, 0x0, 0x0,
    0xcf, 0x0, 0x0, 0xcf, 0x0, 0x0, 0xcf, 0x0,
    0x0, 0xcf, 0x8c, 0x0, 0xde, 0x7f, 0xba, 0xf9,
    0x9, 0xef, 0xa1,

    /* U+004B "K" */
    0x3f, 0x80, 0xd, 0xf4, 0x3f, 0x80, 0xaf, 0x70,
    0x3f, 0x85, 0xfb, 0x0, 0x3f, 0xaf, 0xe1, 0x0,
    0x3f, 0xff, 0xd0, 0x0, 0x3f, 0xfb, 0xf8, 0x0,
    0x3f, 0x90, 0xdf, 0x20, 0x3f, 0x80, 0x4f, 0xc0,
    0x3f, 0x80, 0xa, 0xf6,

    /* U+004C "L" */
    0x3f, 0x80, 0x0, 0x3, 0xf8, 0x0, 0x0, 0x3f,
    0x80, 0x0, 0x3, 0xf8, 0x0, 0x0, 0x3f, 0x80,
    0x0, 0x3, 0xf8, 0x0, 0x0, 0x3f, 0x80, 0x0,
    0x3, 0xfc, 0x88, 0x82, 0x3f, 0xff, 0xff, 0x40,

    /* U+004D "M" */
    0x3f, 0xf3, 0x0, 0xb, 0xfb, 0x3f, 0xf9, 0x0,
    0x1f, 0xfb, 0x3f, 0xee, 0x0, 0x6f, 0xeb, 0x3f,
    0xaf, 0x30, 0xbb, 0xeb, 0x3f, 0x7e, 0x91, 0xf6,
    0xfb, 0x3f, 0x78, 0xe6, 0xf1, 0xfb, 0x3f, 0x83,
    0xfe, 0xb0, 0xfb, 0x3f, 0x80, 0xdf, 0x50, 0xfb,
    0x3f, 0x80, 0x8f, 0x0, 0xfb,

    /* U+004E "N" */
    0x3f, 0xc0, 0x0, 0xfb, 0x3f, 0xf6, 0x0, 0xfb,
    0x3f, 0xfe, 0x0, 0xfb, 0x3f, 0xcf, 0x80, 0xfb,
    0x3f, 0x8a, 0xf3, 0xfb, 0x3f, 0x81, 0xfb, 0xfb,
    0x3f, 0x80, 0x8f, 0xfb, 0x3f, 0x80, 0xe, 0xfb,
    0x3f, 0x80, 0x5, 0xfb,

    /* U+004F "O" */
    0x0, 0x9e, 0xfb, 0x20, 0xb, 0xfb, 0xaf, 0xe1,
    0x3f, 0xa0, 0x6, 0xf7, 0x6f, 0x50, 0x1, 0xfb,
    0x7f, 0x40, 0x0, 0xfc, 0x6f, 0x50, 0x1, 0xfb,
    0x3f, 0xb0, 0x6, 0xf7, 0xb, 0xfb, 0xaf, 0xe1,
    0x0, 0x9e, 0xfb, 0x20,

    /* U+0050 "P" */
    0x3f, 0xff, 0xfb, 0x20, 0x3f, 0xc8, 0xaf, 0xe0,
    0x3f, 0x80, 0x9, 0xf4, 0x3f, 0x80, 0x1b, 0xf2,
    0x3f, 0xff, 0xff, 0xa0, 0x3f, 0xc8, 0x74, 0x0,
    0x3f, 0x80, 0x0, 0x0, 0x3f, 0x80, 0x0, 0x0,
    0x3f, 0x80, 0x0, 0x0,

    /* U+0051 "Q" */
    0x0, 0x9e, 0xfb, 0x20, 0xb, 0xfb, 0xaf, 0xe0,
    0x3f, 0xa0, 0x6, 0xf7, 0x6f, 0x50, 0x1, 0xfa,
    0x7f, 0x40, 0x0, 0xfc, 0x6f, 0x50, 0x1, 0xfb,
    0x3f, 0xa0, 0x6, 0xf7, 0xb, 0xfb, 0xaf, 0xe0,
    0x0, 0x9e, 0xff, 0xa0, 0x0, 0x0, 0x9, 0xf7,
    0x0, 0x0, 0x0, 0x40,

    /* U+0052 "R" */
    0x3f, 0xff, 0xeb, 0x20, 0x3f, 0xc8, 0xaf, 0xc0,
    0x3f, 0x80, 0xb, 0xf0, 0x3f, 0x80, 0x1e, 0xe0,
    0x3f, 0xff, 0xff, 0x50, 0x3f, 0xc8, 0xfc, 0x0,
    0x3f, 0x80, 0xaf, 0x30, 0x3f, 0x80, 0x2f, 0xb0,
    0x3f, 0x80, 0xb, 0xf2,

    /* U+0053 "S" */
    0x4, 0xcf, 0xe9, 0x1, 0xfe, 0x9b, 0xf9, 0x4f,
    0x70, 0xa, 0xa1, 0xee, 0x71, 0x0, 0x2, 0xbf,
    0xf9, 0x0, 0x0, 0x29, 0xfa, 0x7e, 0x30, 0xd,
    0xe3, 0xfe, 0x8a, 0xfb, 0x4, 0xcf, 0xea, 0x10,

    /* U+0054 "T" */
    0xcf, 0xff, 0xff, 0xf3, 0x68, 0xaf, 0xc8, 0x81,
    0x0, 0x3f, 0x90, 0x0, 0x0, 0x3f, 0x90, 0x0,
    0x0, 0x3f, 0x90, 0x0, 0x0, 0x3f, 0x90, 0x0,
    0x0, 0x3f, 0x90, 0x0, 0x0, 0x3f, 0x90, 0x0,
    0x0, 0x3f, 0x90, 0x0,

    /* U+0055 "U" */
    0x5f, 0x70, 0x8, 0xf3, 0x5f, 0x70, 0x8, 0xf3,
    0x5f, 0x70, 0x8, 0xf3, 0x5f, 0x70, 0x8, 0xf3,
    0x5f, 0x70, 0x8, 0xf3, 0x4f, 0x70, 0x8, 0xf3,
    0x3f, 0x90, 0xa, 0xf1, 0xd, 0xf9, 0xaf, 0xc0,
    0x2, 0xbe, 0xea, 0x10,

    /* U+0056 "V" */
    0xcf, 0x20, 0x4, 0xfa, 0x7f, 0x60, 0x9, 0xf5,
    0x2f, 0xb0, 0xd, 0xf0, 0xc, 0xf0, 0x2f, 0xa0,
    0x7, 0xf3, 0x6f, 0x50, 0x2, 0xf8, 0xaf, 0x0,
    0x0, 0xdc, 0xfa, 0x0, 0x0, 0x7f, 0xf5, 0x0,
    0x0, 0x2f, 0xf0, 0x0,

    /* U+0057 "W" */
    0xbf, 0x0, 0x9f, 0x10, 0x8f, 0x37, 0xf3, 0xd,
    0xf5, 0xb, 0xf0, 0x4f, 0x60, 0xff, 0x80, 0xec,
    0x1, 0xf9, 0x4f, 0xcb, 0xf, 0x90, 0xd, 0xc7,
    0xe6, 0xf3, 0xf5, 0x0, 0xaf, 0xba, 0x2f, 0x9f,
    0x20, 0x6, 0xff, 0x70, 0xee, 0xf0, 0x0, 0x3f,
    0xf3, 0xb, 0xfb, 0x0, 0x0, 0xff, 0x0, 0x7f,
    0x80, 0x0,

    /* U+0058 "X" */
    0x8f, 0x70, 0xd, 0xf2, 0xe, 0xe0, 0x5f, 0x90,
    0x6, 0xf7, 0xdf, 0x10, 0x0, 0xdf, 0xf7, 0x0,
    0x0, 0x7f, 0xf1, 0x0, 0x0, 0xef, 0xf8, 0x0,
    0x7, 0xf7, 0xdf, 0x10, 0x1f, 0xe0, 0x5f, 0xa0,
    0x9f, 0x60, 0xc, 0xf3,

    /* U+0059 "Y" */
    0xbf, 0x20, 0xb, 0xf2, 0x4f, 0x90, 0x2f, 0xa0,
    0xc, 0xf0, 0x9f, 0x20, 0x4, 0xf7, 0xfb, 0x0,
    0x0, 0xcf, 0xf3, 0x0, 0x0, 0x5f, 0xb0, 0x0,
    0x0, 0x3f, 0x90, 0x0, 0x0, 0x3f, 0x90, 0x0,
    0x0, 0x3f, 0x90, 0x0,

    /* U+005A "Z" */
    0x9f, 0xff, 0xff, 0xd4, 0x88, 0x8c, 0xf8, 0x0,
    0x1, 0xed, 0x0, 0x0, 0xaf, 0x30, 0x0, 0x5f,
    0x90, 0x0, 0x1e, 0xd0, 0x0, 0xa, 0xf4, 0x0,
    0x5, 0xfe, 0x88, 0x87, 0x9f, 0xff, 0xff, 0xe0,

    /* U+005B "[" */
    0x1, 0x10, 0x4f, 0xf3, 0x4f, 0x91, 0x4f, 0x60,
    0x4f, 0x60, 0x4f, 0x60, 0x4f, 0x60, 0x4f, 0x60,
    0x4f, 0x60, 0x4f, 0x60, 0x4f, 0x60, 0x4f, 0x60,
    0x4f, 0x70, 0x4f, 0xf3, 0x14, 0x41,

    /* U+005C "\\" */
    0xde, 0x0, 0x0, 0x7f, 0x40, 0x0, 0x1f, 0x90,
    0x0, 0xc, 0xf0, 0x0, 0x6, 0xf5, 0x0, 0x1,
    0xfb, 0x0, 0x0, 0xaf, 0x10, 0x0, 0x5f, 0x60,
    0x0, 0xf, 0xc0, 0x0, 0x9, 0xf1,

    /* U+005D "]" */
    0x11, 0x1e, 0xf9, 0x5f, 0x91, 0xf9, 0x1f, 0x91,
    0xf9, 0x1f, 0x91, 0xf9, 0x1f, 0x91, 0xf9, 0x1f,
    0x91, 0xf9, 0x2f, 0x9e, 0xf9, 0x44, 0x20,

    /* U+005E "^" */
    0x0, 0x72, 0x0, 0x6f, 0xa0, 0xc, 0xbf, 0x2,
    0xf2, 0xe6, 0x8c, 0x8, 0xc0,

    /* U+005F "_" */
    0x22, 0x22, 0x20, 0xff, 0xff, 0xf5, 0x55, 0x55,
    0x51,

    /* U+0060 "`" */
    0x4f, 0x60, 0x7, 0xe1,

    /* U+0061 "a" */
    0x7, 0xef, 0xb1, 0x4, 0xfb, 0x8f, 0x90, 0x25,
    0x10, 0xfc, 0x0, 0x8d, 0xef, 0xc0, 0x7f, 0x62,
    0xec, 0x8, 0xf9, 0x9f, 0xc0, 0x1b, 0xfb, 0xde,
    0x0,

    /* U+0062 "b" */
    0x5f, 0x50, 0x0, 0x5, 0xf5, 0x0, 0x0, 0x5f,
    0x50, 0x0, 0x5, 0xfb, 0xed, 0x40, 0x5f, 0xd8,
    0xee, 0x5, 0xf5, 0x7, 0xf4, 0x5f, 0x50, 0x5f,
    0x55, 0xf5, 0x7, 0xf4, 0x5f, 0xd8, 0xee, 0x5,
    0xf9, 0xed, 0x40,

    /* U+0063 "c" */
    0x5, 0xdf, 0xb1, 0x2f, 0xc9, 0xfa, 0x7f, 0x30,
    0x79, 0x9f, 0x10, 0x0, 0x7f, 0x30, 0x56, 0x2f,
    0xc8, 0xfb, 0x5, 0xdf, 0xb1,

    /* U+0064 "d" */
    0x0, 0x0, 0x9f, 0x10, 0x0, 0x9, 0xf1, 0x0,
    0x0, 0x9f, 0x10, 0x7e, 0xdc, 0xf1, 0x3f, 0xd8,
    0xff, 0x17, 0xf3, 0x9, 0xf1, 0x9f, 0x10, 0x9f,
    0x17, 0xf3, 0x9, 0xf1, 0x3f, 0xc6, 0xef, 0x10,
    0x7e, 0xdb, 0xf1,

    /* U+0065 "e" */
    0x4, 0xdf, 0xb1, 0x2, 0xfd, 0x8f, 0xb0, 0x7f,
    0x40, 0x9f, 0x8, 0xff, 0xff, 0xf2, 0x7f, 0x63,
    0x33, 0x1, 0xfe, 0x8b, 0xc0, 0x3, 0xcf, 0xd4,
    0x0,

    /* U+0066 "f" */
    0x2, 0xcf, 0x40, 0xbf, 0x92, 0xe, 0xd0, 0xd,
    0xff, 0xf1, 0x4e, 0xe5, 0x0, 0xed, 0x0, 0xe,
    0xd0, 0x0, 0xed, 0x0, 0xe, 0xd0, 0x0, 0xed,
    0x0,

    /* U+0067 "g" */
    0x6, 0xee, 0xaf, 0x32, 0xfd, 0x8e, 0xf3, 0x7f,
    0x40, 0x8f, 0x39, 0xf1, 0x8, 0xf3, 0x7f, 0x40,
    0x8f, 0x32, 0xfd, 0x8e, 0xf3, 0x6, 0xee, 0xbf,
    0x30, 0x20, 0xa, 0xf2, 0xe, 0x98, 0xfc, 0x0,
    0x8e, 0xfb, 0x20,

    /* U+0068 "h" */
    0x6f, 0x40, 0x0, 0x6, 0xf4, 0x0, 0x0, 0x6f,
    0x40, 0x0, 0x6, 0xf9, 0xee, 0x50, 0x6f, 0xd8,
    0xfe, 0x6, 0xf4, 0xa, 0xf1, 0x6f, 0x40, 0x9f,
    0x16, 0xf4, 0x9, 0xf1, 0x6f, 0x40, 0x9f, 0x16,
    0xf4, 0x9, 0xf1,

    /* U+0069 "i" */
    0x2f, 0x52, 0xd4, 0x0, 0x4, 0xf7, 0x4f, 0x74,
    0xf7, 0x4f, 0x74, 0xf7, 0x4f, 0x74, 0xf7,

    /* U+006A "j" */
    0x3, 0xf5, 0x2, 0xd4, 0x0, 0x0, 0x4, 0xf7,
    0x4, 0xf7, 0x4, 0xf7, 0x4, 0xf7, 0x4, 0xf7,
    0x4, 0xf7, 0x4, 0xf7, 0x4, 0xf6, 0x4c, 0xf4,
    0x8f, 0x90,

    /* U+006B "k" */
    0x5f, 0x50, 0x0, 0x5, 0xf5, 0x0, 0x0, 0x5f,
    0x50, 0x0, 0x5, 0xf5, 0x2f, 0xd1, 0x5f, 0x6d,
    0xf2, 0x5, 0xfe, 0xf5, 0x0, 0x5f, 0xff, 0x60,
    0x5, 0xfa, 0xde, 0x10, 0x5f, 0x54, 0xf9, 0x5,
    0xf5, 0xb, 0xf3,

    /* U+006C "l" */
    0x4f, 0x74, 0xf7, 0x4f, 0x74, 0xf7, 0x4f, 0x74,
    0xf7, 0x4f, 0x74, 0xf7, 0x4f, 0x74, 0xf7,

    /* U+006D "m" */
    0x5f, 0x8d, 0xe6, 0x9f, 0xc2, 0x5f, 0xd8, 0xff,
    0xba, 0xf9, 0x5f, 0x50, 0xaf, 0x0, 0xfb, 0x5f,
    0x50, 0xaf, 0x0, 0xfb, 0x5f, 0x50, 0xaf, 0x0,
    0xfb, 0x5f, 0x50, 0xaf, 0x0, 0xfb, 0x5f, 0x50,
    0xaf, 0x0, 0xfb,

    /* U+006E "n" */
    0x6f, 0x8d, 0xe5, 0x6, 0xfd, 0x8f, 0xe0, 0x6f,
    0x50, 0xaf, 0x16, 0xf5, 0x9, 0xf1, 0x6f, 0x50,
    0x9f, 0x16, 0xf5, 0x9, 0xf1, 0x6f, 0x50, 0x9f,
    0x10,

    /* U+006F "o" */
    0x4, 0xdf, 0xb2, 0x2, 0xfd, 0x8f, 0xd0, 0x7f,
    0x30, 0x7f, 0x39, 0xf1, 0x5, 0xf5, 0x7f, 0x30,
    0x7f, 0x42, 0xfd, 0x8e, 0xd0, 0x4, 0xdf, 0xc2,
    0x0,

    /* U+0070 "p" */
    0x5f, 0xae, 0xd4, 0x5, 0xfc, 0x6e, 0xe0, 0x5f,
    0x50, 0x7f, 0x35, 0xf5, 0x5, 0xf5, 0x5f, 0x50,
    0x7f, 0x35, 0xfd, 0x8e, 0xe0, 0x5f, 0xbe, 0xd4,
    0x5, 0xf5, 0x0, 0x0, 0x5f, 0x50, 0x0, 0x5,
    0xf5, 0x0, 0x0,

    /* U+0071 "q" */
    0x7, 0xed, 0xaf, 0x13, 0xfd, 0x8f, 0xf1, 0x8f,
    0x30, 0x9f, 0x19, 0xf1, 0x9, 0xf1, 0x7f, 0x30,
    0x9f, 0x13, 0xfd, 0x8f, 0xf1, 0x7, 0xed, 0xcf,
    0x10, 0x0, 0x9, 0xf1, 0x0, 0x0, 0x9f, 0x10,
    0x0, 0x9, 0xf1,

    /* U+0072 "r" */
    0x0, 0x0, 0x5, 0xfa, 0xe3, 0x5f, 0xfb, 0x25,
    0xf6, 0x0, 0x5f, 0x50, 0x5, 0xf5, 0x0, 0x5f,
    0x50, 0x5, 0xf5, 0x0,

    /* U+0073 "s" */
    0x8, 0xee, 0xa0, 0x5f, 0x97, 0xf8, 0x5f, 0x81,
    0x32, 0x9, 0xff, 0xc2, 0x24, 0x5, 0xfa, 0x7f,
    0x86, 0xf9, 0x8, 0xef, 0xa1,

    /* U+0074 "t" */
    0x8, 0x50, 0xf, 0xa0, 0xff, 0xfc, 0x5f, 0xc4,
    0xf, 0xa0, 0xf, 0xa0, 0xf, 0xa0, 0xf, 0xe7,
    0x7, 0xfb,

    /* U+0075 "u" */
    0x6f, 0x40, 0x9f, 0x16, 0xf4, 0x9, 0xf1, 0x6f,
    0x40, 0x9f, 0x16, 0xf4, 0x9, 0xf1, 0x5f, 0x50,
    0x9f, 0x13, 0xfc, 0x8f, 0xf1, 0x9, 0xfd, 0xbf,
    0x10,

    /* U+0076 "v" */
    0xcf, 0x0, 0xed, 0x7f, 0x32, 0xf8, 0x2f, 0x76,
    0xf3, 0xd, 0xba, 0xe0, 0x8, 0xfe, 0x90, 0x3,
    0xff, 0x40, 0x0, 0xef, 0x0,

    /* U+0077 "w" */
    0xbe, 0x5, 0xf2, 0x1f, 0x87, 0xf1, 0x9f, 0x64,
    0xf4, 0x4f, 0x4d, 0xfa, 0x7f, 0x0, 0xf9, 0xf8,
    0xea, 0xd0, 0xc, 0xfd, 0x1f, 0xf9, 0x0, 0x9f,
    0x90, 0xdf, 0x50, 0x5, 0xf5, 0x8, 0xf2, 0x0,

    /* U+0078 "x" */
    0x8f, 0x42, 0xfa, 0x1, 0xfc, 0xaf, 0x20, 0x7,
    0xff, 0x90, 0x0, 0x2f, 0xf4, 0x0, 0x9, 0xff,
    0xb0, 0x1, 0xfb, 0x9f, 0x30, 0x9f, 0x31, 0xfc,
    0x0,

    /* U+0079 "y" */
    0xdf, 0x0, 0xed, 0x8f, 0x43, 0xf8, 0x3f, 0x88,
    0xf3, 0xe, 0xcc, 0xe0, 0x9, 0xff, 0x90, 0x4,
    0xff, 0x40, 0x0, 0xff, 0x0, 0x0, 0xea, 0x0,
    0x2b, 0xf5, 0x0, 0x4f, 0xa0, 0x0,

    /* U+007A "z" */
    0x7f, 0xff, 0xf9, 0x37, 0x7d, 0xf5, 0x0, 0x4f,
    0xa0, 0x0, 0xee, 0x10, 0xa, 0xf4, 0x0, 0x4f,
    0xe7, 0x75, 0x9f, 0xff, 0xfb,

    /* U+007B "{" */
    0x0, 0x24, 0x2, 0xf7, 0x9, 0xe0, 0xa, 0xd0,
    0xa, 0xd0, 0x1e, 0xa0, 0xbf, 0x20, 0x3e, 0x90,
    0xb, 0xd0, 0xa, 0xd0, 0x9, 0xe0, 0x3, 0xf6,
    0x0, 0x46,

    /* U+007C "|" */
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
    0xf0, 0xf0, 0xf0,

    /* U+007D "}" */
    0x52, 0x0, 0x8f, 0x20, 0xf, 0x80, 0xe, 0xa0,
    0xe, 0xa0, 0xb, 0xd1, 0x2, 0xfb, 0xa, 0xe3,
    0xd, 0xa0, 0xe, 0xa0, 0xf, 0x80, 0x6f, 0x30,
    0x64, 0x0,

    /* U+007E "~" */
    0x8, 0xfa, 0x3, 0xf1, 0x2f, 0x9e, 0xcb, 0xe0,
    0x39, 0x2, 0xce, 0x40
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 48, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 52, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 62, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 22, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 110, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 96, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 31, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 177, .adv_w = 67, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 205, .adv_w = 68, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 233, .adv_w = 87, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 251, .adv_w = 105, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 276, .adv_w = 47, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 282, .adv_w = 74, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 288, .adv_w = 56, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 72, .box_w = 6, .box_h = 10, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 321, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 110, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 600, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 54, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 50, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 658, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 110, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 696, .adv_w = 99, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 96, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 172, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 810, .adv_w = 129, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 123, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 887, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 923, .adv_w = 125, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 959, .adv_w = 108, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 991, .adv_w = 105, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1023, .adv_w = 131, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1059, .adv_w = 136, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1095, .adv_w = 56, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1109, .adv_w = 107, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1136, .adv_w = 122, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1172, .adv_w = 104, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1204, .adv_w = 168, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1249, .adv_w = 136, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1285, .adv_w = 133, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1321, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1357, .adv_w = 133, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1401, .adv_w = 123, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1437, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1469, .adv_w = 119, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1505, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1541, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1577, .adv_w = 168, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1627, .adv_w = 122, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1663, .adv_w = 119, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1699, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1731, .adv_w = 53, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1761, .adv_w = 81, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1791, .adv_w = 53, .box_w = 3, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1814, .adv_w = 84, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1827, .adv_w = 86, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1836, .adv_w = 63, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1840, .adv_w = 103, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1865, .adv_w = 108, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1900, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1921, .adv_w = 108, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1956, .adv_w = 104, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1981, .adv_w = 69, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2006, .adv_w = 110, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2041, .adv_w = 107, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2076, .adv_w = 51, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2091, .adv_w = 50, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 2117, .adv_w = 103, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2152, .adv_w = 51, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2167, .adv_w = 166, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2202, .adv_w = 108, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2227, .adv_w = 109, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2252, .adv_w = 108, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2287, .adv_w = 108, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2322, .adv_w = 70, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2342, .adv_w = 99, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2363, .adv_w = 65, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2381, .adv_w = 107, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2406, .adv_w = 97, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2427, .adv_w = 141, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2459, .adv_w = 98, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2484, .adv_w = 96, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2514, .adv_w = 98, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2535, .adv_w = 63, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2561, .adv_w = 49, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2572, .adv_w = 63, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2598, .adv_w = 125, .box_w = 8, .box_h = 3, .ofs_x = 0, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    1, 53,
    3, 3,
    3, 8,
    3, 34,
    3, 66,
    3, 68,
    3, 69,
    3, 70,
    3, 72,
    3, 78,
    3, 79,
    3, 80,
    3, 81,
    3, 82,
    3, 84,
    3, 88,
    8, 3,
    8, 8,
    8, 34,
    8, 66,
    8, 68,
    8, 69,
    8, 70,
    8, 72,
    8, 78,
    8, 79,
    8, 80,
    8, 81,
    8, 82,
    8, 84,
    8, 88,
    9, 55,
    9, 56,
    9, 58,
    13, 3,
    13, 8,
    15, 3,
    15, 8,
    16, 16,
    34, 3,
    34, 8,
    34, 32,
    34, 36,
    34, 40,
    34, 48,
    34, 50,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 58,
    34, 78,
    34, 79,
    34, 80,
    34, 81,
    34, 85,
    34, 86,
    34, 87,
    34, 88,
    34, 90,
    34, 91,
    35, 53,
    35, 55,
    35, 58,
    36, 10,
    36, 53,
    36, 62,
    36, 94,
    37, 13,
    37, 15,
    37, 34,
    37, 53,
    37, 55,
    37, 57,
    37, 58,
    37, 59,
    38, 53,
    38, 68,
    38, 69,
    38, 70,
    38, 71,
    38, 72,
    38, 80,
    38, 82,
    38, 86,
    38, 87,
    38, 88,
    38, 90,
    39, 13,
    39, 15,
    39, 34,
    39, 43,
    39, 53,
    39, 66,
    39, 68,
    39, 69,
    39, 70,
    39, 72,
    39, 80,
    39, 82,
    39, 83,
    39, 86,
    39, 87,
    39, 90,
    41, 34,
    41, 53,
    41, 57,
    41, 58,
    42, 34,
    42, 53,
    42, 57,
    42, 58,
    43, 34,
    44, 14,
    44, 36,
    44, 40,
    44, 48,
    44, 50,
    44, 68,
    44, 69,
    44, 70,
    44, 72,
    44, 80,
    44, 82,
    44, 86,
    44, 87,
    44, 88,
    44, 90,
    45, 3,
    45, 8,
    45, 34,
    45, 36,
    45, 40,
    45, 48,
    45, 50,
    45, 53,
    45, 54,
    45, 55,
    45, 56,
    45, 58,
    45, 86,
    45, 87,
    45, 88,
    45, 90,
    46, 34,
    46, 53,
    46, 57,
    46, 58,
    47, 34,
    47, 53,
    47, 57,
    47, 58,
    48, 13,
    48, 15,
    48, 34,
    48, 53,
    48, 55,
    48, 57,
    48, 58,
    48, 59,
    49, 13,
    49, 15,
    49, 34,
    49, 43,
    49, 57,
    49, 59,
    49, 66,
    49, 68,
    49, 69,
    49, 70,
    49, 72,
    49, 80,
    49, 82,
    49, 85,
    49, 87,
    49, 90,
    50, 53,
    50, 55,
    50, 56,
    50, 58,
    51, 53,
    51, 55,
    51, 58,
    53, 1,
    53, 13,
    53, 14,
    53, 15,
    53, 34,
    53, 36,
    53, 40,
    53, 43,
    53, 48,
    53, 50,
    53, 52,
    53, 53,
    53, 55,
    53, 56,
    53, 58,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 72,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 86,
    53, 87,
    53, 88,
    53, 89,
    53, 90,
    53, 91,
    54, 34,
    55, 10,
    55, 13,
    55, 14,
    55, 15,
    55, 34,
    55, 36,
    55, 40,
    55, 48,
    55, 50,
    55, 62,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 72,
    55, 80,
    55, 82,
    55, 83,
    55, 86,
    55, 87,
    55, 90,
    55, 94,
    56, 10,
    56, 13,
    56, 14,
    56, 15,
    56, 34,
    56, 53,
    56, 62,
    56, 66,
    56, 68,
    56, 69,
    56, 70,
    56, 72,
    56, 80,
    56, 82,
    56, 83,
    56, 86,
    56, 94,
    57, 14,
    57, 36,
    57, 40,
    57, 48,
    57, 50,
    57, 55,
    57, 68,
    57, 69,
    57, 70,
    57, 72,
    57, 80,
    57, 82,
    57, 86,
    57, 87,
    57, 90,
    58, 7,
    58, 10,
    58, 11,
    58, 13,
    58, 14,
    58, 15,
    58, 34,
    58, 36,
    58, 40,
    58, 43,
    58, 48,
    58, 50,
    58, 52,
    58, 53,
    58, 54,
    58, 55,
    58, 56,
    58, 57,
    58, 58,
    58, 62,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 71,
    58, 72,
    58, 78,
    58, 79,
    58, 80,
    58, 81,
    58, 82,
    58, 83,
    58, 84,
    58, 85,
    58, 86,
    58, 87,
    58, 89,
    58, 90,
    58, 91,
    58, 94,
    59, 34,
    59, 36,
    59, 40,
    59, 48,
    59, 50,
    59, 68,
    59, 69,
    59, 70,
    59, 72,
    59, 80,
    59, 82,
    59, 86,
    59, 87,
    59, 88,
    59, 90,
    60, 43,
    60, 54,
    66, 3,
    66, 8,
    66, 87,
    66, 90,
    67, 3,
    67, 8,
    67, 87,
    67, 89,
    67, 90,
    67, 91,
    68, 3,
    68, 8,
    70, 3,
    70, 8,
    70, 87,
    70, 90,
    71, 3,
    71, 8,
    71, 10,
    71, 62,
    71, 68,
    71, 69,
    71, 70,
    71, 72,
    71, 82,
    71, 94,
    73, 3,
    73, 8,
    76, 68,
    76, 69,
    76, 70,
    76, 72,
    76, 82,
    78, 3,
    78, 8,
    79, 3,
    79, 8,
    80, 3,
    80, 8,
    80, 87,
    80, 89,
    80, 90,
    80, 91,
    81, 3,
    81, 8,
    81, 87,
    81, 89,
    81, 90,
    81, 91,
    83, 3,
    83, 8,
    83, 13,
    83, 15,
    83, 66,
    83, 68,
    83, 69,
    83, 70,
    83, 71,
    83, 72,
    83, 80,
    83, 82,
    83, 85,
    83, 87,
    83, 88,
    83, 90,
    85, 80,
    87, 3,
    87, 8,
    87, 13,
    87, 15,
    87, 66,
    87, 68,
    87, 69,
    87, 70,
    87, 71,
    87, 72,
    87, 80,
    87, 82,
    88, 13,
    88, 15,
    89, 68,
    89, 69,
    89, 70,
    89, 72,
    89, 80,
    89, 82,
    90, 3,
    90, 8,
    90, 13,
    90, 15,
    90, 66,
    90, 68,
    90, 69,
    90, 70,
    90, 71,
    90, 72,
    90, 80,
    90, 82,
    91, 68,
    91, 69,
    91, 70,
    91, 72,
    91, 80,
    91, 82,
    92, 43,
    92, 54
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -6, -3, -3, -11, -5, -6, -6, -6,
    -6, -2, -2, -9, -2, -6, -9, 1,
    -3, -3, -11, -5, -6, -6, -6, -6,
    -2, -2, -9, -2, -6, -9, 1, 2,
    4, 2, -27, -27, -27, -27, -23, -11,
    -11, -8, -2, -2, -2, -2, -11, -2,
    -7, -4, -14, -4, -4, -1, -4, -2,
    -1, -5, -3, -5, 1, -3, -2, -5,
    -2, -3, -1, -2, -11, -11, -2, -8,
    -2, -2, -4, -2, 2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2,
    -26, -26, -18, -19, 2, -3, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2,
    2, -3, 2, -3, 2, -3, 2, -3,
    -2, -15, -3, -3, -3, -3, -2, -2,
    -2, -2, -3, -2, -2, -4, -6, -4,
    -27, -27, 2, -6, -6, -6, -6, -19,
    -2, -19, -9, -26, -1, -12, -5, -12,
    2, -3, 2, -3, 2, -3, 2, -3,
    -11, -11, -2, -8, -2, -2, -4, -2,
    -38, -38, -17, -17, -5, -3, -1, -1,
    -1, -1, -1, -1, -1, 1, 1, 1,
    -3, -3, -2, -3, -5, -2, -4, -6,
    -24, -25, -24, -11, -3, -3, -20, -3,
    -3, -1, 2, 2, 1, 2, -16, -8,
    -8, -8, -8, -8, -8, -19, -8, -8,
    -6, -7, -6, -8, -4, -7, -8, -6,
    -2, 2, -20, -15, -20, -7, -1, -1,
    -1, -1, 2, -4, -4, -4, -4, -4,
    -4, -4, -3, -3, -1, -1, 2, 1,
    -13, -6, -13, -4, 1, 1, -3, -3,
    -3, -3, -3, -3, -3, -2, -2, 1,
    -15, -2, -2, -2, -2, 1, -2, -2,
    -2, -2, -2, -2, -2, -3, -3, -3,
    2, -5, -22, -14, -22, -14, -3, -3,
    -9, -3, -3, -1, 2, -9, 2, 2,
    1, 2, 2, -6, -6, -6, -6, -2,
    -6, -4, -4, -6, -4, -6, -4, -5,
    -2, -4, -2, -2, -2, -3, 2, 1,
    -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -3, -3, -3, -2, -2,
    -2, -2, -1, -1, -3, -3, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    2, 2, 2, 2, -2, -2, -2, -2,
    -2, 2, -7, -7, -2, -2, -2, -2,
    -2, -7, -7, -7, -7, -8, -8, -1,
    -2, -1, -1, -3, -3, -1, -1, -1,
    -1, 2, 2, -16, -16, -3, -2, -2,
    -2, 2, -2, -3, -2, 5, 2, 2,
    2, -3, 1, 1, -16, -16, -1, -1,
    -1, -1, 1, -1, -1, -1, -12, -12,
    -2, -2, -2, -2, -4, -2, 1, 1,
    -16, -16, -1, -1, -1, -1, 1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -2, -2
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 434,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_Roboto_Bold_12 = {
#else
lv_font_t ui_font_Roboto_Bold_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_ROBOTO_BOLD_12*/
