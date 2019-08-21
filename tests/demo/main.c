#include <stdio.h>
#include <stdlib.h>

int main()
{
  // read/write to axi block
  volatile uint32_t * master = (uint32_t *) 0x10013000;
  volatile uint32_t * slave = (uint32_t *) 0x10014000;

  *(slave + (0x78 >> 2)) = 1;

  *(master + (0x3c >> 2)) = 0x0;
  *(slave + (0x48 >> 2)) = 0x25;
  *(master + (0x48 >> 2)) = 0x13;
  *(slave + (0x48 >> 2)) = 0xA2;
  *(master + (0x48 >> 2)) = 0xB4;
  *(slave + (0x48 >> 2)) = 0x0F;
  *(master + (0x48 >> 2)) = 0xF0;
  *(slave + (0x48 >> 2)) = 0xF0;
  *(master + (0x48 >> 2)) = 0x0F;

  int i;
  for (i = 0; i<200; i++){
      asm("");
  }

  if ((*(slave + (0x4c >> 2)) == 0x13) && (*(master + (0x4c >> 2)) == 0x25)){
  	if ((*(slave + (0x4c >> 2)) == 0xB4) && (*(master + (0x4c >> 2)) == 0xA2)){
      if ((*(slave + (0x4c >> 2)) == 0xF0) && (*(master + (0x4c >> 2)) == 0x0F)){
        if ((*(slave + (0x4c >> 2)) == 0x0F) && (*(master + (0x4c >> 2)) == 0xF0)){
  		    return 0;
        }
      }
    }
  }
	return 1;
}