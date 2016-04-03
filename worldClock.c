//worldClock.c
//Version 0.2
//Driving a set of LED displays with the current time in different areas of the world.
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>

//Lookup table to convert ascii to the appropriate 7-segment output (for use on the time displays)
const char asciiTo7Seg[128] =
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//32 (mostly numbers)
0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x04,
0x9C, 0xF0, 0x00, 0x00, 0x08, 0x02, 0x01, 0x4A,
0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0,
0xFE, 0xF6, 0x00, 0x00, 0x00, 0x12, 0x00, 0xE4,
//64 (uppercase letters)
0x00, 0xEE, 0x3E, 0x9C, 0x7A, 0x9E, 0x8E, 0xBE,
0x6E, 0x60, 0x78, 0xAE, 0x1C, 0xEC, 0x2A, 0xFC,
0xCE, 0xE6, 0x8C, 0xB6, 0x1E, 0xFC, 0x38, 0x7E,
0x6E, 0x76, 0xDA, 0x9C, 0x26, 0xF0, 0x00, 0x10,
//96 (lowercase letters (actually a copy of uppercase letters))
0x80, 0xEE, 0x3E, 0x9C, 0x7A, 0x9E, 0x8E, 0xBE,
0x6E, 0x60, 0x78, 0xAE, 0x1C, 0xEC, 0x2A, 0xFC,
0xCE, 0xE6, 0x8C, 0xB6, 0x1E, 0xFC, 0x38, 0x7E,
0x6E, 0x76, 0xDA, 0x9C, 0x0C, 0xF0, 0x02, 0x00,
};

//Lookup table to convert ascii to the appropriate 16-segment output (for use on the time zone displays)
const unsigned short asciiTo16Seg[128] =
{
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF,
//32 (mostly numbers)
0x0000, 0x0110, 0x0044, 0x00F2, 0x9797, 0xB5B5, 0x2F2B, 0x0008,
0x0820, 0x2008, 0xB8B8, 0x9090, 0x2000, 0x8080, 0x0200, 0x2020,
0x4747, 0x0440, 0xC3C3, 0x87C3, 0x84C4, 0x8787, 0xC787, 0x2023,
0xC7C7, 0x84C7, 0x0201, 0x2001, 0x0820, 0x8083, 0x2008, 0x10C7,
//64 (uppercase letters)
0xDF47, 0xC4C7, 0xC7C7, 0x4307, 0x4747, 0xC307, 0xC007, 0x4787,
0xC4C4, 0x1313, 0x5213, 0xC824, 0x4304, 0x446C, 0x4C4C, 0x4747,
0xC0C7, 0x4F47, 0xC8C7, 0x8787, 0x1013, 0x4744, 0x6024, 0x6C44,
0x2828, 0x1028, 0x2323, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//96 (lowercase letters (not yet supported))
0x0000, 0x0110, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

//Prototypes
void constructTime(int, int, char*);
void shiftRegisterWrite(int, int, int, unsigned short*, int);

int main()
{
  wiringPiSetup();

  int clkPin = 0; //arbitrary
  int datPin = 1; //arbitrary
  int latPin = 2; //arbitrary

  pinMode(clkPin, OUTPUT);
  pinMode(datPin, OUTPUT);
  pinMode(latPin, OUTPUT);

  //Write data to time zone displays (doesn't need to be multiplexed)
  //Get time for various time zones using web-based API
  //Convert time to a format that can be displayed

  while(1)
  {
    //Multiplex time LED display at a frequency of 120 Hz
    //Change the value being displayed by comparing against internal clock time
    //Check the time (once every few hours or so)
    printf("it works but doesnt do anything");
 
  }
  return 0;
}

void shiftRegisterWrite(int clkPin, int datPin, int latPin, unsigned short* data, int dataLength)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < dataLength; i++) //cycle through the number of bytes of data
    {
        int dataValue = 0;
        for(j = 0; j < 16; j++) //cycle through the number of bits
        dataValue = data[i] & (1 << j);
        digitalWrite(datPin, dataValue);
        usleep(10);
        digitalWrite(clkPin, 1);
        usleep(10);
        digitalWrite(clkPin, 0);
        usleep(10);
    }
    digitalWrite(latPin, 1);
    usleep(10);
    digitalWrite(latPin, 0);
}

void constructTime(int hours, int minutes, char* writeThis)
{
    char writeIndexes[] = {0x00, 0x00, 0x00, 0x00};
    if(hours < 10)
    {
        writeIndexes[0] = '\0';
        writeIndexes[1] = hours + '0';
    }
    else if(hours < 20)
    {
        writeIndexes[0] = '1';
        writeIndexes[1] = (hours - 10) + '0';
    }
    else if(hours < 24)
    {
        writeIndexes[0] = '1';
        writeIndexes[1] = (hours - 20) + '0';
    }
    else
    {
        writeIndexes[0] = '0';
        writeIndexes[1] = '0';
    }

    if(minutes < 10)
    {
        writeIndexes[2] = '0';
        writeIndexes[3] = minutes + '0';
    }
    else if(minutes < 20)
    {
        writeIndexes[2] = '1';
        writeIndexes[3] = (minutes - 10) + '0';
    }
    else if(minutes < 30)
    {
        writeIndexes[2] = '2';
        writeIndexes[3] = (minutes - 20) + '0';
    }
    else if(minutes < 40)
    {
        writeIndexes[2] = '3';
        writeIndexes[3] = (minutes - 30) + '0';
    }
    else if(minutes < 50)
    {
        writeIndexes[2] = '4';
        writeIndexes[3] = (minutes - 40) + '0';
    }
    else if(minutes < 60)
    {
        writeIndexes[2] = '5';
        writeIndexes[3] = (minutes - 50) + '0';
    }
    else
    {
        writeIndexes[2] = '0';
        writeIndexes[3] = '0';
    }

    writeThis[0] = asciiTo7Seg[(int)writeIndexes[0]];
    writeThis[1] = asciiTo7Seg[(int)writeIndexes[1]];
    writeThis[2] = asciiTo7Seg[(int)writeIndexes[2]];
    writeThis[3] = asciiTo7Seg[(int)writeIndexes[3]];
}
