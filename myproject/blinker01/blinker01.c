#include <stdint.h>

void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void PUT8 ( unsigned int, unsigned int );
unsigned int GET8 ( unsigned int );
void PUT16 ( unsigned int, unsigned int );
unsigned int GET16 ( unsigned int );
void dummy ( unsigned int );

#define PORT_BASE 0x40004C00

#define PAOUT PAOUT_L
#define PAOUT_L (PORT_BASE+0x02)
#define PAOUT_H (PORT_BASE+0x03)
#define PADIR PADIR_L
#define PADIR_L (PORT_BASE+0x04)
#define PADIR_H (PORT_BASE+0x05)

#define PASEL0 PASEL0_L
#define PASEL0_L (PORT_BASE+0x0a)
#define PASEL0_H (PORT_BASE+0x0b)
#define PASEL1 PASEL1_L
#define PASEL1_L (PORT_BASE+0x0c)
#define PASEL1_H (PORT_BASE+0x0d)

#define DELAY_COUNT 200000

void delay ( unsigned int x )
{
    while(x--) dummy(x);
}
int notmain ( void )
{
    //set P1.0 as output
    PUT8(PASEL0_L,GET8(PASEL0_L)& ~0x01);
    //PUT8(PASEL0_H,GET8(PASEL0_H)|0x01);
    PUT8(PASEL1_L,GET8(PASEL1_L)& ~0x01);
    //PUT8(PASEL1_H,GET8(PASEL1_H)|0x01);

    unsigned int ra;

    PUT8(PADIR_L,GET8(PADIR_L)|0x01);
    ra=GET8(PAOUT_L);
    while(1)
    {
        ra^=1;
        PUT8(PAOUT_L,ra);
        delay(DELAY_COUNT);
        ra^=1;
        PUT8(PAOUT_L,ra);
        delay(DELAY_COUNT);
    }
    return(0);
}
