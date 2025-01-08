/**
 * @file hw01_images.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-01-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __HW01_IMAGES_H__
#define __HW01_IMAGES_H__

#include "../main.h"

typedef struct {
    uint8_t w_px;
    uint8_t h_px;
    uint16_t index;
} Font_LUT;


extern const uint8_t IMAGE_CLUB[];
extern const uint8_t IMAGE_CLUB_PIXEL_WIDTH;
extern const uint8_t IMAGE_CLUB_PIXEL_HEIGHT;

extern const uint8_t IMAGE_SPADE[];
extern const uint8_t IMAGE_SPADE_PIXEL_WIDTH;
extern const uint8_t IMAGE_SPADE_PIXEL_HEIGHT;

extern const uint8_t IMAGE_HEART[];
extern const uint8_t IMAGE_HEART_PIXEL_WIDTH;
extern const uint8_t IMAGE_HEART_PIXEL_HEIGHT;

extern const uint8_t IMAGE_DIAMOND[];
extern const uint8_t IMAGE_DIAMOND_PIXEL_WIDTH;
extern const uint8_t IMAGE_DIAMOND_PIXEL_HEIGHT;

extern const uint8_t IMAGE_QUESTION[];
extern const uint8_t IMAGE_QUESTION_PIXEL_WIDTH;
extern const uint8_t IMAGE_QUESTION_PIXEL_HEIGHT;

extern const uint8_t IMAGE_GAME_OVER[];
extern const uint8_t IMAGE_GAME_OVER_PIXEL_WIDTH;
extern const uint8_t IMAGE_GAME_OVER_PIXEL_HEIGHT;

extern const uint8_t IMAGE_NUMBERS[];
extern const Font_LUT Shentox_Desc[];


#endif