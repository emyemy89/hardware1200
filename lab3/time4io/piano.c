#include <pic32mx.h> // This includes the necessary definitions for the PIC32


// Define the buttons for the notes
#define NUM_BUTTONS 2
#define tonePin LATDbits.LATD0 // Buzzer connected to RD0
int buttons[NUM_BUTTONS] = {2,3};

void delay_us(unsigned int microseconds) {
    // Assuming a clock speed of 80 MHz
    unsigned int ticks = microseconds * 80; // 1 microsecond is 80 clock cycles at 80 MHz

    while(ticks--) {
        asm volatile ("nop"); // 'nop' is a machine instruction that does nothing and takes one clock cycle
    }
}

void playTone(int tone, int duration) {

    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        LATD |= 0x01; // Set RD0 high
        __delay_us(tone);
        LATD &= ~0x01; // Set RD0 low
        __delay_us(tone);
    }
}


int getbtns(void){
    int buttons=PORTD;  //read from the buttons
    buttons=buttons >> 5;//shift 5 digits so that btn2 corresponds to LSB
    buttons=buttons & 0x3; //keep only the last 2 LSB
    return buttons;
    
}

void setup() {
  // Set up the buzzer output
  TRISD &= 0xfffe;
}

void loop() {
  // put your main code here, to run repeatedly:
  int btns = getbtns();
        // If any button is pressed, update mytime
        if (btns != 0) {
            if (btns & 0x2) { // If BTN3 is pressed
                playTone(1000, 500); // Play tone of 1000 Hz for 500 ms
                delay_ms(500); // Delay of 500 ms
            }
            if (btns & 0x1) { // If BTN2 is pressed
               playTone(2000, 500); // Play tone of 2000 Hz for 500 ms
               delay_ms(500); // Delay of 500 ms
            }
        }
}

int main(void) {
    setup();
    while(1) {
        loop();
    }
}
