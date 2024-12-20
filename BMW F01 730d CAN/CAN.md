BMW F01 F02 F10
CAN-Speed 500.000kbps (Terminated)
Unlock-Code 34


Notes:
- 0x1ee Switch fuel consumption
- 0x1f6 Turn signal Byte 0 Bit 0,1,4,5
- 0x349 Fuel
- 0x3f9 Oil-Temp
- 0x291 Units/Language: Byte 0 /Language (0,1,2,3), Byte 1 /Unit A-Temp, Byte 2 /Units

btw. 200 and 230 controlling lights


0x12f - Ignition

length 8

byte 2 - Ignition and Light
    bit 0 - ?
    bit 1 - 0 - for stealth mode? (or not and)
    bit 2 - 0 - for stealth mode?
    bit 3 - Terminal 15 (Ignition)
    bit 4 - ?
    bit 5 - ?
    bit 6 - ?
    bit 7 - ?

=============================================================================

0x0f3 - Tachometer / EfficientDynamics

length 8

byte 1 -
    bit 0 - Toggle it
    bit 1 - ?
    bit 2 - ?
    bit 3 - ?
    bit 4 - RPM-BIT0
    bit 5 - RPM-BIT1
    bit 6 - RPM-BIT2
    bit 7 - RPM-BIT3

byte 2 -
    bit 0 - RPM-BIT4
    bit 1 - RPM-BIT5
    bit 2 - RPM-BIT6
    bit 3 - RPM-BIT7
    bit 4 - RPM-BIT8
    bit 5 - RPM-BIT9
    bit 6 - RPM-BIT10
    bit 7 - RPM-BIT11

byte 4 - Efficient Dynamics
    bit 0 - Enable?
    bit 1 - 
    bit 2 - 
    bit 3 - 
    bit 4 - 
    bit 5 - 
    bit 6 - 
    bit 7 - 

=============================================================================

0x1a1 Speedometer

lenght 8

byte 2
    bit 0 - 
    bit 1 - ?
    bit 2 - 
    bit 3 - 
    bit 4 - SPEED-BIT0 (decimal?)
    bit 5 - SPEED-BIT1 (decimal?)
    bit 6 - SPEED-BIT2
    bit 7 - SPEED-BIT3

byte 3
    bit 0 - SPEED-BIT4
    bit 1 - SPEED-BIT5
    bit 2 - SPEED-BIT6
    bit 3 - SPEED-BIT7
    bit 4 - SPEED-BIT8
    bit 5 - SPEED-BIT9
    bit 6 - SPEED-BIT10 (overload)
    bit 7 - SPEED-BIT11 (overload)

byte 4
    bit 0 - Needs to be 1 to change speed
    bit 1 -
    bit 2 - 
    bit 3 - 
    bit 4 - 
    bit 5 -
    bit 6 -
    bit 7 - 

=============================================================================

0x349 - Fuel
Typical = 25 - 6553 Ohms
Usage = 25 - 927 Ohms
the higher the value, the emptier

Gastank left:
42.5L @ 25 Ohms 
0L @ ~949 Ohms (Byte0: 0x18, Byte1: 0x25)
Gastank right:
30.5L @ 25 Ohms
0L @ ~961 Ohms (Byte2: 0x91, Byte3: 0x25)
IMPORTANT: There will be an out of range error if you go too far beyond the values

length 8

byte 0 - gastank left (8/16Bit)
byte 1 - gastank left (16/16Bit)
byte 2 - gastank right (8/16Bit)
byte 3 - gastank right (16/16Bit)

=============================================================================

0x349 - Temperature

length 8

byte 4 - Coolant
    0x00 -> -48 °C (Min)
    0xC6 -> 150 °C
    0x7E -> 78 °C
    0xFD -> 205 °C (Max)
    0xFE -> -128 °C (Error)
    0xFF -> -128 °C (Error)
byte 5 - Oil
    0x00 -> -48 °C (Min)
    0xC6 -> 150 °C
    0x7E -> 78 °C
    0xFE -> 206 °C (Max)
    0xFF -> Error
