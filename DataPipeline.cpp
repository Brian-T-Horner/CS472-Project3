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
// 4/29/2022 - EX_Stage done
// 4/30/2022 - Mem_Stage and WB_Stage done

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
int CalcOpCode(int64_t);
int CalcOffset(int64_t);
int CalcReadReg1(int64_t, int []);
int CalcReadReg2(int64_t, int []);
int CalcWriteReg_15_11(int64_t);
int CalcWriteReg_20_16(int64_t);
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
        ID_EX_Write.setReadReg1(CalcReadReg1(newInstruction, registers));
        // Calc read register 2 and set
        ID_EX_Write.setReadReg2(CalcReadReg2(newInstruction, registers));
        // Calc write register bits 15-11 and set
        ID_EX_Write.setWriteReg_15_11(CalcWriteReg_15_11(newInstruction));
        // Set write register bits 20-16 from read register 2
        ID_EX_Write.setWriteReg_20_16(CalcWriteReg_20_16(newInstruction));
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




void DataPipeline::EX_stage() {

    EX_Mem_Write.setMemRead(ID_EX_Read.getMemRead());
    EX_Mem_Write.setMemWrite(ID_EX_Read.getMemWrite());
    EX_Mem_Write.setRegWrite(ID_EX_Read.getRegWrite());
    EX_Mem_Write.setMemToReg(ID_EX_Read.getMemToReg());

    if (ID_EX_Read.getRegDest() == 1 && ID_EX_Read.getALUOp() == 1 &&ID_EX_Read.getALUSrc() == 0){
        // R type
        if(ID_EX_Read.getFunction() == 0x20){
            //add
            EX_Mem_Write.setALUResult(ID_EX_Read.getReadReg1() + ID_EX_Read.getReadReg2());
        }else if(ID_EX_Read.getFunction() == 0x22){
            //sub
            EX_Mem_Write.setALUResult(ID_EX_Read.getReadReg1()-ID_EX_Read.getReadReg2());
        }else{
            std::cout << "Error: Should not reach here in R type function "
                         "execution."<<std::endl;
        }

        // set WriteRegNum
        EX_Mem_Write.setWriteRegNum(ID_EX_Read.getWriteReg_15_11());
        // set SWValue
        EX_Mem_Write.setSWValue(ID_EX_Read.getReadReg2());

    }else if(ID_EX_Read.getRegDest() == 0 && ID_EX_Read.getALUOp() == 0 &&
    ID_EX_Read.getALUSrc() == 1){
        if(ID_EX_Read.getOpCode() == 0x20){
            // load byte

            // Set ALU Result
            EX_Mem_Write.setALUResult(ID_EX_Read.getReadReg1() + ID_EX_Read
            .getOffset());
            // Set WriteReg
            EX_Mem_Write.setWriteRegNum(ID_EX_Read.getWriteReg_20_16());
            // Set swvalue
            EX_Mem_Write.setSWValue(ID_EX_Read.getReadReg2());

        }else if(ID_EX_Read.getOpCode() == 0x28){
            // store byte
            EX_Mem_Write.setALUResult(ID_EX_Read.getReadReg1() + ID_EX_Read
            .getOffset());
            // WriteRegNum & SWValue not used
        }else{
            std::cout << "Error: Should not reach here in I type opcode "
                         "execution." <<std::endl;
        }
    }else{
        // Nop

        EX_Mem_Write.setALUResult(0);
        EX_Mem_Write.setSWValue(0);
        EX_Mem_Write.setWriteRegNum(0);

    }

}
void DataPipeline::MEM_stage() {

    Mem_WB_Write.setMemToReg(EX_Mem_Read.getMemToReg());
    Mem_WB_Write.setRegWrite(EX_Mem_Read.getRegWrite());


    if (EX_Mem_Read.getMemRead() == 0 && EX_Mem_Read.getMemWrite() == 0){
        // R type
        Mem_WB_Write.setLWDataValue(00); // setting to 00 as NULL value
        Mem_WB_Write.setALUResult(EX_Mem_Read.getALUResult());
        Mem_WB_Write.setWriteRegNum((EX_Mem_Read.getWriteRegNum()));

    }else if(EX_Mem_Read.getMemRead() == 1 && EX_Mem_Read.getMemWrite() == 0){
        // load byte

        // Getting write reg number for loading later
        Mem_WB_Write.setWriteRegNum((EX_Mem_Read.getWriteRegNum()));
        // Getting alu result
        Mem_WB_Write.setALUResult(EX_Mem_Read.getALUResult());
        // setting load word data value
        Mem_WB_Write.setLWDataValue(main_Mem[Mem_WB_Write.getALUResult()]);



    }else if(EX_Mem_Read.getMemRead() == 0 && EX_Mem_Read.getMemWrite() == 1){
        // store byte

        // Getting ALUResult
        Mem_WB_Write.setALUResult(EX_Mem_Read.getALUResult());
        // storing SWValue into main memory with alu result location
        main_Mem[Mem_WB_Write.getALUResult()] = EX_Mem_Read.getSWValue();
        Mem_WB_Write.setALUResult(00); // setting to 00 as NULL value
        Mem_WB_Write.setWriteRegNum(00); // setting to 00 as NULL value
    }else{
        //nop
        Mem_WB_Write.setLWDataValue(0);
        Mem_WB_Write.setALUResult(0);
        Mem_WB_Write.setWriteRegNum(0);
    }
}
void DataPipeline::WB_stage() {
    if(Mem_WB_Read.getRegWrite() == 1 && Mem_WB_Read.getRegWrite() == 0){
        // R type
        // Storing alu result into registers with reg num as index
        registers[Mem_WB_Read.getWriteRegNum()] = Mem_WB_Read.getALUResult();
    }else if (Mem_WB_Read.getRegWrite() == 1 && Mem_WB_Read.getRegWrite() == 1){
        // load byte
        // Storing loading byte into registers with reg num as index
        registers[Mem_WB_Read.getWriteRegNum()] = Mem_WB_Read.getLWDataValue();
    }
    // Load word is already done at this point
}

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

int CalcReadReg1(int64_t instruction, int registers []){
    // Calculates Read Register 1 Value
    int mask = 0b11111;
    int reg = ((mask<<21)&instruction)>>21;
    int regValue = registers[reg];
    return regValue;
}
int CalcReadReg2(int64_t instruction, int registers []){
    // Calculates Read Register 2 Value
    int mask = 0b11111;
    int reg = ((mask<<16)&instruction)>>16;
    int regValue = registers[reg];
    return regValue;
}
int CalcWriteReg_20_16(int64_t instruction){
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

int CalcFunction(int64_t instruction, int registers){
    // Calculates function code
    int mask = 0b111111;
    int func = (mask&instruction);
    return func;
}
