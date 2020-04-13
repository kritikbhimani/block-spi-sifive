#include <stdio.h>
#include <stdlib.h>

#define TXDATA 0
#define RXDATA 4
#define TXCTRL 8
#define RXCTRL 12
#define IE 16
#define DIV 24
#define PARITY 28
#define WIRE4 32
#define EITHER8OR9 36

#define UART_BASE 0x10013000
#define UART_REG(offset) *(uint8_t *)(UART_BASE + offset)
#define UART_REG32(offset) *(uint32_t *)(UART_BASE + offset)

static inline void tx(uint32_t txdata) 
{
  UART_REG32(TXDATA) = txdata;
}

static inline uint32_t rx() 
{
  return UART_REG32(RXDATA);
}

int main()
{
  int fail = 1;

  UART_REG32(DIV) = 19; // override default
  UART_REG32(TXCTRL) = 3 | (3 << 16); // enable tx and nstop = 1
  UART_REG32(RXCTRL) = 1; // enable rx
  UART_REG32(IE) = 0;
  UART_REG32(PARITY) = 3; // enable parity
  UART_REG32(WIRE4) = 1;
//  * (uart_base + 0x8) = 0x1;

  tx(0x61); // send tx data

  int i;
  while ( (i = rx()) >> 8 );
  if ((UART_REG32(PARITY) == 0x3) && (i == 0x61)) {
    tx(0x62);
    tx(0xFF);
    tx(0x64);
    tx(0x65);
    tx(0x66);
    tx(0x67);
    tx(0x68);
    tx(0x69);
    while ( (i = rx()) >> 8 );
    if (i == 0x62) {
      while ( (i = rx()) >> 8 );
      if (i == 0xFF) {
        while ( (i = rx()) >> 8 );
        if (i == 0x64) {
          while ( (i = rx()) >> 8 );
          if (i == 0x65) {
            while ( (i = rx()) >> 8 );
            if (i == 0x66) {
              while ( (i = rx()) >> 8 );
              if (i == 0x67) {
                while ( (i = rx()) >> 8 );
                if (i == 0x68) {
                  while ( (i = rx()) >> 8 );
                  if (((UART_REG32(PARITY)) == 0x3) && (i == 0x69)) {
                    goto test2;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
goto finish;

test2: 
//* (uart_base + 0x8) = 0x0;
UART_REG32(PARITY) = 0;
for (i = 0; i<8; i++)
  tx(0x62 + i);
while ( (i = rx()) >> 8 );
if (i == 0x62) {
  while ( (i = rx()) >> 8 );
  if (i == 0x63) {
    while ( (i = rx()) >> 8 );
    if (i == 0x64) {
      while ( (i = rx()) >> 8 );
      if (i == 0x65) {
        while ( (i = rx()) >> 8 );
        if (i == 0x66) {
          while ( (i = rx()) >> 8 );
          if (i == 0x67) {
            while ( (i = rx()) >> 8 );
            if (i == 0x68) {
              while ( (i = rx()) >> 8 );
              if (i == 0x69) {
              //  fail = 0;
                goto test3;
              }
            }
          }
        }
      }
    }
  }
}

goto finish;

test3:
//* (uart_base + 0x8) = 0x0;
UART_REG32(PARITY) = 1;
for (i = 0; i<8; i++)
  tx(0x62 + i);
while ( (i = rx()) >> 8 );
if (i == 0x62) {
  while ( (i = rx()) >> 8 );
  if (i == 0x63) {
    while ( (i = rx()) >> 8 );
    if (i == 0x64) {
      while ( (i = rx()) >> 8 );
      if (i == 0x65) {
        while ( (i = rx()) >> 8 );
        if (i == 0x66) {
          while ( (i = rx()) >> 8 );
          if (i == 0x67) {
            while ( (i = rx()) >> 8 );
            if (i == 0x68) {
              while ( (i = rx()) >> 8 );
              if ((UART_REG32(PARITY) == 0x1) && (i == 0x69)) {
              //  fail = 0;
                goto test4;
              }
            }
          }
        }
      }
    }
  }
}  

goto finish;

test4: 
//* (uart_base + 0x8) = 0x0;
UART_REG32(PARITY) = 0;
for (i = 0; i<8; i++)
  tx(0x62 + i);
while ( (i = rx()) >> 8 );
if (i == 0x62) {
  while ( (i = rx()) >> 8 );
  if (i == 0x63) {
    while ( (i = rx()) >> 8 );
    if (i == 0x64) {
      while ( (i = rx()) >> 8 );
      if (i == 0x65) {
        while ( (i = rx()) >> 8 );
        if (i == 0x66) {
          while ( (i = rx()) >> 8 );
          if (i == 0x67) {
            while ( (i = rx()) >> 8 );
            if (i == 0x68) {
              while ( (i = rx()) >> 8 );
              if (i == 0x69) {
              //  fail = 0;
                goto test5;
              }
            }
          }
        }
      }
    }
  }
}

goto finish;

test5:
//* (uart_base + 0x8) = 0x0;
UART_REG32(EITHER8OR9) = 0;
tx(0x62);
tx(0x63);
tx(0x0164);
tx(0x65);
tx(0x66);
tx(0x167);
tx(0x68);
tx(0x169);
while ( (i = rx()) >> 9 );
if (i == 0x62) {
  while ( (i = rx()) >> 9 );
  if (i == 0x63) {
    while ( (i = rx()) >> 9 );
    if (i == 0x164) {
      while ( (i = rx()) >> 9 );
      if (i == 0x65) {
        while ( (i = rx()) >> 9 );
        if (i == 0x66) {
          while ( (i = rx()) >> 9 );
          if (i == 0x167) {
            while ( (i = rx()) >> 9 );
            if (i == 0x68) {
              while ( (i = rx()) >> 9 );
              if (i == 0x169) {
                //  fail = 0;
                goto test6;
              }
            }
          }
        }
      }
    }
  }
}

goto finish;

test6:
UART_REG32(PARITY) = 1;
tx(0x62);
tx(0x63);
tx(0x0164);
tx(0x65);
tx(0x66);
tx(0x167);
tx(0x68);
tx(0x169);
while ( (i = rx()) >> 9 );
if (i == 0x62) {
  while ( (i = rx()) >> 9 );
  if (i == 0x63) {
    while ( (i = rx()) >> 9 );
    if (i == 0x164) {
      while ( (i = rx()) >> 9 );
      if (i == 0x65) {
        while ( (i = rx()) >> 9 );
        if (i == 0x66) {
          while ( (i = rx()) >> 9 );
          if (i == 0x167) {
            while ( (i = rx()) >> 9 );
            if (i == 0x68) {
              while ( (i = rx()) >> 9 );
              if ((UART_REG32(PARITY) == 1) && (i == 0x169)) {
                //  fail = 0;
                goto test7;
              }
            }
          }
        }
      }
    }
  }
}

goto finish;

test7:
UART_REG32(PARITY) = 3;
tx(0x62);
tx(0x63);
tx(0x0164);
tx(0x65);
tx(0x66);
tx(0x167);
tx(0x68);
tx(0x169);
while ( (i = rx()) >> 9);
if (i == 0x62) {
  while ( (i = rx()) >> 9 );
  if (i == 0x63) {
    while ( (i = rx()) >> 9 );
    if (i == 0x164) {
      while ( (i = rx()) >> 9 );
      if (i == 0x65) {
        while ( (i = rx()) >> 9 );
        if (i == 0x66) {
          while ( (i = rx()) >> 9 );
          if (i == 0x167) {
            while ( (i = rx()) >> 9 );
            if (i == 0x68) {
              while ( (i = rx()) >> 9 );
              if ((UART_REG32(PARITY) == 3) && (i == 0x169)) {
                fail = 0;
              }
            }
          }
        }
      }
    }
  }
}

finish:
  return fail;
}
