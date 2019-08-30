#include <stdio.h>
#include <stdlib.h>

#define SPI_TXFIFO 0x48
#define SPI_RXFIFO 0x4C

#define SPI0_BASE 0x10013000 // master
#define SPI0_REG(offset) *(uint8_t *)(SPI0_BASE + offset)
#define SPI1_BASE 0x10014000 // slave
#define SPI1_REG(offset) *(uint8_t *)(SPI1_BASE	+ offset)

int main()
{
  SPI1_REG(0x78) = 1; // enable slave mode

  SPI0_REG(0x3C) = 0;

  SPI1_REG(SPI_TXFIFO) = 0x25;
  SPI0_REG(SPI_TXFIFO) = 0x13;
  SPI1_REG(SPI_TXFIFO) = 0xA2;
  SPI0_REG(SPI_TXFIFO) = 0xB4;
  SPI1_REG(SPI_TXFIFO) = 0x0F;
  SPI0_REG(SPI_TXFIFO) = 0xF0;
  SPI1_REG(SPI_TXFIFO) = 0xF0;
  SPI0_REG(SPI_TXFIFO) = 0x0F;

  int i;
  for (i = 0; i<200; i++){ // arbitrary delay
      asm("");
  }

  if (SPI1_REG(SPI_RXFIFO) == 0x13 && SPI0_REG(SPI_RXFIFO) == 0x25){
  	if (SPI1_REG(SPI_RXFIFO) == 0xB4 && SPI0_REG(SPI_RXFIFO) == 0xA2){
      if (SPI1_REG(SPI_RXFIFO) == 0xF0 && SPI0_REG(SPI_RXFIFO) == 0x0F){
        if (SPI1_REG(SPI_RXFIFO) == 0x0F && SPI0_REG(SPI_RXFIFO) == 0xF0){
  		    return 0;
        }
      }
    }
  }
	return 1;
}
