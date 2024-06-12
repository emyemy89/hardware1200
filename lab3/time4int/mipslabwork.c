/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */


int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";
int timeoutcount = 0;
int prime = 1234567;

/* Interrupt Service Routine */
void user_isr( void )
{
    if(IFS(0) & (1<<8)) { // Acknowledge interrupts from Timer 2
            IFS(0) = 0; // Clear the interrupt flag
            timeoutcount++; // Increment timeoutcount
            if(timeoutcount >= 10) { // Check if timeoutcount has reached 10
                timeoutcount = 0; // Reset timeoutcount
                time2string( textstring, mytime );
                display_string( 3, textstring );
                display_update();
                tick( &mytime );
            }
        }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    
    //1/80.000.000 -> 256/80.000.000 -> 100ms = 31.250
      T2CON = 0x8070; //0x8070 corresponds to a binary value where the 15th bit is set to 1 ,setting the prescaler to 1:256,all other bits are 0.
      PR2 = 31250;//set perios register
      TMR2 = 0; //start timer counter from 0
    

    // Enable interrupts from Timer 2 without affecting other bits
        IEC(0) |= 1 << 8;//enabling interrupts from Timer 2. IEC(0) is the Interrupt Enable Control Register. The bit 8 of this register corresponds to Timer 2

        
        IPC(2) |= 31;//setting the priority of Timer 2 interrupt to the highest. IPC(2) is the Interrupt Priority Control Register.  11111 is 31 in binary.

        // Clear all interrupt flags
        IFS(0) = 0;//clearing all interrupt flags in IFS(0)

        // Enable interrupts globally
        enable_interrupt();
        return;

}

/* This function is called repetitively from the main program */
void labwork( void )
{
    prime = nextprime( prime );
     display_string( 0, itoaconv( prime ) );
     display_update();
}
