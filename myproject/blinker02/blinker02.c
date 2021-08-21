
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

#define SYST_CSR 0xE000E010     //SysTick Control and Status Register (STCSR)
#define SYST_RVR 0xE000E014     //SysTick Reload Value Register (STRVR)
#define SYST_CVR 0xE000E018     //SysTick Current Value Register
#define SYST_CALIB 0xE000E01C   //


void delay ( void )
{
    unsigned int ra;
    for(ra=0;ra<10;ra++)
    {
        while(1)
        {
            //timer reach 0,clear on read.
            if(GET32(SYST_CSR)&0x10000) break;
        }
    }
}
int notmain ( void )
{
    unsigned int ra;

    //PUT8(PADIR_L,GET8(PADIR_L)|0x01);
    PUT8(PASEL0_L,GET8(PASEL0_L)& ~0x01);
    PUT8(PASEL1_L,GET8(PASEL1_L)& ~0x01);

    PUT32(SYST_CSR,4);
    PUT32(SYST_RVR,1200000-1);
    PUT32(SYST_CVR,1200000-1);
    PUT32(SYST_CSR,5);

    ra=GET8(PAOUT_L);
    while(1)
    {
        ra^=1;
        PUT8(PAOUT_L,ra);
        delay();
        ra^=1;
        PUT8(PAOUT_L,ra);
        delay();
    }
    return(0);
}
