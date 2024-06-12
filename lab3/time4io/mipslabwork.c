/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
//#include </Applications/mcb32tools.app/Contents/Resources/Toolchain/include/pic32mx.h>
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    
    volatile int *trise = (volatile int *) 0xbf886100; // Pointer to TRISE register
    *trise = *trise & ~0xff; // Set bits 0 through 7 to 0 (output)
    
    TRISD |= 0x0FE0; // Port D is used Set bits 5 through 11 to 1 (input)
        
    return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  static int count = 0; /* Initialize counter to 0 */
  volatile int *porte = (volatile int *) 0xbf886110; /* Pointer to PORTE register */
    
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
    
  /* Display count on LEDs */
  *porte = count;
  /* Increment counter each time tick is called */
  count++;
  
    
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
}


