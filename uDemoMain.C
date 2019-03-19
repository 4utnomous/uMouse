int main(int argc, char** argv) {
OSCCON = 0b01111100; //enable 8MHz internal clock
OSCTUNE = 0b01001111;//enable internal PLL clock = 32MHz
ADCON1 = 0b00001010; //configures A/D clock source, acquisition time
ADCON2 = 0b10001010;
/*
TRISx handles setting pins to I/O, 1 = in, 0 = out
TRIS is for setting output pins on chip for motors
LATx handles outputting logic signals, 1 = logic
LAT is used for driving motors, digital

PORTx checks an input, used for it statements
Remember to 0 conditions before/after loop
*/
TRISC = 0b00000000; // motors output
    if(PORTDbits.RD0 == 1){
        startup (3,500);
        delay (1000);
        LATB = 0b00000011;
        delay (1000);
        LATB = 0b00000000;
    }

    if(PORTDbits.RD0 == 1){
        driveForward(96,15); //change dist as needed
        driveForward(96,10); //change dist as needed
    }

    int x = 0b00000001;

    while(PORTDbits.RD0 == 1) {
        LATB = 0b00000001;
        LATC = 0b00000001;
        delay(20);
        LATC = 0b00000010;
        delay(20);
        LATC = 0b00000100;
        delay(20);
        LATC = 0b00001000;
        delay(20);
    }
    LATB = 0b00000000;
    LATC = 0b00000000;
    delay(1500);
}

// Driving forward function, have to consider distance eventually
void driveForward (unsigned int dist, unsigned int speed, unsigned int speed1) {
int x = 0;
for (x = 0; x <= dist; x++) {
    LATC = 0b00010000;
    delay(speed1);

    LATC = 0b00000001;
    delay(speed);

    LATC = 0b00100000;
    delay(speed1);

    LATC = 0b00000010;
    delay(speed);

    LATC = 0b01000000;
    delay(speed1);

    LATC = 0b00000100;
    delay(speed);

    LATC = 0b10000000;
    delay(speed1);

    LATC = 0b00001000;
    delay(speed);

    }
LATC = 0b00000000;
}