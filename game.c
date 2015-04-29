#include <stdio.h>
#include "field.h"
#include "shipPlacer.h"
//#include "computer.h"
//#include "human.h"
#include "coord.h"
#include "matrix.h"
#include "stm8s.h"
#include "stm8s_flash.h"

#define NUMBER_OF_SHIPS 10
#define EEPROM_ADRESS 0x4100

void gameMain();
void checkHumanMove();
int countAliveShipCell ();
void checkComputerMove();

//CellType cell;
//Coord c;

int computerShipKilled = 0;
//int humanShipKilled1 = 0;
int  humanShipKilled1 = 0;
u32 FLASH_ReadWord(u32 start_adr);

void main()
{
  
  CLK_DeInit();
    
    /* Clock divider to HSI/1 */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    
 
  GPIO_Configuration();
  
  
  /*Define FLASH programming time*/
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
    /* Unlock Data memory */
    FLASH_Unlock(FLASH_MEMTYPE_DATA);

    u8 rand_value;
    
        /* Read EEPROM */
    rand_value = FLASH_ReadByte(EEPROM_ADRESS);
    ++rand_value;
    /*__no_init u32 *rand_value1 = (u32 *)0x4100;
    u32 rand_value = *rand_value1 + 1;*/
    
    
    /* Program word at address 0x4100*/
    FLASH_ProgramByte(EEPROM_ADRESS, rand_value);
    
    
    
    srand(rand_value);
  
  initMatrix ();
  
  gameMain();

}

void gameMain() // game entry point
{ 

	// game main cycle
	//srand(time(NULL));
        
	
	initField();
	placeShips(COMPUTER);
        
        while (1)
        {
          fieldTOmatrix (COMPUTER);
        }
}
u32 FLASH_ReadWord(u32 start_adr)
{
  u32 word = 0x00;
  u8 memoryByte = 0x00;
  u8 i;
  
  for (i = 0; i < 4; ++i)
  {
    memoryByte = FLASH_ReadByte(start_adr);
    word |= (memoryByte << ((3-i)*8));
    start_adr += 1;
  }
  return (word);
}