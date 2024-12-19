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

byte 1 - Ignition and Light
    bit 0 - ?
    bit 1 - Toggle for keep on
    bit 2 - ?
    bit 3 - ?
    bit 4 - ?
    bit 5 - ?
    bit 6 - ?
    bit 7 - ?

byte 2 - Ignition and Light
    bit 0 - ?
    bit 1 - ?
    bit 2 - Light-Mode (Stand-By?)
    bit 3 - Ignition
    bit 4 - ?
    bit 5 - ?
    bit 6 - ?
    bit 7 - ?

=============================================================================

0x0f3 - Tachometer / EfficientDynamics

length 8

byte 1 -
    bit 0 - LoBit
    bit 1 - ?
    bit 2 - ?
    bit 3 - ?
    bit 4 - ?
    bit 5 - ?
    bit 6 - ?
    bit 7 - ?

byte 2 -
    bit 0 - ?
    bit 1 - ?
    bit 2 - ?
    bit 3 - ?
    bit 4 - ?
    bit 5 - ?
    bit 6 - MidBit
    bit 7 - HighBit


=============================================================================

0x1a1 Speedometer

lenght 8

byte 3
    bit 0 - 
    bit 1 - 
    bit 2 - 
    bit 3 - 
    bit 4 - 
    bit 5 - 
    bit 6 - Speed
    bit 7 - 

byte 4
    bit 0 - Needs to be 1 to change speed
    bit 1 -
    bit 2 - 
    bit 3 - 
    bit 4 - 
    bit 5 -
    bit 6 -
    bit 7 - 