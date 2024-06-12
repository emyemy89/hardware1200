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

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    //1/80.000.000 -> 256/80.000.000 -> 100ms = 31.250
      T2CON = 0x8070; //set 15th bit is set to 1 , setting the prescaler to 1:256, and all other bits are 0.
      PR2 = 31250;//set period register
      TMR2 = 0; //start timer counter from 0
    
    volatile int *trise = (volatile int *) 0xbf886100; // Pointer to TRISE register
        *trise = *trise & ~0xff; // Set bits 0 through 7 to 0 (output)
    TRISD |= 0x0FE0; // Port D is used set bits 5 through 11 to 1 (input)
      return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
    
    static int count = 0; /* Initialize counter to 0 */
    volatile int *porte = (volatile int *) 0xbf886110; /* Pointer to PORTE register */
    
    
    
    int btns = getbtns();

        // If any button is pressed, update mytime
        if (btns != 0) {
            int sw = getsw(); // Get the status of the switches
            if (btns & 0x4) { // If BTN4 is pressed
                mytime = (mytime & 0x0FFF) | (sw << 12); // Update the first digit of mytime
            }
            if (btns & 0x2) { // If BTN3 is pressed
                mytime = (mytime & 0xF0FF) | (sw << 8); // Update the second digit of mytime
            }
            if (btns & 0x1) { // If BTN2 is pressed
                mytime = (mytime & 0xFF0F) | (sw << 4); // Update the third digit of mytime
            }
        }
    
    
    // IFS(0) = 0;
      if(IFS(0) & (1<<8)) //checks the 8th bit of the Interrupt Flag Status register (IFS(0))if it caused an interrupt
      {
        timeoutcount++; //incrememnt timeout
        IFS(0) = 0;    //clears the interrupt flag
      }
      if(timeoutcount >= 10)   //each increment of timeoutcount represents a 100 ms timeout, a timeoutcount of 10 represents a 1-second timeout
      {
        timeoutcount = 0;
        time2string( textstring, mytime );
        display_string( 3, textstring );
        display_update();
        tick( &mytime );
        display_image(96, icon);
          
          /* Display count on LEDs */
         *porte = count;
          /* Increment counter each time tick is called */
         count++;
      }
    
    
}
