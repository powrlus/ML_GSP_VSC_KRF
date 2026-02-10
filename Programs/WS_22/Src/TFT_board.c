/**
 ******************************************************************************
 * @file    TFT_board.c
 * @author  XXX
 *
 * @date    3. Feb. 2023
 *
 * @brief   Darstellung des TicTacToe Boards auf dem TFT Display des ITS Boards.
 *
 ******************************************************************************
 */
 
#include "TFT_board.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"


#define COLOR_BG			GRAY         // Hintergrundfarbe
#define COLOR_LINE		    BLACK        // Farbe der Trennlinien des Spielfelds  
#define COLOR_SP1			GREEN        // Farbe der runden Spielsteine
#define COLOR_SP2			BLUE         // Farbe der quadratischen Spielsteine

#define ZB       5                   // Breite einer Trennlinie
#define QKL      101                 // Kantenlaenge des Quadrats eines Felds des Spielbretts
#define ZL       (3*QKL + 2*ZB)      // Laenge einer Trennlinie des Spielfelds

#define U_X     83
#define U_Y     3

typedef struct {
	Coordinate topLeft;
    Coordinate bottomRight;
} Rectangle;

// Die vier Trennlinien werden als Rechtecke dargestellt. 
// Das folgende Feld enthaelt die Koordinaten dieser Rechtecke.
static Rectangle line[] = {
   {.topLeft     = {.x = U_X,                   .y = U_Y +        QKL},
    .bottomRight = {.x = U_X + ZL,              .y = U_Y +        QKL + ZB}
   },
   {.topLeft     = {.x = U_X,                   .y = U_Y + ZB + 2*QKL},
    .bottomRight = {.x = U_X + ZL,              .y = U_Y + ZB + 2*QKL + ZB} 
   }, 
   {.topLeft     = {.x = U_X + QKL,             .y = U_Y},
    .bottomRight = {.x = U_X + QKL + ZB,        .y = U_Y + ZL} 
   },   
   {.topLeft     = {.x = U_X + ZB + 2*QKL,      .y = U_Y},
    .bottomRight = {.x = U_X + ZB + 2*QKL + ZB, .y = U_Y + ZL} 
   }
};

// Die Mittelpunkte der 9 Felder des Spielbretts
static Coordinate  mp[] = {
    {.x = U_X +                QKL/2 + 1, .y = U_Y +                 QKL/2 + 1},
    {.x = U_X +                QKL/2 + 1, .y = U_Y +   (QKL + ZB) +  QKL/2 + 1},
    {.x = U_X +                QKL/2 + 1, .y = U_Y + 2*(QKL + ZB) +  QKL/2 + 1},

    {.x = U_X +   (QKL + ZB) + QKL/2 + 1, .y = U_Y +                 QKL/2 + 1},
    {.x = U_X +   (QKL + ZB) + QKL/2 + 1, .y = U_Y +   (QKL + ZB) +  QKL/2 + 1},
    {.x = U_X +   (QKL + ZB) + QKL/2 + 1, .y = U_Y + 2*(QKL + ZB) +  QKL/2 + 1},
		
    {.x = U_X + 2*(QKL + ZB) + QKL/2 + 1, .y = U_Y +                 QKL/2 + 1},
    {.x = U_X + 2*(QKL + ZB) + QKL/2 + 1, .y = U_Y +   (QKL + ZB) +  QKL/2 + 1},
    {.x = U_X + 2*(QKL + ZB) + QKL/2 + 1, .y = U_Y + 2*(QKL + ZB) +  QKL/2 + 1}};


// EOF
