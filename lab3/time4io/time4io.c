//
//  time4io.c
//  
//
//  Created by Emi Paraschiv on 05.02.2024.
//

#include <stdio.h>
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw( void ){
    int switches = PORTD; // Read the state of the switches
        switches = switches >> 8; // Shift right 8 places so that SW1 corresponds to the least significant bit
        switches = switches & 0xF; // Mask all bits except the four least significant bits
        return switches;
}

int getbtns(void){
    int buttons=PORTD;  //read from the buttons
    buttons=buttons >> 5;//shift 5 digits so that btn2 corresponds to LSB
    buttons=buttons & 0x7; //keep only the last 3 LSB
    return buttons;
    
}


int getbtns(void){
    int buttons234=PORTD;  //read from the buttons
    buttons234=buttons234 >> 5;//shift 5 digits so that btn2 corresponds to LSB
    buttons234=buttons234 & 0x7; //keep only the last 3 LSB
    int button1=PORTF;
    button1=button1>>1;
    button1=button1 & 0x1;
    int buttons;
    buttons=(buttons234<<1) | button1;
    return buttons;
    
}


