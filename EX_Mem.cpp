// EX Mem Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/27/2022 - Initial Version
// 4/27/2022 - Added constructor, destructor and general methods
// 4/27/2022 - Added get and set methods

// --- Standard Library Includes
#include <iostream>
// --- User Built Includes
#include "EX_Mem.h"

// --- Constructor ---
EX_Mem::EX_Mem() {}
EX_Mem::EX_Mem(EX_Mem const &referenceEX_Mem) {

    //Instruction Calculated Information
    setALUResult( referenceEX_Mem.getALUResult());
    setSWValue(referenceEX_Mem.getSWValue());
    setWriteRegNum(referenceEX_Mem.getWriteRegNum());

    // Control Bits
    setMemRead(referenceEX_Mem.getMemRead());
    setMemWrite(referenceEX_Mem.getMemWrite());
    setRegWrite(referenceEX_Mem.getRegWrite());
    setMemToReg(referenceEX_Mem.getMemToReg());
}

// --- General Methods ---
void EX_Mem::copyDataToRead(EX_Mem const &referenceEX_Mem) {
    //Instruction Calculated Information
    setALUResult( referenceEX_Mem.getALUResult());
    setSWValue(referenceEX_Mem.getSWValue());
    setWriteRegNum(referenceEX_Mem.getWriteRegNum());

    // Control Bits
    setMemRead(referenceEX_Mem.getMemRead());
    setMemWrite(referenceEX_Mem.getMemWrite());
    setRegWrite(referenceEX_Mem.getRegWrite());
    setMemToReg(referenceEX_Mem.getMemToReg());
}

// --- Instruction Get Methods ---
int EX_Mem::getALUResult() const {return ALUResult;}
int EX_Mem::getSWValue() const {return SWValue;}
int EX_Mem::getWriteRegNum() const {return WriteRegNum;}

// --- Instruction Set Methods ---
void EX_Mem::setALUResult(int newALUResult) {ALUResult = newALUResult;}
void EX_Mem::setSWValue(int newSWValue) {SWValue = newSWValue;}
void EX_Mem::setWriteRegNum(int newWriteRegNum) {WriteRegNum = newWriteRegNum;}

// --- Control Get Methods ---
bool EX_Mem::getMemRead() const {return  MemRead;}
bool EX_Mem::getMemWrite() const {return MemWrite;}
bool EX_Mem::getRegWrite() const {return  RegWrite;}
bool EX_Mem::getMemToReg() const {return MemToReg;}

// --- Control Set Methods ---
void EX_Mem::setMemRead(bool newMemRead) {MemRead = newMemRead;}
void EX_Mem::setMemWrite(bool newMemWrite) {MemWrite = newMemWrite;}
void EX_Mem::setRegWrite(bool newRegWrite) {RegWrite = newRegWrite;}
void EX_Mem::setMemToReg(bool newMemToReg) {MemToReg = newMemToReg;}

// --- Print Method ---
void EX_Mem::print() const {
    std::cout << "Calculation Instruction Information:\n";
    std::cout << "ALUResult: " <<std::uppercase<<std::hex <<ALUResult<<std::endl;
    std::cout << "SWValue: " <<SWValue <<std::endl;
    std::cout << "WriteRegNum: " <<std::dec <<WriteRegNum <<std::endl;

    std::cout <<"\nControl Information:\n";
    std::cout << "MemRead: " <<std::dec<<MemRead <<std::endl;
    std::cout << "MemWrite: " << MemWrite <<std::endl;
    std::cout << "RegWrite: " <<RegWrite <<std::endl;
    std::cout << "MemToReg: " <<MemToReg <<std::endl;

}

// --- Destructor ---
EX_Mem::~EX_Mem() {}