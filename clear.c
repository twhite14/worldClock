//clar.c
//Version 0.1
//Clear a set of LED displays.
#include <wiringPi.h>
#include <unistd.h>

void shiftRegisterWrite(int, int, unsigned short);

int main()
{
    wiringPiSetup();

    int clkPin = 2;
    int datPin = 0;
    int latPin = 3;

    pinMode(clkPin, OUTPUT);
    pinMode(datPin, OUTPUT);
    pinMode(latPin, OUTPUT);

    int i = 0;
    for(i = 0; i < 24; i++)
        shiftRegisterWrite(clkPin, datPin, 0x0000);
    digitalWrite(latPin, 1);
    usleep(10);
    digitalWrite(latPin, 0);

}
void shiftRegisterWrite(int clkPin, int datPin, unsigned short data)
{
    int i = 0;
    int dataValue = 0;
    for(i = 0; i < 16; i++)
    {
        dataValue = data & (1 << (15 - i)) ;
        digitalWrite(datPin, dataValue);
        usleep(10);
        digitalWrite(clkPin, 1);
        usleep(10);
        digitalWrite(clkPin, 0);
        usleep(10);
    }
}
