// Data Pipeline Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/26/2022 - Initial Version
// 4/27/2022 - Added copy and print functions
// 4/27/2022 - Added Constructor and destructor
// 4/27/2022 - Added general declarations (mainMem, Registers etc.)
// 4/27/2022 - Fixed print function
// 4/27/2022 - IF_Stage done
// 4/28/2022 - Added bitwise & and shift functions
// 4/28/2022 - ID_Stage done

// --- Standard Library Includes ---
#include <iostream>
#include <cstdint>
#include <bitset>

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
int CalcOpCode(int64_t);
int CalcOffset(int64_t);
int CalcReadReg1(int64_t);
int CalcReadReg2(int64_t);
int CalcWriteReg_15_11(int64_t);
int CalcFunction(int64_t);




// --- Constructor ---
DataPipeline::DataPipeline() {
    populateMainMem(main_Mem, mainMemSize);
    populateRegisters(registers, numOfRegisters);
}

// --- General Pipeline Functions --- // TODO:: Mst to be done
void DataPipeline::IF_stage(int64_t newinstruction) {
    addToClockCycle(1);
    IF_ID_Write.setInstruction(newinstruction);
}
void DataPipeline::ID_stage() {
    int64_t newInstruction = IF_ID_Read.getInstruction();
    if(newInstruction == 0){
        resetIDStage(ID_EX_Write);
    }else{
        // Calc Op Code and set
        ID_EX_Write.setOpCode(CalcOpCode(newInstruction));
        // Calc Offset and set
        ID_EX_Write.setOffset(CalcOffset(newInstruction));
        // Calc read register 1 and set
        ID_EX_Write.setReadReg1(CalcReadReg1(newInstruction));
        // Calc read register 2 and set
        ID_EX_Write.setReadReg2(CalcReadReg2(newInstruction));
        // Calc write register bits 15-11 and set
        ID_EX_Write.setWriteReg_15_11(CalcWriteReg_15_11(newInstruction));
        // Set write register bits 20-16 from read register 2
        ID_EX_Write.setWriteReg_20_16(ID_EX_Write.getReadReg2());
        // Calculate function code and set
        ID_EX_Write.setFunction(CalcFunction(newInstruction));

        // set control bits
        if(ID_EX_Write.getOpCode() == 0x20){
            // load byte
            ID_EX_Write.setRegDest(false);
            ID_EX_Write.setALUOp(false);
            ID_EX_Write.setALUSrc(true);
            ID_EX_Write.setMemRead(true);
            ID_EX_Write.setMemWrite(false);
            ID_EX_Write.setRegWrite(true);
            ID_EX_Write.setMemToReg(true);
        }else if(ID_EX_Write.getOpCode() == 0x28){
            // store byte
            ID_EX_Write.setRegDest(false); // Not actually needed
            ID_EX_Write.setALUOp(false);
            ID_EX_Write.setALUSrc(true);
            ID_EX_Write.setMemRead(false);
            ID_EX_Write.setMemWrite(true);
            ID_EX_Write.setRegWrite(false);
            ID_EX_Write.setMemToReg(false); // Not actually needed

        }else if(ID_EX_Write.getOpCode() == 0){
            // R format
            ID_EX_Write.setRegDest(true);
            ID_EX_Write.setALUOp(true);
            ID_EX_Write.setALUSrc(false);
            ID_EX_Write.setMemRead(false);
            ID_EX_Write.setMemWrite(false);
            ID_EX_Write.setRegWrite(true);
            ID_EX_Write.setMemToReg(false);
        }
    }
}




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

void DataPipeline::resetIDStage(ID_EX& referenceID_EX) {
    // Instruction Calculations
    referenceID_EX.setReadReg1(0);
    referenceID_EX.setReadReg2(0);
    referenceID_EX.setOffset(0);
    referenceID_EX.setWriteReg_20_16(0);
    referenceID_EX.setWriteReg_15_11(0);
    referenceID_EX.setOpCode(0);

    // Control Bits
    referenceID_EX.setRegDest(false);
    referenceID_EX.setALUOp(false);
    referenceID_EX.setALUSrc(false);
    referenceID_EX.setMemRead(false);
    referenceID_EX.setMemWrite(false);
    referenceID_EX.setRegWrite(false);
    referenceID_EX.setMemToReg(false);
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

int CalcOpCode(int64_t instruction){
    // Calculates the OP Code
    unsigned int OpCodeMask = 0b111111<<26;
    unsigned int OpCode = (OpCodeMask & instruction)>>26;
    return static_cast<int>(OpCode);
}

int CalcOffset(int64_t instruction){
    //Calculates the offset
    unsigned int OffsetMask = 0xffff<<16;
    int offset = (OffsetMask&(instruction<<16))>>16;
    return static_cast<int>(offset);
}

int CalcReadReg1(int64_t instruction){
    // Calculates Read Register 1
    int mask = 0b11111;
    int reg = ((mask<<21)&instruction)>>21;
    return reg;
}
int CalcReadReg2(int64_t instruction){
    // Calculates Read Register 2
    int mask = 0b11111;
    int reg = ((mask<<16)&instruction)>>16;
    return reg;
}
int CalcWriteReg_15_11(int64_t instruction){
    // Calculates Write Register bits 15-11
    int mask = 0b11111;
    int reg = ((mask<<11)&instruction)>>11;
    return reg;
}

int CalcFunction(int64_t instruction){
    // Calculates function code
    int mask = 0b111111;
    int func = (mask&instruction);
    return func;
}
