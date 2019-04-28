/* 
 * File:   main.c
 * Author: jakecast
 *
 * Created on February 2, 2019, 12:17 PM
 */

// PIC18F4620 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic18f4620.h>
#include <time.h>

#define _XTAL_FREQ 32000000

void interrupt service_routine(int x);
void move_forward(int x, int counter_left, int counter_right);

int x = 0b00000001;
int counter_left=0;
int counter_right=0;

int main(){
    while(1){
    //enable 8MHz internal clock
    OSCCON = 0b01111100;
    //enable internal PLL clock = 32MHz
    OSCTUNE = 0b01001111;
    //set all output
    TRISA = 0x0f;
    TRISC = 0b00000000;
    INTCON = 0b11100000; //enable peripheral interrupt and TMR0 interrupt
    T0CON = 0b11000000;
    PIE1 = 0b01000000; //enable ADC interrupt
    move_forward(x, counter_left, counter_right);
    }
}
void interrupt service_routine(int x){
    
    if(TMR0IE && TMR0IF){ //if timer interrupt is enable, and flag is triggered
        counter_right++;
        counter_left++;
        TMR0IF = 0;
    }
}

void move_forward(int x, int counter_left, int counter_right){
    
int right_speed = 200; // # of interrupt triggers before you shift a bit, remembering shifting the bit moves the stepper motor 1 step
int left_speed = 200;
    if (counter_left > left_speed){
        if(x == 0b00001000){
        if(x == 0b00000001)
        x = 0b00001000;
        else
        x = x >> 1;
    }
    
    else{
        if(x == 0b00001000)
        x = 0b00000001;
        else
        x = x << 1;
    }

        LATC = x; 
        counter_left = 0;
    }

    if (counter_right > right_speed){
            if(x == 0b00001000){
        if(x == 0b00000001)
        x = 0b00001000;
        else
        x = x >> 1;
    }
    
    else{
        if(x == 0b00001000)
        x = 0b00000001;
        else
        x = x << 1;
    }

        LATC = x; 
        counter_right = 0;
    }

}
