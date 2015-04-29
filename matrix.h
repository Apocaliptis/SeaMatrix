#ifndef MATRIX_H
#define MATRIX_H

//#include "stm8s.h"

typedef enum
{
  /*Control signal is '0'*/
	WHITE	= ((unsigned char)0x0),	/*0b 000*/
	PINK	= ((unsigned char)0x1),	/*0b 001*/
	SKY	= ((unsigned char)0x2),	/*0b 010*/
	BLUE	= ((unsigned char)0x3),	/*0b 011*/
	YELLOW	= ((unsigned char)0x4),	/*0b 100*/
	RED	= ((unsigned char)0x5),	/*0b 101*/
	GREEN	= ((unsigned char)0x6),	/*0b 110*/
	OFF	= ((unsigned char)0x7)	/*0b 111*/
 }Colour;


void GPIO_Configuration(void);

void putINmatrix (unsigned long input);

void initMatrix(void);

void lightMYled (unsigned char x, unsigned char y, unsigned char colour);

#endif /* MATRIX_H */ 