# worldClock
Using a Raspberry Pi to drive a series of 7-segment and 16-segment displays using shift registers so that they create a World Clock display with three time zones.

##Overview
The world clock contains six displays, three four-digit 7-segment displays for displaying the time, and three eight-digit 16-segment displays. Both types of display are driven by shift registers. The Raspberry Pi generates 3.3V signals which are sent via ribbon cables to the display driver broads. Each display driver board contains the shift registers and supporting circuitry to drive the LEDs.

##Hardware Layout
The 4-digit 7-segment displays are being repurposed from an existing but broken world clock. I have been unable to find a datasheet for these particular displays, but have been able to decode the signal patterns to the display.

####The LED display pinout is as follows:
(Segment naming scheme matches the diagram found on https://en.wikipedia.org/wiki/Seven-segment_display)

    0:  Digit 0 HIGH
    1:  Digit 1 HIGH
    2:  Digit 2 HIGH
    3:  Segment G LOW
    4:  Digit 2 HIGH
    5:  Segment DOT LOW
    6:  Digit 1 HIGH
    7:  NC
    8:  Digit 0 HIGH
    9:  Segment B LOW
    10: Segment F LOW
    11: Segment A LOW
    12: Digit 3 HIGH
    13: NC
    14: Segment C LOW
    15: Segment E LOW
    16: Segment D LOW
####The outputs from the shift registers are configured as follows:

    0:  NC
    1:  NC
    2:  NC
    3:  NC
    4:  Digit 3 HIGH
    5:  Digit 2 HIGH
    6:  Digit 1 HIGH
    7:  Digit 0 HIGH
    8:  Segment A LOW
    9:  Segment B LOW
    10: Segment C LOW
    11: Segment D LOW
    12: Segment E LOW
    13: Segment F LOW
    14: Segment G LOW
    15: Segment DOT LOW
    
The 8-digit 16-digit displays are being repurposed from an existing but broken world clock. I have decoded the signal patterns of the display through experimentation.

####The outputs from the shift registers are configured as follows:
(Segment naming scheme matches Figure 2 in http://pdfserv.maximintegrated.com/en/an/AN3212.pdf)

    0:  A1
    1:  A2
    2:  F
    3:  H
    4:  I
    5:  J
    6:  B
    7:  G2
    8:  D2
    9:  D1
    10: C
    11: K
    12: L
    13: M
    14: E
    15: G1

##Requirements
- Raspberry Pi
- wiringPi Library
- an internet connection
- compatible hardware (this is the tricky part)

Note: The hardware used in this project is highly customized. It's unlikely that off-the-shelf hardware will be naively compatible with this code. The look-up-table array constants that decode ascii to 7-segment and 16-segment values will need to be rebuilt manually based on the hardware configuration.

##Execution
Work in progress