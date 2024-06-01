/*******************************************************************************
 * Size: 10 px
 * Bpp: 4
 * Opts: --bpp 4 --size 10 --font C:/Users/Raizen/Documents/SquareLine/assets/Roboto-Bold.ttf -o C:/Users/Raizen/Documents/SquareLine/assets\ui_font_Roboto_Bold_10.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_ROBOTO_BOLD_10
#define UI_FONT_ROBOTO_BOLD_10 1
#endif

#if UI_FONT_ROBOTO_BOLD_10

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x5f, 0x25, 0xf1, 0x4f, 0x14, 0xf0, 0x3f, 0x1,
    0x70, 0x18, 0x3, 0xe1,

    /* U+0022 "\"" */
    0xb6, 0xeb, 0x5d, 0xb3, 0xb0,

    /* U+0023 "#" */
    0x0, 0xc1, 0xe0, 0x0, 0xe1, 0xc0, 0x5f, 0xff,
    0xfb, 0x4, 0xa6, 0x70, 0x6, 0x88, 0x50, 0xaf,
    0xff, 0xf5, 0xa, 0x3d, 0x10, 0xd, 0x1d, 0x0,

    /* U+0024 "$" */
    0x0, 0x22, 0x0, 0x0, 0x77, 0x0, 0xb, 0xff,
    0xa0, 0x3f, 0x56, 0xf2, 0x3f, 0x50, 0x51, 0xa,
    0xfa, 0x10, 0x0, 0x5d, 0xe0, 0x59, 0x3, 0xf3,
    0x4f, 0x7a, 0xf1, 0x8, 0xed, 0x60, 0x0, 0x75,
    0x0,

    /* U+0025 "%" */
    0x2d, 0xd2, 0x0, 0x7, 0x77, 0x84, 0x80, 0x78,
    0x88, 0xd1, 0x1, 0xdd, 0x97, 0x0, 0x0, 0x1d,
    0x9e, 0x60, 0x9, 0x6e, 0x2e, 0x2, 0xb1, 0xe1,
    0xe0, 0x1, 0x9, 0xe7,

    /* U+0026 "&" */
    0x6, 0xed, 0x20, 0x0, 0xf9, 0xba, 0x0, 0xf,
    0x6b, 0x80, 0x0, 0x9f, 0xb0, 0x0, 0x2e, 0xeb,
    0x3d, 0x9, 0xd2, 0xfd, 0xd0, 0x8e, 0x39, 0xf8,
    0x1, 0xbf, 0xeb, 0xe2,

    /* U+0027 "'" */
    0xb5, 0xb4, 0xb3,

    /* U+0028 "(" */
    0x0, 0x62, 0x4, 0xd1, 0xc, 0x50, 0x1f, 0x0,
    0x4e, 0x0, 0x5d, 0x0, 0x5d, 0x0, 0x4e, 0x0,
    0xf, 0x20, 0x9, 0x80, 0x1, 0xe2, 0x0, 0x20,

    /* U+0029 ")" */
    0x61, 0x6, 0xc0, 0xd, 0x50, 0x9a, 0x6, 0xd0,
    0x5f, 0x5, 0xe0, 0x6c, 0xa, 0x90, 0xf2, 0x98,
    0x3, 0x0,

    /* U+002A "*" */
    0x2, 0xc0, 0x7, 0x5c, 0x63, 0x4c, 0xf9, 0x20,
    0xdb, 0x70, 0x16, 0x17, 0x0,

    /* U+002B "+" */
    0x0, 0xb4, 0x0, 0x11, 0xf7, 0x10, 0xbf, 0xff,
    0xf2, 0x34, 0xf9, 0x40, 0x0, 0xf6, 0x0, 0x0,
    0xf6, 0x0,

    /* U+002C "," */
    0x5e, 0x5c, 0xa7, 0x10,

    /* U+002D "-" */
    0x0, 0x0, 0x7f, 0xf4, 0x13, 0x30,

    /* U+002E "." */
    0x19, 0x3, 0xe1,

    /* U+002F "/" */
    0x0, 0x9, 0x70, 0x0, 0xe2, 0x0, 0x3d, 0x0,
    0x8, 0x80, 0x0, 0xd3, 0x0, 0x2e, 0x0, 0x7,
    0x90, 0x0, 0xc4, 0x0, 0x7, 0x0, 0x0,

    /* U+0030 "0" */
    0x7, 0xed, 0x40, 0x3f, 0x7a, 0xe0, 0x7e, 0x3,
    0xf2, 0x8e, 0x2, 0xf4, 0x8e, 0x2, 0xf4, 0x7e,
    0x3, 0xf2, 0x3f, 0x7a, 0xe0, 0x7, 0xed, 0x40,

    /* U+0031 "1" */
    0x1, 0x7c, 0x2f, 0xfe, 0x13, 0x8e, 0x0, 0x8e,
    0x0, 0x8e, 0x0, 0x8e, 0x0, 0x8e, 0x0, 0x8e,

    /* U+0032 "2" */
    0x8, 0xfe, 0x50, 0x6f, 0x6b, 0xf0, 0x57, 0x5,
    0xf1, 0x0, 0xb, 0xc0, 0x0, 0x7f, 0x30, 0x5,
    0xf5, 0x0, 0x3f, 0xb4, 0x41, 0x8f, 0xff, 0xf5,

    /* U+0033 "3" */
    0xa, 0xfe, 0x50, 0x7f, 0x5a, 0xf0, 0x0, 0x7,
    0xf0, 0x1, 0xff, 0x60, 0x0, 0x39, 0xe0, 0x23,
    0x3, 0xf3, 0x8f, 0x5a, 0xf1, 0xa, 0xfd, 0x50,

    /* U+0034 "4" */
    0x0, 0x1f, 0xa0, 0x0, 0x9f, 0xa0, 0x3, 0xfd,
    0xa0, 0xb, 0x7c, 0xa0, 0x5e, 0x1c, 0xa0, 0xbf,
    0xff, 0xf7, 0x23, 0x3c, 0xb1, 0x0, 0xc, 0xa0,

    /* U+0035 "5" */
    0xf, 0xff, 0xf1, 0xf, 0x75, 0x50, 0x2f, 0x20,
    0x0, 0x3f, 0xee, 0x70, 0x17, 0x48, 0xf2, 0x12,
    0x2, 0xf4, 0x5f, 0x79, 0xf2, 0x8, 0xfe, 0x60,

    /* U+0036 "6" */
    0x0, 0x9e, 0x40, 0xb, 0xe7, 0x10, 0x3f, 0x40,
    0x0, 0x7f, 0xcf, 0x90, 0x8f, 0x67, 0xf3, 0x6f,
    0x0, 0xf5, 0x2f, 0x78, 0xf2, 0x6, 0xee, 0x60,

    /* U+0037 "7" */
    0xbf, 0xff, 0xf4, 0x34, 0x48, 0xf1, 0x0, 0xa,
    0xb0, 0x0, 0x1f, 0x40, 0x0, 0x7e, 0x0, 0x0,
    0xe8, 0x0, 0x4, 0xf2, 0x0, 0xb, 0xc0, 0x0,

    /* U+0038 "8" */
    0x9, 0xfe, 0x60, 0x4f, 0x7a, 0xf0, 0x4f, 0x48,
    0xf0, 0xb, 0xff, 0x60, 0x3f, 0x69, 0xe0, 0x7e,
    0x2, 0xf3, 0x5f, 0x69, 0xf1, 0x9, 0xee, 0x60,

    /* U+0039 "9" */
    0x8, 0xfd, 0x30, 0x5f, 0x6b, 0xd0, 0x8d, 0x3,
    0xf2, 0x7f, 0x26, 0xf3, 0x1d, 0xfe, 0xf2, 0x0,
    0x27, 0xf0, 0x2, 0x7f, 0x80, 0x8, 0xe8, 0x0,

    /* U+003A ":" */
    0x3e, 0x11, 0x90, 0x0, 0x0, 0x0, 0x19, 0x3,
    0xe1,

    /* U+003B ";" */
    0x4d, 0x2, 0x80, 0x0, 0x0, 0x0, 0x15, 0x3,
    0xf0, 0x4d, 0x7, 0x50,

    /* U+003C "<" */
    0x0, 0x0, 0x0, 0x1, 0x86, 0x29, 0xfe, 0x4b,
    0xf6, 0x0, 0x5d, 0xfa, 0x20, 0x5, 0xc7, 0x0,
    0x0, 0x10,

    /* U+003D "=" */
    0x0, 0x0, 0x0, 0x5f, 0xff, 0xf0, 0x14, 0x44,
    0x40, 0x5f, 0xff, 0xf0, 0x13, 0x33, 0x30,

    /* U+003E ">" */
    0x59, 0x10, 0x3, 0xdf, 0xa2, 0x0, 0x5e, 0xd2,
    0xaf, 0xe6, 0x6d, 0x50, 0x1, 0x0, 0x0,

    /* U+003F "?" */
    0x2c, 0xfb, 0x1a, 0xe6, 0xf8, 0x22, 0xe, 0x80,
    0x8, 0xe2, 0x2, 0xf4, 0x0, 0x27, 0x0, 0x2,
    0x80, 0x0, 0x4e, 0x0,

    /* U+0040 "@" */
    0x0, 0x4c, 0xed, 0x80, 0x0, 0x5d, 0x20, 0x7,
    0xa0, 0xe, 0x14, 0xed, 0x2c, 0x25, 0xa0, 0xe2,
    0xb3, 0x77, 0x87, 0x4c, 0xc, 0x25, 0x88, 0x66,
    0xa0, 0xd1, 0x67, 0x77, 0x5b, 0x2f, 0x1b, 0x33,
    0xd1, 0xdc, 0x9e, 0x80, 0xb, 0x91, 0x1, 0x0,
    0x0, 0x9, 0xef, 0xc1, 0x0,

    /* U+0041 "A" */
    0x0, 0x7f, 0x30, 0x0, 0xc, 0xf8, 0x0, 0x2,
    0xfb, 0xd0, 0x0, 0x7e, 0x3f, 0x30, 0xc, 0xa1,
    0xe8, 0x2, 0xff, 0xff, 0xd0, 0x7f, 0x44, 0x6f,
    0x3c, 0xb0, 0x0, 0xf8,

    /* U+0042 "B" */
    0x5f, 0xff, 0xb2, 0x5f, 0x66, 0xea, 0x5f, 0x10,
    0xda, 0x5f, 0xff, 0xf2, 0x5f, 0x43, 0xdb, 0x5f,
    0x10, 0x9e, 0x5f, 0x65, 0xeb, 0x5f, 0xff, 0xc2,

    /* U+0043 "C" */
    0x4, 0xdf, 0xc2, 0x1, 0xfb, 0x6c, 0xd0, 0x6f,
    0x10, 0x3c, 0x18, 0xe0, 0x0, 0x0, 0x8e, 0x0,
    0x0, 0x6, 0xf1, 0x3, 0xb1, 0x1f, 0xb5, 0xcd,
    0x0, 0x4d, 0xfc, 0x20,

    /* U+0044 "D" */
    0x5f, 0xfe, 0x70, 0x5, 0xf6, 0x8f, 0x60, 0x5f,
    0x10, 0xad, 0x5, 0xf1, 0x7, 0xf0, 0x5f, 0x10,
    0x7f, 0x5, 0xf1, 0xa, 0xd0, 0x5f, 0x68, 0xf7,
    0x5, 0xff, 0xe7, 0x0,

    /* U+0045 "E" */
    0x5f, 0xff, 0xf6, 0x5f, 0x65, 0x52, 0x5f, 0x20,
    0x0, 0x5f, 0xff, 0xe0, 0x5f, 0x43, 0x30, 0x5f,
    0x10, 0x0, 0x5f, 0x65, 0x52, 0x5f, 0xff, 0xf6,

    /* U+0046 "F" */
    0x5f, 0xff, 0xf4, 0x5f, 0x65, 0x51, 0x5f, 0x21,
    0x0, 0x5f, 0xff, 0xe0, 0x5f, 0x54, 0x30, 0x5f,
    0x10, 0x0, 0x5f, 0x10, 0x0, 0x5f, 0x10, 0x0,

    /* U+0047 "G" */
    0x4, 0xdf, 0xc3, 0x1, 0xfc, 0x6c, 0xe0, 0x6f,
    0x20, 0x2b, 0x28, 0xf0, 0x0, 0x0, 0x8f, 0x8,
    0xff, 0x46, 0xf2, 0x15, 0xf4, 0x1e, 0xc5, 0x9f,
    0x40, 0x3c, 0xfe, 0x80,

    /* U+0048 "H" */
    0x5f, 0x10, 0xf, 0x65, 0xf1, 0x0, 0xf6, 0x5f,
    0x21, 0x1f, 0x65, 0xff, 0xff, 0xf6, 0x5f, 0x54,
    0x4f, 0x65, 0xf1, 0x0, 0xf6, 0x5f, 0x10, 0xf,
    0x65, 0xf1, 0x0, 0xf6,

    /* U+0049 "I" */
    0x4f, 0x34, 0xf3, 0x4f, 0x34, 0xf3, 0x4f, 0x34,
    0xf3, 0x4f, 0x34, 0xf3,

    /* U+004A "J" */
    0x0, 0x8, 0xf0, 0x0, 0x8f, 0x0, 0x8, 0xf0,
    0x0, 0x8f, 0x0, 0x8, 0xf5, 0x50, 0x8f, 0x9e,
    0x5d, 0xc1, 0xbf, 0xc2,

    /* U+004B "K" */
    0x5f, 0x10, 0xce, 0x15, 0xf1, 0x7f, 0x40, 0x5f,
    0x4f, 0x90, 0x5, 0xfd, 0xf0, 0x0, 0x5f, 0xff,
    0x60, 0x5, 0xf4, 0xbe, 0x0, 0x5f, 0x12, 0xf8,
    0x5, 0xf1, 0x9, 0xf2,

    /* U+004C "L" */
    0x5f, 0x10, 0x0, 0x5f, 0x10, 0x0, 0x5f, 0x10,
    0x0, 0x5f, 0x10, 0x0, 0x5f, 0x10, 0x0, 0x5f,
    0x10, 0x0, 0x5f, 0x65, 0x51, 0x5f, 0xff, 0xf3,

    /* U+004D "M" */
    0x5f, 0xb0, 0x0, 0xff, 0x15, 0xff, 0x0, 0x4f,
    0xf1, 0x5f, 0xe5, 0x9, 0xdf, 0x15, 0xf9, 0xa0,
    0xe9, 0xf1, 0x5f, 0x4f, 0x3f, 0x5f, 0x15, 0xf1,
    0xec, 0xa5, 0xf1, 0x5f, 0x19, 0xf5, 0x5f, 0x15,
    0xf1, 0x4f, 0x5, 0xf1,

    /* U+004E "N" */
    0x5f, 0x50, 0xf, 0x65, 0xfe, 0x0, 0xf6, 0x5f,
    0xf7, 0xf, 0x65, 0xf9, 0xe1, 0xf6, 0x5f, 0x2e,
    0x9f, 0x65, 0xf1, 0x6f, 0xf6, 0x5f, 0x10, 0xdf,
    0x65, 0xf1, 0x5, 0xf6,

    /* U+004F "O" */
    0x3, 0xcf, 0xc2, 0x1, 0xec, 0x6d, 0xd0, 0x6f,
    0x10, 0x3f, 0x48, 0xe0, 0x0, 0xf7, 0x8e, 0x0,
    0xf, 0x76, 0xf1, 0x3, 0xf4, 0x1e, 0xc6, 0xde,
    0x0, 0x3c, 0xfc, 0x20,

    /* U+0050 "P" */
    0x5f, 0xff, 0xc2, 0x5, 0xf6, 0x5d, 0xc0, 0x5f,
    0x10, 0x7f, 0x5, 0xf2, 0x1b, 0xe0, 0x5f, 0xff,
    0xf5, 0x5, 0xf5, 0x31, 0x0, 0x5f, 0x10, 0x0,
    0x5, 0xf1, 0x0, 0x0,

    /* U+0051 "Q" */
    0x3, 0xcf, 0xc2, 0x1, 0xfc, 0x6d, 0xd0, 0x6f,
    0x10, 0x3f, 0x49, 0xe0, 0x0, 0xf6, 0x9e, 0x0,
    0xf, 0x76, 0xf1, 0x3, 0xf4, 0x1f, 0xc6, 0xde,
    0x0, 0x3c, 0xff, 0x80, 0x0, 0x0, 0x6f, 0x20,
    0x0, 0x0, 0x10,

    /* U+0052 "R" */
    0x5f, 0xff, 0xb2, 0x5, 0xf6, 0x6e, 0xb0, 0x5f,
    0x10, 0x9d, 0x5, 0xf2, 0x1d, 0xb0, 0x5f, 0xff,
    0xe2, 0x5, 0xf5, 0xae, 0x0, 0x5f, 0x12, 0xf7,
    0x5, 0xf1, 0xa, 0xe0,

    /* U+0053 "S" */
    0x8, 0xef, 0xa0, 0x4f, 0x86, 0xf9, 0x6f, 0x20,
    0x45, 0xd, 0xfa, 0x30, 0x0, 0x6d, 0xf4, 0x57,
    0x0, 0xcb, 0x6f, 0x76, 0xea, 0x8, 0xef, 0xb1,

    /* U+0054 "T" */
    0xcf, 0xff, 0xff, 0x45, 0xcd, 0x55, 0x0, 0xad,
    0x0, 0x0, 0xad, 0x0, 0x0, 0xad, 0x0, 0x0,
    0xad, 0x0, 0x0, 0xad, 0x0, 0x0, 0xad, 0x0,

    /* U+0055 "U" */
    0x7f, 0x0, 0x7f, 0x7, 0xf0, 0x7, 0xf0, 0x7f,
    0x0, 0x7f, 0x7, 0xf0, 0x7, 0xf0, 0x7f, 0x0,
    0x7f, 0x6, 0xf1, 0x7, 0xf0, 0x2f, 0xa5, 0xeb,
    0x0, 0x5d, 0xfb, 0x10,

    /* U+0056 "V" */
    0xdc, 0x0, 0x4f, 0x58, 0xf1, 0x8, 0xf0, 0x3f,
    0x50, 0xcb, 0x0, 0xe9, 0x1f, 0x60, 0x9, 0xd5,
    0xf1, 0x0, 0x4f, 0xbc, 0x0, 0x0, 0xff, 0x70,
    0x0, 0xa, 0xf2, 0x0,

    /* U+0057 "W" */
    0xbb, 0x5, 0xf1, 0xf, 0x78, 0xe0, 0x8f, 0x42,
    0xf4, 0x5f, 0xc, 0xf8, 0x4f, 0x12, 0xf3, 0xfa,
    0xb7, 0xe0, 0xf, 0x8f, 0x3e, 0xab, 0x0, 0xbe,
    0xc0, 0xfe, 0x80, 0x8, 0xf8, 0xc, 0xf4, 0x0,
    0x5f, 0x50, 0x9f, 0x10,

    /* U+0058 "X" */
    0x9f, 0x10, 0xbe, 0x1, 0xf9, 0x3f, 0x60, 0x8,
    0xfc, 0xd0, 0x0, 0x1f, 0xf5, 0x0, 0x1, 0xff,
    0x60, 0x0, 0x9f, 0xbe, 0x0, 0x2f, 0x83, 0xf7,
    0xa, 0xf1, 0xb, 0xe0,

    /* U+0059 "Y" */
    0xcd, 0x0, 0xae, 0x4, 0xf3, 0x1f, 0x70, 0xd,
    0xa7, 0xf1, 0x0, 0x6f, 0xe8, 0x0, 0x0, 0xef,
    0x10, 0x0, 0xa, 0xd0, 0x0, 0x0, 0xad, 0x0,
    0x0, 0xa, 0xd0, 0x0,

    /* U+005A "Z" */
    0xaf, 0xff, 0xfa, 0x35, 0x58, 0xf5, 0x0, 0xd,
    0xb0, 0x0, 0x7f, 0x20, 0x1, 0xf8, 0x0, 0xb,
    0xd0, 0x0, 0x4f, 0x95, 0x53, 0xaf, 0xff, 0xfc,

    /* U+005B "[" */
    0x0, 0x6, 0xfb, 0x6f, 0x26, 0xf0, 0x6f, 0x6,
    0xf0, 0x6f, 0x6, 0xf0, 0x6f, 0x6, 0xf0, 0x6f,
    0x6, 0xfb, 0x13, 0x20,

    /* U+005C "\\" */
    0xd9, 0x0, 0x7, 0xe0, 0x0, 0x2f, 0x40, 0x0,
    0xca, 0x0, 0x6, 0xf0, 0x0, 0x1f, 0x50, 0x0,
    0xbb, 0x0, 0x6, 0xf1, 0x0, 0x8, 0x20,

    /* U+005D "]" */
    0x0, 0xf, 0xf2, 0x6f, 0x23, 0xf2, 0x3f, 0x23,
    0xf2, 0x3f, 0x23, 0xf2, 0x3f, 0x23, 0xf2, 0x3f,
    0x2f, 0xf2, 0x33, 0x0,

    /* U+005E "^" */
    0x8, 0xe0, 0x0, 0xde, 0x30, 0x3d, 0x79, 0x9,
    0x82, 0xf0,

    /* U+005F "_" */
    0x0, 0x0, 0xf, 0xff, 0xf7, 0x33, 0x33, 0x10,

    /* U+0060 "`" */
    0x5a, 0x0, 0xc7,

    /* U+0061 "a" */
    0x1b, 0xfd, 0x20, 0x5a, 0x3c, 0xb0, 0x1b, 0xef,
    0xc0, 0x8e, 0x19, 0xd0, 0x9e, 0x4d, 0xd0, 0x2d,
    0xeb, 0xe0,

    /* U+0062 "b" */
    0x7f, 0x0, 0x0, 0x7f, 0x0, 0x0, 0x7f, 0xce,
    0x60, 0x7f, 0x69, 0xf1, 0x7f, 0x2, 0xf3, 0x7f,
    0x2, 0xf3, 0x7f, 0x69, 0xf1, 0x7e, 0xbe, 0x60,

    /* U+0063 "c" */
    0x9, 0xfd, 0x36, 0xf5, 0xcc, 0x9c, 0x2, 0x49,
    0xc0, 0x1, 0x6f, 0x5b, 0xd0, 0x9f, 0xd3,

    /* U+0064 "d" */
    0x0, 0x5, 0xf1, 0x0, 0x5, 0xf1, 0xb, 0xfc,
    0xf1, 0x6f, 0x6b, 0xf1, 0x9c, 0x5, 0xf1, 0x9c,
    0x5, 0xf1, 0x6f, 0x49, 0xf1, 0xb, 0xfb, 0xf1,

    /* U+0065 "e" */
    0x8, 0xfd, 0x40, 0x5f, 0x69, 0xe0, 0x9f, 0xff,
    0xf1, 0x9e, 0x22, 0x20, 0x5f, 0x86, 0xb0, 0x8,
    0xee, 0x60,

    /* U+0066 "f" */
    0x8, 0xf8, 0xf, 0x92, 0xdf, 0xf6, 0x3f, 0x70,
    0x1f, 0x50, 0x1f, 0x50, 0x1f, 0x50, 0x1f, 0x50,

    /* U+0067 "g" */
    0xa, 0xfb, 0xf2, 0x6f, 0x69, 0xf2, 0x9c, 0x4,
    0xf2, 0x9c, 0x4, 0xf2, 0x6f, 0x69, 0xf2, 0xa,
    0xfc, 0xf2, 0x8, 0x4a, 0xf0, 0x1b, 0xfd, 0x40,

    /* U+0068 "h" */
    0x7e, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x7f, 0xbf,
    0x70, 0x7f, 0x6a, 0xf0, 0x7e, 0x5, 0xf1, 0x7e,
    0x5, 0xf1, 0x7e, 0x5, 0xf1, 0x7e, 0x5, 0xf1,

    /* U+0069 "i" */
    0x4d, 0x2, 0x80, 0x6f, 0x6, 0xf0, 0x6f, 0x6,
    0xf0, 0x6f, 0x6, 0xf0,

    /* U+006A "j" */
    0x5, 0xd0, 0x2, 0x70, 0x6, 0xf0, 0x6, 0xf0,
    0x6, 0xf0, 0x6, 0xf0, 0x6, 0xf0, 0x6, 0xf0,
    0x2a, 0xf0, 0x7f, 0x70,

    /* U+006B "k" */
    0x7f, 0x0, 0x0, 0x7f, 0x0, 0x0, 0x7f, 0xc,
    0xd0, 0x7f, 0x8f, 0x20, 0x7f, 0xf8, 0x0, 0x7f,
    0xee, 0x0, 0x7f, 0x1f, 0x80, 0x7f, 0x7, 0xf2,

    /* U+006C "l" */
    0x6f, 0x6, 0xf0, 0x6f, 0x6, 0xf0, 0x6f, 0x6,
    0xf0, 0x6f, 0x6, 0xf0,

    /* U+006D "m" */
    0x7e, 0xbe, 0x7a, 0xf8, 0x7, 0xf6, 0xbf, 0x79,
    0xf0, 0x7f, 0x6, 0xf0, 0x4f, 0x17, 0xf0, 0x6f,
    0x4, 0xf1, 0x7f, 0x6, 0xf0, 0x4f, 0x17, 0xf0,
    0x6f, 0x4, 0xf1,

    /* U+006E "n" */
    0x7e, 0xaf, 0x80, 0x7f, 0x6a, 0xf0, 0x7e, 0x5,
    0xf1, 0x7e, 0x5, 0xf1, 0x7e, 0x5, 0xf1, 0x7e,
    0x5, 0xf1,

    /* U+006F "o" */
    0x9, 0xfd, 0x40, 0x5f, 0x6a, 0xf1, 0xac, 0x2,
    0xf4, 0x9c, 0x2, 0xf4, 0x5f, 0x6a, 0xf1, 0x9,
    0xed, 0x40,

    /* U+0070 "p" */
    0x7e, 0xce, 0x60, 0x7f, 0x49, 0xf1, 0x7f, 0x2,
    0xf3, 0x7f, 0x2, 0xf3, 0x7f, 0x6a, 0xf1, 0x7f,
    0xce, 0x60, 0x7f, 0x0, 0x0, 0x7f, 0x0, 0x0,

    /* U+0071 "q" */
    0xb, 0xfa, 0xf1, 0x6f, 0x6a, 0xf1, 0x9c, 0x5,
    0xf1, 0x9c, 0x5, 0xf1, 0x6f, 0x6a, 0xf1, 0xb,
    0xfc, 0xf1, 0x0, 0x5, 0xf1, 0x0, 0x5, 0xf1,

    /* U+0072 "r" */
    0x0, 0x0, 0x7e, 0xc8, 0x7f, 0x93, 0x7f, 0x0,
    0x7f, 0x0, 0x7f, 0x0, 0x7f, 0x0,

    /* U+0073 "s" */
    0x1b, 0xfc, 0x27, 0xe3, 0xc9, 0x5f, 0xa5, 0x0,
    0x39, 0xf9, 0x9c, 0x3c, 0xb1, 0xbf, 0xd3,

    /* U+0074 "t" */
    0x18, 0x10, 0x2f, 0x30, 0xff, 0xf2, 0x4f, 0x50,
    0x2f, 0x30, 0x2f, 0x30, 0x2f, 0x80, 0xb, 0xf2,

    /* U+0075 "u" */
    0x7e, 0x5, 0xf1, 0x7e, 0x5, 0xf1, 0x7e, 0x5,
    0xf1, 0x7e, 0x5, 0xf1, 0x6f, 0x6a, 0xf1, 0x1c,
    0xfb, 0xf1,

    /* U+0076 "v" */
    0xca, 0xa, 0xd7, 0xe0, 0xd8, 0x3f, 0x4f, 0x30,
    0xec, 0xe0, 0x9, 0xfa, 0x0, 0x4f, 0x50,

    /* U+0077 "w" */
    0xb9, 0xf, 0x44, 0xf1, 0x8c, 0x3f, 0x87, 0xd0,
    0x4f, 0x7d, 0xda, 0xa0, 0x1f, 0xd5, 0xfe, 0x60,
    0xd, 0xf1, 0xbf, 0x20, 0xa, 0xc0, 0x7f, 0x0,

    /* U+0078 "x" */
    0x9e, 0xd, 0xb0, 0x1f, 0xbf, 0x30, 0x8, 0xfa,
    0x0, 0x9, 0xfb, 0x0, 0x2f, 0x9f, 0x30, 0xad,
    0xb, 0xc0,

    /* U+0079 "y" */
    0xda, 0xa, 0xd8, 0xe0, 0xe8, 0x2f, 0x6f, 0x30,
    0xde, 0xd0, 0x8, 0xf8, 0x0, 0x3f, 0x30, 0x1a,
    0xe0, 0x6, 0xf5, 0x0,

    /* U+007A "z" */
    0x9f, 0xff, 0xa2, 0x48, 0xf4, 0x1, 0xea, 0x0,
    0xae, 0x10, 0x4f, 0x84, 0x3a, 0xff, 0xfc,

    /* U+007B "{" */
    0x0, 0x80, 0x9, 0xc0, 0xd, 0x60, 0xe, 0x50,
    0x1f, 0x30, 0xcb, 0x0, 0x3f, 0x20, 0xe, 0x50,
    0xd, 0x60, 0xa, 0xa0, 0x1, 0xb0,

    /* U+007C "|" */
    0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b, 0x2b,
    0x2b, 0x14,

    /* U+007D "}" */
    0x62, 0x0, 0x7e, 0x0, 0x2f, 0x20, 0x1f, 0x30,
    0xe, 0x50, 0x6, 0xf0, 0xd, 0x80, 0x1f, 0x30,
    0x1f, 0x20, 0x6f, 0x0, 0x94, 0x0,

    /* U+007E "~" */
    0x0, 0x0, 0x0, 0xd, 0xf6, 0x4e, 0x6c, 0x5e,
    0xf8, 0x12, 0x0, 0x20
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 40, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 44, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 51, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 17, .adv_w = 95, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 92, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 74, .adv_w = 118, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 105, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 26, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 133, .adv_w = 56, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 157, .adv_w = 56, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 175, .adv_w = 73, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 188, .adv_w = 87, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 206, .adv_w = 39, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 210, .adv_w = 62, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 216, .adv_w = 46, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 60, .box_w = 5, .box_h = 9, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 242, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 92, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 45, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 42, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 495, .adv_w = 81, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 92, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 528, .adv_w = 83, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 143, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 608, .adv_w = 108, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 105, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 104, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 716, .adv_w = 90, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 88, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 820, .adv_w = 47, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 89, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 852, .adv_w = 102, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 880, .adv_w = 87, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 904, .adv_w = 140, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 940, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 968, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 996, .adv_w = 103, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1024, .adv_w = 110, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1059, .adv_w = 102, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1087, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1111, .adv_w = 99, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1135, .adv_w = 105, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1163, .adv_w = 105, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1191, .adv_w = 140, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1227, .adv_w = 102, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1255, .adv_w = 99, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1283, .adv_w = 97, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1307, .adv_w = 44, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1327, .adv_w = 68, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1350, .adv_w = 44, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1370, .adv_w = 70, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1380, .adv_w = 71, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1388, .adv_w = 53, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1391, .adv_w = 86, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1409, .adv_w = 90, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1433, .adv_w = 83, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1448, .adv_w = 90, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1472, .adv_w = 86, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1490, .adv_w = 57, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1506, .adv_w = 91, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1530, .adv_w = 90, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1554, .adv_w = 42, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1566, .adv_w = 42, .box_w = 4, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1586, .adv_w = 85, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1610, .adv_w = 42, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1622, .adv_w = 139, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1649, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1667, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1685, .adv_w = 90, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1709, .adv_w = 90, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1733, .adv_w = 58, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1747, .adv_w = 82, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1762, .adv_w = 54, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1778, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1796, .adv_w = 81, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1811, .adv_w = 118, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1835, .adv_w = 81, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1853, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1873, .adv_w = 81, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1888, .adv_w = 53, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1910, .adv_w = 40, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1920, .adv_w = 53, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1942, .adv_w = 104, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 1}
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
    -5, -3, -3, -9, -4, -5, -5, -5,
    -5, -2, -2, -7, -2, -5, -7, 1,
    -3, -3, -9, -4, -5, -5, -5, -5,
    -2, -2, -7, -2, -5, -7, 1, 2,
    3, 2, -22, -22, -22, -22, -19, -9,
    -9, -6, -2, -2, -2, -2, -9, -1,
    -6, -3, -12, -4, -4, -1, -4, -1,
    -1, -4, -3, -4, 1, -2, -2, -4,
    -2, -2, -1, -1, -10, -10, -2, -7,
    -2, -2, -3, -2, 2, -1, -1, -1,
    -1, -1, -1, -1, -1, -2, -2, -2,
    -21, -21, -15, -16, 2, -3, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2,
    1, -2, 1, -2, 1, -2, 1, -2,
    -2, -13, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -3, -5, -3,
    -22, -22, 1, -5, -5, -5, -5, -16,
    -2, -16, -7, -22, -1, -10, -4, -10,
    1, -2, 1, -2, 1, -2, 1, -2,
    -10, -10, -2, -7, -2, -2, -3, -2,
    -32, -32, -14, -14, -4, -3, -1, -1,
    -1, -1, -1, -1, -1, 1, 1, 1,
    -3, -2, -2, -3, -4, -1, -4, -5,
    -20, -21, -20, -9, -2, -2, -17, -2,
    -2, -1, 1, 1, 1, 1, -13, -7,
    -7, -7, -7, -7, -7, -16, -7, -7,
    -5, -6, -5, -6, -4, -6, -6, -5,
    -2, 2, -17, -12, -17, -6, -1, -1,
    -1, -1, 1, -4, -3, -3, -3, -3,
    -4, -3, -2, -2, -1, -1, 1, 1,
    -11, -5, -11, -3, 1, 1, -3, -2,
    -2, -2, -2, -2, -2, -2, -1, 1,
    -12, -2, -2, -2, -2, 1, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2,
    2, -4, -18, -12, -18, -12, -2, -2,
    -7, -2, -2, -1, 1, -7, 1, 1,
    1, 1, 1, -5, -5, -5, -5, -2,
    -5, -3, -3, -5, -3, -5, -3, -5,
    -2, -3, -2, -2, -2, -2, 1, 1,
    -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -1, -2, -2, -2, -1, -1,
    -1, -1, -1, -1, -2, -2, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    1, 1, 2, 1, -2, -2, -2, -2,
    -2, 1, -6, -6, -2, -2, -2, -2,
    -2, -6, -6, -6, -6, -7, -7, -1,
    -2, -1, -1, -2, -2, -1, -1, -1,
    -1, 1, 1, -14, -14, -2, -1, -1,
    -1, 2, -1, -3, -1, 4, 1, 1,
    1, -2, 1, 1, -13, -13, -1, -1,
    -1, -1, 1, -1, -1, -1, -10, -10,
    -2, -2, -2, -2, -3, -2, 1, 1,
    -13, -13, -1, -1, -1, -1, 1, -1,
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
const lv_font_t ui_font_Roboto_Bold_10 = {
#else
lv_font_t ui_font_Roboto_Bold_10 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_ROBOTO_BOLD_10*/

