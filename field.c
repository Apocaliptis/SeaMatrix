#include "field.h"
#include "stringOperations.h"
#include "coord.h"
#include <string.h>
#include <stdio.h>
#include "matrix.h"

// template
#define EMPTY_CELL_SYMB "*"
#define CHECKED_CELL_SYMB "-"
#define SHIP_CELL_SYMB "O"
#define KILLED_SHIP_CELL_SYMB "X"
#define UNDEFINED_CELL_SYMB "U"


//#define FIELD_LENGTH 6
#define COMPUTER_NAME "Computer"
#define PLANAR(X,Y) (X + Y * FIELD_LENGTH)

#define TEMPLATE_FIELD_SIZE 4096

void prepareTemplate();
void emptyField();


// data models
CellType computerField[FIELD_LENGTH][FIELD_LENGTH];
CellType humanField[FIELD_LENGTH][FIELD_LENGTH];

// fields store pointers to fields
CellType *fields[2] = {(CellType*)computerField, (CellType*)humanField};

void renderField(Player p);

char *str_replace(char *orig, char *rep, char *with);
void rep(char *orig, char *rep, char *with);	

char templateField[TEMPLATE_FIELD_SIZE];
char renderedField[TEMPLATE_FIELD_SIZE];

void emptyFieldByPlayer(Player p){
	
	CellType *field = fields[(int)p]; // select field


	int i,j;
	for (i=0;i<FIELD_LENGTH;++i) {
		for (j=0;j<FIELD_LENGTH;++j) {
			field[PLANAR(i,j)] = EMPTY_CELL;
		}
	}
}

void emptyField() {
	emptyFieldByPlayer(HUMAN);
	emptyFieldByPlayer(COMPUTER);
}

void setShipCell(Player p, int x, int y) {
	CellType *field = fields[(int)p]; // select field
	field[PLANAR(x,y)] = SHIP_CELL;
}

CellType check(Player p, int x, int y) {
	CellType *field = fields[(int)p]; // select field
	if (field[PLANAR(x,y)] == EMPTY_CELL) {
		return EMPTY_CELL;
	}
	else if (field[PLANAR(x,y)] == CHECKED_CELL) {
		return CHECKED_CELL;
	}
	else if (field[PLANAR(x,y)] == SHIP_CELL) {
		return SHIP_CELL;
	}
	else if (field[PLANAR(x,y)] == KILLED_SHIP_CELL) {
		return KILLED_SHIP_CELL;
	}
	
	return UNKNOWN_CELL_TYPE;
}

CellType shoot(Player p, int x, int y) {
	CellType *field = fields[(int)p]; // select field

	// shoot logic

	if (field[PLANAR(x,y)] == EMPTY_CELL) { // empty
		field[PLANAR(x,y)] = CHECKED_CELL;
		return EMPTY_CELL;
	}
	else if (field[PLANAR(x,y)] == CHECKED_CELL) { // checked
		return CHECKED_CELL;
	}
	else if (field[PLANAR(x,y)] == SHIP_CELL) { // ship
		field[PLANAR(x,y)] = KILLED_SHIP_CELL;
		return SHIP_CELL;
	}
	else if (field[PLANAR(x,y)] == KILLED_SHIP_CELL) { // killed ship
		return KILLED_SHIP_CELL;
	}
	else {
		return UNKNOWN_CELL_TYPE;
	}
}

void printField() { 

	memcpy(renderedField, templateField, sizeof(renderedField));

	renderField(COMPUTER);
	renderField(HUMAN);
	
	printf("\n\n%s\n\n\n\n", renderedField);

}

char* cellToStr(Player p, int cell) {

	if (cell == EMPTY_CELL) {
		return EMPTY_CELL_SYMB;
	}
	else if (cell == CHECKED_CELL) {
		return CHECKED_CELL_SYMB;
	}
	else if (cell == SHIP_CELL) {
		if (p == COMPUTER) { // hide computer ships
			return EMPTY_CELL_SYMB;
		}
		return SHIP_CELL_SYMB;
	}
	else if (cell == KILLED_SHIP_CELL) {
		return KILLED_SHIP_CELL_SYMB;
	}

	return UNDEFINED_CELL_SYMB;
}

void renderField(Player p) {
	CellType *field = fields[(int)p]; // select field

	char fieldEnumerator[4];
	char playerId[3] = "cp"; // for field enumerator {COMPUTER, HUMAN}
	fieldEnumerator[0] = playerId[(int)p];

	int i,j;
	char fieldVerticalHelper = '0';
	char fieldHorizontalHelper;

	for (i=0;i<FIELD_LENGTH;++i) {
		fieldEnumerator[1] = fieldVerticalHelper++;
		fieldHorizontalHelper = 'a';
		for (j=0;j<FIELD_LENGTH;++j) {
			fieldEnumerator[2] = fieldHorizontalHelper++;
			fieldEnumerator[3] = '\0';
			rep(renderedField, fieldEnumerator, cellToStr(p, field[PLANAR(j,i)]));
		}
	}
}

void initField() {


	emptyField();
}





// string operations
void rep(char *orig, char *rep, char *with) {
	char *p = str_replace(orig, rep, with);
	strncpy(renderedField, p, strlen(orig));	
}

void fieldTOmatrix (Player p)
{
	CellType *field = fields[(int)p]; // select field
	unsigned long matrixColumn = 0;
	unsigned long anod, greenColour, redColour, blueColour;
	//unsigned char tmp;

	char i, j;

	for (i = 0; i < FIELD_LENGTH; ++i)
	{
		greenColour = 0xFF;
		redColour = 0xFF;
		blueColour = 0xFF;
		anod = 0xFF;

		for (j = 0; j < FIELD_LENGTH; ++j)
		{
			//tmp = field[PLANAR(j,i)];

		 /*set up green colour*/
  			
			if (field[PLANAR(i,j)] == CHECKED_CELL)
				greenColour &= ~(1 << j);
			  
		/*set up red colour*/
			
			if (field[PLANAR(i,j)] == KILLED_SHIP_CELL)
				redColour &= ~(1 << j);
			  
		/*set up blue colour*/
			
			if (field[PLANAR(i,j)] == SHIP_CELL)
				blueColour &= ~(1 << j);	
		}

			/*set up anod output in coord. y*/
  		
  		anod &= ~(1 << i);
  		
  		matrixColumn = anod + (greenColour << 8 ) + (redColour << 16) + (blueColour << 24);

  		putINmatrix (matrixColumn);


	}
		
	//field[PLANAR(j,i)];

}

