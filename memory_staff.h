/**
 * @file memory_staff.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __MEMORY_STAFF_H__
#define __MEMORY_STAFF_H__

#include "main.h"

#if defined(HW02A)
#include "hw01/hw01_images.h"

#define HEIGHT_IMAGE                    40
#define HEIGHT_MARGIN_TIME_TOP          2
#define HEIGHT_TIME                     30
#define HEIGHT_MARGIN_TIME_BOTTOM       3
#define HEIGHT_BOARD                    198 
#define HEIGHT_MARGIN_BOARD_BOTTOM      5
#define HEIGHT_BORDER                   8 

#define WIDTH_IMAGE                     40
#define WIDTH_MARGIN_LEFT               60
#define WIDTH_BOARD                     198 
#define WIDTH_MARGIN_RIGHT              60
#define WIDTH_BORDER                    8 

/* Macros used to determine the vertical position of the images and game board borders */
#define LOC_Y_CENTER                    (240/2)
#define LOC_Y_TIME                      (HEIGHT_MARGIN_TIME_TOP + (HEIGHT_TIME/2) - 1)

#define LOC_Y_GAME_BOARD_CENTER         (LOC_Y_TIME + (HEIGHT_TIME/2) + HEIGHT_MARGIN_BOARD_BOTTOM + (HEIGHT_BOARD/2))

#define LOC_Y_BORDER_ROW0               (LOC_Y_TIME + (HEIGHT_TIME/2) + HEIGHT_MARGIN_TIME_BOTTOM + (HEIGHT_BORDER/2)) 
#define LOC_Y_IMAGE_ROW0                (LOC_Y_BORDER_ROW0 + (HEIGHT_BORDER/2) + (HEIGHT_IMAGE/2))

#define LOC_Y_BORDER_ROW1               (LOC_Y_IMAGE_ROW0 + (HEIGHT_IMAGE/2) + (HEIGHT_BORDER/2))
#define LOC_Y_IMAGE_ROW1                (LOC_Y_BORDER_ROW1 + (HEIGHT_BORDER/2) + (HEIGHT_IMAGE/2))

#define LOC_Y_BORDER_ROW2               (LOC_Y_IMAGE_ROW1 + (HEIGHT_IMAGE/2) + (HEIGHT_BORDER/2))
#define LOC_Y_IMAGE_ROW2                (LOC_Y_BORDER_ROW2 + (HEIGHT_BORDER/2) + (HEIGHT_IMAGE/2))

#define LOC_Y_BORDER_ROW3               (LOC_Y_IMAGE_ROW2 + (HEIGHT_IMAGE/2) + (HEIGHT_BORDER/2))
#define LOC_Y_IMAGE_ROW3                (LOC_Y_BORDER_ROW3 + (HEIGHT_BORDER/2) + (HEIGHT_IMAGE/2))

#define LOC_Y_BORDER_ROW4               (LOC_Y_IMAGE_ROW3 + (HEIGHT_IMAGE/2) + (HEIGHT_BORDER/2))


/* Macros used to determine the horizontal position of the images and game board boarders */
#define LOC_X_CENTER                    (320/2)

#define LOC_X_GAME_BOARD_CENTER         (LOC_X_CENTER)

#define LOC_X_BORDER_COL0               (WIDTH_MARGIN_LEFT + (WIDTH_BORDER/2) - 1)
#define LOC_X_IMAGE_COL0                (LOC_X_BORDER_COL0 + (WIDTH_BORDER/2) + (WIDTH_IMAGE/2))

#define LOC_X_BORDER_COL1               (LOC_X_IMAGE_COL0 + (WIDTH_IMAGE/2) + (WIDTH_BORDER/2))
#define LOC_X_IMAGE_COL1                (LOC_X_BORDER_COL1 + (WIDTH_BORDER/2) + (WIDTH_IMAGE/2))

#define LOC_X_BORDER_COL2               (LOC_X_IMAGE_COL1 + (WIDTH_IMAGE/2) + (WIDTH_BORDER/2))
#define LOC_X_IMAGE_COL2                (LOC_X_BORDER_COL2 + (WIDTH_BORDER/2) + (WIDTH_IMAGE/2))

#define LOC_X_BORDER_COL3               (LOC_X_IMAGE_COL2 + (WIDTH_IMAGE/2) + (WIDTH_BORDER/2))
#define LOC_X_IMAGE_COL3                (LOC_X_BORDER_COL3 + (WIDTH_BORDER/2) + (WIDTH_IMAGE/2))

#define LOC_X_BORDER_COL4               (LOC_X_IMAGE_COL3 + (WIDTH_IMAGE/2) + (WIDTH_BORDER/2))



/*****************************************************************************/
/* REMOTE UART Command Bytes */
/*****************************************************************************/
#define REMOTE_CMD_PACKET_START 0xA0
#define REMOTE_CMD_PACKET_END 0xA1
#define REMOTE_CMD_TYPE_INIT 0xB0
#define REMOTE_CMD_TYPE_SEL 0xB1
#define REMOTE_CMD_PLAYER1_SEL 0xC0
#define REMOTE_CMD_ACK 0xD0
#define REMOTE_CMD_RESTART 0xE0   


/*****************************************************************************/
/* Valid Images */
/*****************************************************************************/
typedef enum
{
    MEM_IMAGE_CLUB = 0,
    MEM_IMAGE_SPADE = 1,
    MEM_IMAGE_HEART = 2,
    MEM_IMAGE_DIAMOND = 3,
    MEM_IMAGE_QUESTION = 4,
    MEM_IMAGE_GRID_ACTIVE = 5,
    MEM_IMAGE_GRID_INACTIVE = 6
} mem_image_t;

/*****************************************************************************/
/* Memory Game Software Events */
/*****************************************************************************/
typedef enum
{
    EVENT_NONE,
    EVENT_IPC_RX_ACK,
    EVENT_IPC_RX_PLAYER1,
    EVENT_IPC_RX_SQUARE_INIT,
    EVENT_IPC_RX_SQUARE_SEL,
} memory_event_t;

/*****************************************************************************/
/* Data Structures for Square Information */
/*****************************************************************************/
typedef enum
{
    SQUARE_STATUS_SELECTED,
    SQUARE_STATUS_NOT_SELECTED,
    SQUARE_STATUS_FOUND
} Square_Status_t;

typedef struct
{
    Square_Status_t status;
    bool active;
    uint32_t random_num;
    mem_image_t image_type;
    uint8_t row;
    uint8_t col;
    uint16_t fcolor;
    uint16_t bcolor;
} Square_t;


/*****************************************************************************/
/*  Game FSM states */
/*****************************************************************************/
typedef enum 
{
    GAME_STATE_PLAYER_SELECTION,
    GAME_STATE_INIT_SEND,
    GAME_STATE_INIT_RECEIVE,
    GAME_STATE_ACTIVE,
    GAME_STATE_WAITING, 
    GAME_STATE_GAME_OVER,
} Game_State_t;

extern cyhal_trng_t trng_obj;


void staff_draw_image(uint8_t row, uint8_t col, mem_image_t image, uint16_t fcolor, uint16_t bcolor);
void staff_randomize_images(Square_t *squares);
void staff_set_grid_color(uint16_t color);
#endif
#endif