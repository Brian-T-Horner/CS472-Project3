// CS472 Project 3
// Pipelined Datapath
//
// Author: Brian Horner
// Edit History:
// 4/26/2022 - Initial Version

// --- Standard Library Includes ---
#include <iostream>

// --- User Built Includes ---

// --- Function Prototypes ---
void populateMainMem(short *, short);
void populateRegisters(int *, short);

int main() {
    short mainMemSize = 1024;
    short numOfRegisters = 32;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

void populateMainMem(short *mainMem, short mainMemSize){
    short b{0};
    for (int i{0}; i<mainMemSize; i++){
        if(b<=0xFF){
            mainMem[i] = b;
            b++;
        }else{
            b = 0;
            mainMem[i] = b;
            b++;
        }
    }
}

void populateRegisters(int *registers, short numOfRegisters){
    for (int i{0}; i<numOfRegisters; i++){
        if(i==0){
            registers[i] = 0;
        }else{
            registers[i] = 0x100+i;
        }
    }
}