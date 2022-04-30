// CS472 Project 3
// Pipelined Datapath
//
// Author: Brian Horner
// Edit History:
// 4/26/2022 - Initial Version
// 4/27/2022 - Added instruction array and run function

// --- Standard Library Includes ---
#include <iostream>
#include <bitset>


// --- User Built Includes ---
#include "DataPipeline.h"

// --- Function Prototypes ---
void populateMainMem(short *, short);
void populateRegisters(int *, short);
void runSimulation(const int64_t *, int);



int main() {
    const int instructionCacheSize = 12;
    int64_t testInstructionCache[5] = {0x00a63820, 0x8d0f0004, 0xad09fffc,
                                       0x00625022, 0x10c8fffb};
    int64_t instructionCache[instructionCacheSize] = {0xa1020000, 0x810AFFFC,
                                                      0x00831820,0x01263820,
                                                      0x01224820, 0x81180000,
                                                      0x81510010, 0x00624022,
                                                      0x00000000,0x00000000,
                                                      0x00000000, 0x00000000};


//    runSimulation(testInstructionCache, 5);
    runSimulation(instructionCache, instructionCacheSize);
    return 0;
}

void runSimulation(const int64_t *instructionArr, int numInstructions){
    DataPipeline dataPipeline;
    int64_t instruction;
    for(int i{0}; i<numInstructions; i++){
        int clockCycleStart = 1;
        instruction = instructionArr[i];
        dataPipeline.IF_stage(instruction);
        dataPipeline.ID_stage();
        dataPipeline.EX_stage();
        dataPipeline.MEM_stage();
        dataPipeline.WB_stage();
        dataPipeline.print_out_everything();
        dataPipeline.copy_write_to_read();


    }
}

