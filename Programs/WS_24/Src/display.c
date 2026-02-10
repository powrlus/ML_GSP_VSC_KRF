/**
 ******************************************************************************
 * @file    display.c
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    22. Jan. 2025
 * @brief   Dieses Modul implementiert die LCD Ausgabe der W�rfel.
 ******************************************************************************
 */

#include "display.h"
#include "LCD_general.h"
#include "main.h"
#include "LCD_GUI.h"
#include "error.h"
#include <stddef.h>
#include <stdint.h>
#include "kniffel.h"

// Dieses Feld speichert die Positionen der W�rfel. Die Position eines W�rfels
// ist durch seine linke obere und rechte untere Ecke beschrieben.

const struct {
	 Coordinate tl;
	 Coordinate br;
	} dicePosData[NO_DICE] = { {.tl = {.x = 382, .y = 40}, .br = {.x = 465, .y = 123}},
		                         {.tl = {.x = 292, .y = 40}, .br = {.x = 375, .y = 123}},
														 {.tl = {.x = 202, .y = 40}, .br = {.x = 285, .y = 123}},
														 {.tl = {.x = 112, .y = 40}, .br = {.x = 195, .y = 123}},
														 {.tl = {.x = 22,  .y = 40}, .br = {.x = 105, .y = 123}}};

// Von der linken oberen Ecke eines W�rfels ausgehend, beschreiben folgende Konstanten 
// den Offset der Mittelpunkte der einzelnen Positionen der W�rfelaugen / W�rfelpunkte.
//
//           |-------------------------|
//           |                         |
//           |  Pos1             Pos2  |
//           |                         |
//           |  Pos3    Pos4     Pos5  |
//           |                         |
//           |  Pos6             Pos7  |
//           |                         |
//           |-------------------------|
											
const Coordinate offsetPos1 = {.x = 1 * 21, .y = 1 * 21};
const Coordinate offsetPos2 = {.x = 3 * 21, .y = 1 * 21};
const Coordinate offsetPos3 = {.x = 1 * 21, .y = 2 * 21};
const Coordinate offsetPos4 = {.x = 2 * 21, .y = 2 * 21};
const Coordinate offsetPos5 = {.x = 3 * 21, .y = 2 * 21};
const Coordinate offsetPos6 = {.x = 1 * 21, .y = 3 * 21};
const Coordinate offsetPos7 = {.x = 3 * 21, .y = 3 * 21};

#define RADIUS_DICE_EYE       6   // 
#define LINE_START_X 0
#define LINE_END_X (LCD_WIDTH - 1)
#define ROW_START_Y 0
#define ROW_END_Y (LCD_HEIGHT - 1)
#define DIE_LINEWEIGHT 1

#define POINT_COUNT 7
#define POINT_RADIUS 4
#define POINT_LINEWEIGHT 1

#define ARR_E_TO_IDX 1

static void offsetByCoord(const Coordinate* target, const Coordinate* offset, Coordinate* result) {
	result->x = (target-> x + offset->x);
	result->y = (target->y + offset->y);
}

static void displayDieValue(const Coordinate *dieTl, uint8_t value, COLOR c) {

	Coordinate pointsToDraw[POINT_COUNT];
	switch(value) {
		case 1:
			offsetByCoord(dieTl, &offsetPos4, &pointsToDraw[0]);

			for(int i = 0; i < value; i++) {
				GUI_drawCircle(pointsToDraw[i], POINT_RADIUS, c, true, POINT_LINEWEIGHT);
			}
			break;
		case 2:
			offsetByCoord(dieTl, &offsetPos2, &pointsToDraw[0]);
			offsetByCoord(dieTl, &offsetPos6, &pointsToDraw[1]);

			for(int i = 0; i < value; i++) {
				GUI_drawCircle(pointsToDraw[i], POINT_RADIUS, c, true, POINT_LINEWEIGHT);
			}
			break;
		case 3:
			offsetByCoord(dieTl, &offsetPos2, &pointsToDraw[0]);
			offsetByCoord(dieTl, &offsetPos4, &pointsToDraw[1]);
			offsetByCoord(dieTl, &offsetPos6, &pointsToDraw[3]);
			
			for(int i = 0; i < value; i++) {
				GUI_drawCircle(pointsToDraw[i], POINT_RADIUS, c, true, POINT_LINEWEIGHT);
			}
			break;
		case 4:
			offsetByCoord(dieTl, &offsetPos1, &pointsToDraw[0]);
			offsetByCoord(dieTl, &offsetPos2, &pointsToDraw[1]);
			offsetByCoord(dieTl, &offsetPos6, &pointsToDraw[2]);
			offsetByCoord(dieTl, &offsetPos7, &pointsToDraw[3]);
			
			for(int i = 0; i < value; i++) {
				GUI_drawCircle(pointsToDraw[i], POINT_RADIUS, c, true, POINT_LINEWEIGHT);
			}
			break;
		case 5:
			offsetByCoord(dieTl, &offsetPos1, &pointsToDraw[0]);
			offsetByCoord(dieTl, &offsetPos2, &pointsToDraw[1]);
			offsetByCoord(dieTl, &offsetPos4, &pointsToDraw[2]);
			offsetByCoord(dieTl, &offsetPos6, &pointsToDraw[3]);
			offsetByCoord(dieTl, &offsetPos7, &pointsToDraw[4]);

			for(int i = 0; i < value; i++) {
				GUI_drawCircle(pointsToDraw[i], POINT_RADIUS, c, true, POINT_LINEWEIGHT);
			}
			break;
		case 6:
			offsetByCoord(dieTl, &offsetPos1, &pointsToDraw[0]);
			offsetByCoord(dieTl, &offsetPos2, &pointsToDraw[1]);
			offsetByCoord(dieTl, &offsetPos3, &pointsToDraw[2]);
			offsetByCoord(dieTl, &offsetPos5, &pointsToDraw[3]);
			offsetByCoord(dieTl, &offsetPos6, &pointsToDraw[4]);
			offsetByCoord(dieTl, &offsetPos7, &pointsToDraw[5]);

			for(int i = 0; i < value; i++) {
				GUI_drawCircle(pointsToDraw[i], POINT_RADIUS, c, true, POINT_LINEWEIGHT);
			}
			break;
		default:
			Error_Handler(); // value außerhalb von gültigem Wertebereich
	}
}

void clearDisplay() {
	Coordinate screenTl = {LINE_START_X, ROW_START_Y};
	Coordinate screenBr = {LINE_END_X, ROW_END_Y};

	GUI_drawRectangle(screenTl, screenBr, BLUE, true, 1);
}

void displayDie(uint8_t die, uint8_t value, COLOR c) {
	const Coordinate dieTl = dicePosData[die].tl;
	const Coordinate dieBr = dicePosData[die].br;

	// invalid input handeling
	if (die > DIE_COUNT || die < 0) {
		Error_Handler();
	}

	if((value > DIE_MAXVAL) || (value < DIE_MINVAL)) {
		Error_Handler();
	}

	// displaying die
	
	GUI_drawRectangle(dieTl, dieBr, c, false, DIE_LINEWEIGHT);
	displayDieValue(&dieTl, value, c);
}

// EOF

