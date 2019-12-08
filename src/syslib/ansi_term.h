#ifndef _ANSI_TERM_HEADER_
#define _ANSI_TERM_HEADER_

#include "common_datatypes.h"

#define ASCII_SHIFTIN	0x0F
#define ASCII_SHIFTOUT	0x0E

#define ANSI_P_SET_AOFF(a) (a | 0x01)
#define ANSI_P_SET_BOLD(a) (a | 0x02)
#define ANSI_P_SET_UNDR(a) (a | 0x04)
#define ANSI_P_SET_BLNK(a) (a | 0x08)
#define ANSI_P_SET_REVR(a) (a | 0x10)

#define ANSI_P_CHK_AOFF(a) (a & 0x01)
#define ANSI_P_CHK_BOLD(a) (a & 0x02)
#define ANSI_P_CHK_UNDR(a) (a & 0x04)
#define ANSI_P_CHK_BLNK(a) (a & 0x08)
#define ANSI_P_CHK_REVR(a) (a & 0x10)

typedef enum {
	ed_erase_before = 0,
	ed_erase_after = 1,
	ed_erase_all = 2
} EraseDir;

typedef enum {
	md_move_up = 0,
	md_move_down = 1,
	md_move_left = 2,
	md_move_right = 3
} ModeDir;

typedef enum {
	lm_doubleh_top = 0,
	lm_doubleh_bottom = 1,
	lm_singlew_singleh = 2,
	lm_doublew_singleh = 3
} LineMode;

void term_ANSIMode(void); 

void term_ANSIClrScrn(EraseDir dir);
void term_ANSIClrLine(EraseDir dir);
void term_ANSIDirectCursorAddr(uint8_t column, uint8_t line);
void term_ANSICursorMove(uint8_t spaces, ModeDir dir);
void term_ANSISaveCursor(void);
void term_ANSIRestoreCursor(void);
void term_ANSIIndex(void);
void term_ANSIReverseIndex(void);
void term_ANSILineMode(LineMode lm);

// prm format:
// BIT 0 -> all off
// BIT 1 -> bold on
// BIT 2 -> underscore on
// BIT 3 -> blink on
// BIT 4 -> reverse on
void term_ANSISetParam(uint8_t prm);

#endif /* _ANSI_TERM_HEADER_ */
