// Mem WB Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/27/2022 - Initial Version

// --- Standard Library Includes
#include <iostream>
// --- User Built Includes
#include "Mem_WB.h"

// --- Constructor ---
Mem_WB::Mem_WB() {}
Mem_WB::Mem_WB(const Mem_WB &referenceMem_WB) {

    // Instruction Calculated Information
    setLWDataValue(referenceMem_WB.getLWDataValue());
    setALUResult(referenceMem_WB.getALUResult());
    setWriteRegNum(referenceMem_WB.getWriteRegNum());

    // Control Bits
    setMemToReg(referenceMem_WB.getMemToReg());
    setRegWrite(referenceMem_WB.getRegWrite());
}
// --- General Methods ---
void Mem_WB::copyDataToRead(const Mem_WB &referenceMem_WB) {

    // Instruction Calculated Information
    setLWDataValue(referenceMem_WB.getLWDataValue());
    setALUResult(referenceMem_WB.getALUResult());
    setWriteRegNum(referenceMem_WB.getWriteRegNum());

    // Control Bits
    setMemToReg(referenceMem_WB.getMemToReg());
    setRegWrite(referenceMem_WB.getRegWrite());
}
// --- Instruction Get Methods ---
int Mem_WB::getLWDataValue() const {return LWDataValue;}
int Mem_WB::getALUResult() const {return ALUResult;}
int Mem_WB::getWriteRegNum() const {return WriteRegNum;}

// --- Instruction Set Methods ---
void Mem_WB::setLWDataValue(int newLWDataValue) {LWDataValue = newLWDataValue;}
void Mem_WB::setALUResult(int newALUResult) {ALUResult = newALUResult;}
void Mem_WB::setWriteRegNum(int newWriteRegNum) {WriteRegNum = newWriteRegNum;}

// --- Control Get Methods ---
bool Mem_WB::getMemToReg() const {return MemToReg;}
bool Mem_WB::getRegWrite() const {return RegWrite;}

// --- Control Set Methods ---
void Mem_WB::setMemToReg(bool newMemToReg) {MemToReg = newMemToReg;}
void Mem_WB::setRegWrite(bool newRegWrite) {RegWrite = newRegWrite;}

// --- Print Method ---
void Mem_WB::print() const {
    std::cout << "Calculation Instruction Information:\n";
    std::cout << "ALUResult: " <<std::uppercase<<std::hex <<ALUResult<<std::endl;
    std::cout << "LWDataValue: " <<LWDataValue <<std::endl;
    std::cout << "WriteRegNum: " <<std::dec <<WriteRegNum <<std::endl;

    std::cout <<"\nControl Information:\n";
    std::cout << "RegWrite: " <<RegWrite <<std::endl;
    std::cout << "MemToReg: " <<MemToReg <<std::endl;
}

// --- Destructor ---
Mem_WB::~Mem_WB() {}