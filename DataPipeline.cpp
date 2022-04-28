// Data Pipeline Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/26/2022 - Initial Version
// 4/27/2022 - Added copy and print functions
// 4/27/2022 - Added Constructor and destructor
// 4/27/2022 - Added general declarations (mainMem, Registers etc.)
// 4/27/2022 - Fixed print function

// --- Standard Library Includes ---
#include <iostream>
#include <cstdint>

// --- User Build Includes ---
#include "DataPipeline.h"
#include "IF_ID.h"
#include "ID_EX.h"
#include "EX_Mem.h"
#include "Mem_WB.h"

// --- Declarations ---



// Write Objects
IF_ID IF_ID_Write;
ID_EX ID_EX_Write;
EX_Mem EX_Mem_Write;
Mem_WB Mem_WB_Write;

// Read Objects
IF_ID IF_ID_Read(IF_ID_Write);
ID_EX ID_EX_Read(ID_EX_Write);
EX_Mem EX_Mem_Read(EX_Mem_Write);
Mem_WB Mem_WB_Read(Mem_WB_Write);

// Instruction Shortcuts
int lb = 0x20;
int sb = 0x28;
int nop = 0;
int add = 0x20;
int sub = 0x22;

// Memory Objects and Sizes
const short mainMemSize = 1024;
const short numOfRegisters = 32;
short main_Mem[mainMemSize];
int registers[numOfRegisters];



// --- General Functions ---
void populateMainMem(short *, short);
void populateRegisters(int *, short);
void initializeReadWriteObject();

// --- Constructor ---
DataPipeline::DataPipeline() {
    populateMainMem(main_Mem, mainMemSize);
    populateRegisters(registers, numOfRegisters);
}

// --- General Pipeline Functions ---
void DataPipeline::IF_stage(int64_t newinstruction) {
    addToClockCycle(1);
}
void DataPipeline::ID_stage() {}
void DataPipeline::EX_stage() {}

void DataPipeline::MEM_stage() {}

void DataPipeline::WB_stage() {}

void DataPipeline::print_out_everything() {
    std::cout << "\n\nCurrent Print out for Clock Cycle: " <<ClockCycle <<
    "\n\n";

    // Printing Registers
    std::cout << "Current Register Values: " <<std::endl;
    for (int i{0}; i< numOfRegisters; i++){
        std::cout << "Register: " <<i;
        std::cout << std::uppercase <<std::hex;
        std::cout << " Value: 0x" <<registers[i]<<std::endl;
    }
    std::cout <<
    "------------------------------------------------------"<<std::endl;

    // Printing IF_ID's
    std::cout << "IF_ID Write: \n";
    IF_ID_Write.print();
    std::cout <<
    "------------------------------------------------------"<<std::endl;

    std::cout <<"IF_ID Read: \n";
    IF_ID_Read.print();
    std::cout <<
    "------------------------------------------------------"<<std::endl;

    // Printing ID_EX's
    std::cout <<"ID_EX Write: \n";
    ID_EX_Write.print();
    std::cout <<
    "------------------------------------------------------"<<std::endl;

    std::cout <<"ID_EX Read: \n";
    ID_EX_Read.print();
    std::cout <<
    "------------------------------------------------------"<<std::endl;

    // Printing EX_Mem's
    std::cout <<"EX_Mem Write: \n";
    EX_Mem_Write.print();
    std::cout <<
    "------------------------------------------------------"<<std::endl;

    std::cout <<"EX_Mem Read: \n";
    EX_Mem_Read.print();
    std::cout <<
    "------------------------------------------------------"<<std::endl;

    // Printing Mem_WB's
    std::cout <<"Mem_WB Write: \n";
    Mem_WB_Write.print();
    std::cout <<
    "------------------------------------------------------"<<std::endl;

    std::cout <<"Mem_WB Read: \n";
    Mem_WB_Read.print();
    std::cout <<
    "------------------------------------------------------"<<std::endl;
}

void DataPipeline::copy_write_to_read() {
    IF_ID_Read.copyDataToRead(IF_ID_Write);
    ID_EX_Read.copyDataToRead(ID_EX_Write);
    EX_Mem_Read.copyDataToRead(EX_Mem_Write);
    Mem_WB_Read.copyDataToRead(Mem_WB_Write);
}

// --- Get Methods ---
int DataPipeline::getClockCycle() {return this->ClockCycle;}

// --- Set Methods ---
void DataPipeline::setClockCycle(int newClockCycle) {ClockCycle = newClockCycle;}

void DataPipeline::addToClockCycle(int additive){ClockCycle +=additive;}
// --- Destructor ---
DataPipeline::~DataPipeline() {}


//--------------------------------------------------------

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

