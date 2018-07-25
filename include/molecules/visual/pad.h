#ifndef pad_h
#define pad_h

#include "app.h"

#define LP_FIRST_BUTTON (1)
#define LP_LAST_BUTTON  (98)

#define LP_OCTAVE_DOWN    (92)
#define LP_OCTAVE_UP      (91)
#define LP_TRANSPOSE_DOWN (93)
#define LP_TRANSPOSE_UP   (94)

#define LP_SESSION        (95)
#define LP_NOTE           (96)
#define LP_DEVICE         (97)
#define LP_USER           (98)

#define LP_SETUP          (90)
#define LP_SHIFT          (80)
#define LP_CLICK          (70)
#define LP_UNDO           (60)
#define LP_DELETE         (50)
#define LP_QUANTISE       (40)
#define LP_DUPLICATE      (30)
#define LP_DOUBLE         (20)
#define LP_RECORD         (10)

#define LP_FIRST_PLAY     (19)
#define LP_LAST_PLAY      (89)
#define LP_PLAY_GAP       (ROW_SIZE)

#define LP_RECORD_ARM     (1)
#define LP_TRACK_SELECT   (2)
#define LP_MUTE           (3)
#define LP_SOLO           (4)
#define LP_VOLUME         (5)
#define LP_PAN            (6)
#define LP_SENDS          (7)
#define LP_STOP_CLIP      (8)


/*******************************************************************************
 * Defines/helpers
 ******************************************************************************/

#define NUM_NOTES   (12)
#define MAX_NOTE    (0x7F)
#define NUM_OCTAVES (MAX_NOTE / NUM_NOTES)

#define GRID_SIZE (8)
#define ROW_GAP   (2)
#define ROW_SIZE  (GRID_SIZE + ROW_GAP)
#define FIRST_PAD (11)
#define LAST_PAD  (FIRST_PAD + GRID_SIZE * ROW_SIZE - (ROW_GAP + 1))

#define BUTTON_COUNT 100

typedef enum
{
    DIR_TL,
    DIR_UP,
    DIR_TR,
    DIR_RIGHT,
    DIR_BR,
    DIR_DOWN,
    DIR_BL,
    DIR_LEFT,
    DIR_NUM
} Direction;

u8 directional(Direction whichDir, u8 fromPad);

#endif /* pad_h */