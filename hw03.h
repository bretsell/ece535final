/**
 * @file memory.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __HW03_H__
#define __HW03_H__

#include "main.h"

#if defined(HW03A)

#include "hw01/hw01_images.h"
#include "task_console.h"
#include "task_io_expander.h"
#include "task_imu.h"
#include "task_lcd.h"
#include "task_remote_rx.h"
#include "task_remote_tx.h"
#include "task_sw.h"
#include "task_joystick.h"

#include "task_state_active.h"
#include "task_state_game_over.h"
#include "task_state_init_receive.h"
#include "task_state_init_send.h"
#include "task_state_player_sel.h"
#include "task_state_waiting.h"


#define HW03_TASK_PRIORITY_BOTTOM_HALF  6
#define HW03_TASK_PRIORITY_UI_INPUT     5
#define HW03_TASK_PRIORITY_UI_OUTPUT    4
#define HW03_TASK_PRIORITY_FSM          3


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
/* Struct used to Tx/Rx data from the Remote UART */
/*****************************************************************************/
typedef struct Remote_Uart_Data
{
    uint8_t num_bytes;
    uint8_t payload[6];
} Remote_Uart_Data_t;


/*****************************************************************************/
/* Memory Game Software Events */
/*****************************************************************************/
#define EVENT_UI_SW1                 (1 << 0)
#define EVENT_UI_SW2                 (1 << 1)
#define EVENT_UI_SW3                 (1 << 2)
#define EVENT_UI_MOVE                (1 << 3)
#define EVENT_IPC_RX_ACK             (1 << 4)
#define EVENT_IPC_RX_PLAYER1         (1 << 5)
#define EVENT_IPC_RX_RESTART         (1 << 6)

/*****************************************************************************/
/* Data Structures for Square Information */
/*****************************************************************************/

/*****************************************************************************/
/* Valid Images */
/*****************************************************************************/
typedef enum
{
    MEM_IMAGE_CLUB,             /* CLUB image */
    MEM_IMAGE_SPADE,            /* SPADE image */
    MEM_IMAGE_HEART,            /* HEART image */
    MEM_IMAGE_DIAMOND,          /* DIAMOND image */
    MEM_IMAGE_QUESTION,         /* QUESTION image */
    MEM_IMAGE_GRID_ACTIVE,      /* Orange Grid */
    MEM_IMAGE_GRID_INACTIVE,    /* Grey Grid */
    MEM_IMAGE_GAME_OVER,        /* GAME OVER image */
    MEM_IMAGE_LCD_RESET         /* Clear the entire LCD */
} mem_image_t;


/*****************************************************************************/
/* Structs used to hold information about each square */
/*****************************************************************************/
typedef enum
{
    SQUARE_STATUS_SELECTED,         /* The square is selected */
    SQUARE_STATUS_NOT_SELECTED,     /* The square is not selected */
    SQUARE_STATUS_FOUND             /* The square has been matched with another square*/
} Square_Status_t;

typedef struct
{
    Square_Status_t status;         /* See Square_Status_t struct*/
    bool active;                    /* Is this square the active square*/
    uint32_t random_num;            /* Used for randomizing the images */
    mem_image_t image_type;         /* Image located at this square */
    uint8_t row;                    /* Row Coordinate of the square */
    uint8_t col;                    /* Column Coordinate of the square */
    uint16_t fcolor;                /* Foreground color of image */
    uint16_t bcolor;                /* Background color of image */
} Square_t;

/*****************************************************************************/
/* Enum for the direction the active square can move */
/*****************************************************************************/
typedef enum
{
    DIR_CENTER,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
} Direction_t;


/* Event Groups */
extern EventGroupHandle_t eg_UI;

/* Queues */
extern QueueHandle_t q_Squares;
extern QueueHandle_t q_Dir;

/* Global variables used for the memory game */
extern cyhal_trng_t trng_obj;
extern Square_t Game_Board[4][4];
extern Square_t Images[16];
extern uint8_t Row;
extern uint8_t Col;
extern uint8_t Score;
extern char STUDENTS[];

#endif
#endif
