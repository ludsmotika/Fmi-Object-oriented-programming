#include "GlobalFunctions.h"

void printBitsOfByte(uint8_t num) 
{
    char binaryString[9];
    binaryString[8] = '\0';

    for (int i = 7; i >= 0; i--) {
        binaryString[i] = (num & 1) ? '1' : '0';
        num >>= 1;
    }

    std::cout << binaryString;
}