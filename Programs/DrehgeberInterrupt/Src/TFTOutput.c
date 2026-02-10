/**
  * @file TFTOutput.c
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief This modules implements a simple output to TFT monitor.
  *        It defines one TFT terminal areas. 
  *
  */
	
#include "TFTOutput.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "output.h"
#include "terminal.h"
#include "LCD_GUI.h"
#include "fontsFLASH.h"
#include "lcd.h"

// Definition of terminal area
#define ROW_1				       2
#define ROW_2				       4
#define ROW_3				       6
#define ROW_4				       8
#define COL_1				       3
#define COL_2				       (6 + (COL_1))

#define SPACE_4_NUMBERS		    22

#define OUT_STR_SIZE          32

static Terminal term;

void setupTerm(void) {
	// For speeding up TFT display only numbers will be updated.
	Coordinate tl = {0,0};
	Coordinate br = {LCD_WIDTH-1, LCD_HEIGHT-1};
   term = genTerm(tl, br, BLUE, YELLOW, &Font16FLASH);

	setPosTerm(ROW_1, COL_1, &term);
	printTerm("Winkel [Grad] : ",   &term);
	setPosTerm(ROW_3, COL_1, &term);
	printTerm("Geschwindigkeit [Grad/s] :", &term);
   setTextColorTerm(RED, &term); // Color for numbers
}

/* Das printResults kostet die meiste Zeit aufgrund der Ansteuerung des TFT Displays
 * Die Zeit steigt in erster Naeherung linear zur Anzahl der Zeichen, die auf dem
 * Bildschirm dargestellt werden.
 *
 * Konsequenz: In jedem Durchlauf der Super Loop wird maximal ein Zeichen auf dem
 * Bildschirm ausgegeben. Somit wird die maximale Drehgeschwindigkeit erhöht, denn
 * diese wird durch die maximale Länge Durchlaufs durch die Super Loop begrenzt.
 * Diese Optimierung wird ueber folgende Prepozessor Variable aktiviert.
 */

// #define PRINT_STEP_BY_STEP     # Zeichenweise Ausgabe

static char angleBuffer[OUT_STR_SIZE] = {'\0'};
static char speedBuffer[OUT_STR_SIZE] = {'\0'};
static char *nextBufferToPrint = NULL;     // NULL : Es liegt keine neue Ausgabe vor
static int nextPosToPrint = 0;

/*
 * @brief This function extends the string end given in buf with ' '
 */
static void clearBufferEnd(char *buf, const int buf_size){
	// Fuelle den String mit Blanks auf, damit alte Werte auf der Ausgabe ueberschrieben werden
	 for(int i = 0; (i < buf_size-2); i++) {
		  if (buf[i] == '\0') {
				 buf[i] = ' '; 
				 buf[i+1] = '\0'; 
			}
	 }
}

/*
 * @brief This function converts a double to a str with one position after decimal point.
 */
static void double2str(char * buf, const int buf_size, double val){
	 char *formatStr = "%-20.1lf";
   snprintf(buf, buf_size , formatStr, val);
   // Fuelle den String mit Blanks auf, damit alte Werte auf der Ausgabe ueberschrieben werden
	 clearBufferEnd(buf, buf_size);
}

/*
 * @brief This function converts an int64_t val to a str with value val/10.
 */
static void int642str(char * buf, const int buf_size, int64_t val){
   char *formatStr = "%s%lld.%d";
	 int64_t abs_val = (val < 0) ? (-1 * val) : val;
	 if (abs_val < 0){
		  // Bereichsueberschreitung - halbherzige Loesung, faengt nur einen von wenigen Faellen ab.
		  lcdGotoXY(3,3);
      lcdPrintlnS("INTERNAL ERROR"); 
   while(1) {}
		 
	 }
   snprintf(buf, buf_size , formatStr, (val < 0) ? "-" : "", abs_val / 10, abs_val % 10);
   // Fuelle den String mit Blanks auf, damit alte Werte auf der Ausgabe ueberschrieben werden
	 clearBufferEnd(buf, buf_size);	
}

void fillResultBuffer(int64_t angle, double angularSpeed){
	int642str(angleBuffer, (sizeof(angleBuffer) < SPACE_4_NUMBERS) ? sizeof(angleBuffer) : SPACE_4_NUMBERS, angle); 
   double2str(speedBuffer, (sizeof(speedBuffer) < SPACE_4_NUMBERS) ? sizeof(speedBuffer) : SPACE_4_NUMBERS, angularSpeed);
   nextBufferToPrint = angleBuffer;
   nextPosToPrint = 0;
}

#ifdef PRINT_STEP_BY_STEP

static void printResultBufferStepByStep(void){
	if (nextBufferToPrint == NULL) { // Alle Zeichen wurden schon ausgegeben
      return;
   }
   // Geben neachsten Zeichen aus
	if (nextBufferToPrint[nextPosToPrint] == '\0'){ 
	   if (nextBufferToPrint == speedBuffer){ // alle Zeichen ausgegeben
		 	nextBufferToPrint = NULL;
			return;
		}
		nextBufferToPrint = speedBuffer;
		nextPosToPrint = 0;	 
	}   
	setPosTerm((nextBufferToPrint == angleBuffer) ? ROW_2: ROW_4, 
	            COL_2 + nextPosToPrint, &term);
	char b[] = {nextBufferToPrint[nextPosToPrint++] , '\0'};
	printTerm(b, &term);
}

void printResultBuffer(void){
	printResultBufferStepByStep();
}
#else
void printResultBuffer(void){
   if (nextBufferToPrint != NULL){
		// Neue Ausgabe liegt vor. Geben alle Zeichen auf einmal aus.
	   setPosTerm(ROW_2, COL_2, &term);
		printTerm(angleBuffer, &term);
		setPosTerm(ROW_4, COL_2, &term);
      printTerm(speedBuffer, &term);
		nextBufferToPrint = NULL;
   }
}
#endif

// EOF
