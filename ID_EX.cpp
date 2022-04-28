// ID EX Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/27/2022 - Initial Version
// 4/27/2022 - Added control get and set methods
// 4/27/2022 - Added destructor
// 4/27/2022 - Added instruction get and set methods
// 4/27/2022 - Changed methods that passed pointer to ID_EX object to const
// reference

// --- Standard Library Includes
#include <iostream>
// --- User Built Includes
#include "ID_EX.h"

// --- Constructor ---
ID_EX::ID_EX() {}

ID_EX::ID_EX(ID_EX const &referenceID_EX) {
    if(checkInstructionValues()){
        // Instruction Information
        setReadReg1(referenceID_EX.getReadReg1());
        setReadReg2(referenceID_EX.getReadReg2());
        setOffset(referenceID_EX.getOffset());
        setWriteReg_20_16(referenceID_EX.getWriteReg_20_16());
        setWriteReg_15_11(referenceID_EX.getWriteReg_15_11());
        setOpCode(referenceID_EX.getOpCode());

        // Control Bits
        setRegDest(referenceID_EX.getRegDest());
        setALUOp(referenceID_EX.getALUOp());
        setALUSrc(referenceID_EX.getALUSrc());
        setMemRead(referenceID_EX.getMemRead());
        setMemWrite(referenceID_EX.getMemWrite());
        setRegWrite(referenceID_EX.getRegWrite());
        setMemToReg(referenceID_EX.getMemToReg());
    }
}
// --- General Methods ---
ID_EX ID_EX::copyDataToRead(ID_EX const &referenceID_EX){
    // Instruction Information
    setReadReg1(referenceID_EX.getReadReg1());
    setReadReg2(referenceID_EX.getReadReg2());
    setOffset(referenceID_EX.getOffset());
    setWriteReg_20_16(referenceID_EX.getWriteReg_20_16());
    setWriteReg_15_11(referenceID_EX.getWriteReg_15_11());
    setOpCode(referenceID_EX.getOpCode());

    // Control Bits
    setRegDest(referenceID_EX.getRegDest());
    setALUOp(referenceID_EX.getALUOp());
    setALUSrc(referenceID_EX.getALUSrc());
    setMemRead(referenceID_EX.getMemRead());
    setMemWrite(referenceID_EX.getMemWrite());
    setRegWrite(referenceID_EX.getRegWrite());
    setMemToReg(referenceID_EX.getMemToReg());
}



bool ID_EX::checkInstructionValues() const {
    if (OpCode){
        if(ReadReg1 && ReadReg2 && WriteReg_20_16 && WriteReg_15_11){
            return true;
        }else{
            return false;
        }
    }else {
        if(Offset && ReadReg1 && ReadReg2 && WriteReg_20_16 && WriteReg_15_11){
            return true;
        }else{
            return false;
        }
    }
}

// --- Instruction Get Methods ---
int ID_EX::getReadReg1() const {return this-> ReadReg1;}
int ID_EX::getReadReg2() const {return this-> ReadReg2;}
int ID_EX::getOffset() const {return this-> Offset;}
int ID_EX::getWriteReg_20_16() const {return this-> WriteReg_20_16;}
int ID_EX::getWriteReg_15_11() const {return this-> WriteReg_15_11;}
int ID_EX::getOpCode() const {return this-> OpCode;}

// --- Instruction Set Methods ---
void ID_EX::setReadReg1(int newReadReg1) {this->ReadReg1 = newReadReg1;}
void ID_EX::setReadReg2(int newReadReg2) {this->ReadReg2 = newReadReg2;}
void ID_EX::setOffset(int newOffset) {this->Offset = newOffset;}

void ID_EX::setWriteReg_20_16(int newWriteReg_20_16) {
    this->WriteReg_20_16 = newWriteReg_20_16;
}
void ID_EX::setWriteReg_15_11(int newWriteReg_15_11) {
    this->WriteReg_15_11 = newWriteReg_15_11;
}

void ID_EX::setOpCode(int newOpCode) {this->OpCode = newOpCode;}

// --- Control Bits Get Methods --
bool ID_EX::getRegDest() const {return this->RegDest;}
bool ID_EX::getALUOp() const {return this->ALUOp;}
bool ID_EX::getALUSrc() const {return this->ALUSrc;}
bool ID_EX::getMemRead() const {return this->MemRead;}
bool ID_EX::getMemWrite() const {return this-> MemWrite;}
bool ID_EX::getRegWrite() const {return this->RegWrite;}
bool ID_EX::getMemToReg() const {return this->MemToReg;}

// --- Control Bits Set Methods ---
void ID_EX::setRegDest(bool newRegDest) {this->RegDest = newRegDest;}
void ID_EX::setALUOp(bool newALUOp) {this->ALUOp = newALUOp;}
void ID_EX::setALUSrc(bool newALUSrc) {this->ALUSrc = newALUSrc;}
void ID_EX::setMemRead(bool newMemRead) {this->MemRead = newMemRead;}
void ID_EX::setMemWrite(bool newMemWrite) {this->MemWrite = newMemWrite;}
void ID_EX::setRegWrite(bool newRegWrite) {this->RegWrite = newRegWrite;}
void ID_EX::setMemToReg(bool newMemToReg) {this->MemToReg = newMemToReg;}

// Print Method ---
void ID_EX::print() const {
    std::cout <<"Instruction Information:\n";
    std::cout << "Read Register 1: 0x" <<std::uppercase<<std::hex<< ReadReg1<<std::endl;
    std::cout << "Read Register 2: 0x" <<std::uppercase<<std::hex<<ReadReg2<<std::endl;
    std::cout << "Offset: 0x" <<std::uppercase<<std::hex<<Offset<<std::endl;
    std::cout << "Write Register Bits 20-16: "<<std::dec<<WriteReg_20_16<<std::endl;
    std::cout << "Write Register Bits 15-11: " <<WriteReg_15_11 <<std::endl;
    std::cout << "Opcode: " <<OpCode <<std::endl;
    // TODO:: FUNCTION???

    std::cout << "\nControl Information:\n";
    std::cout << "RegDest: " <<RegDest<<std::endl;
    std::cout << "ALUOp: "<<ALUOp<<std::endl;
    std::cout << "ALUSrc: "<<ALUSrc<<std::endl;
    std::cout << "MemRead: "<<MemRead<< std::endl;
    std::cout <<"MemWrite: "<<MemWrite<< std::endl;
    std::cout << "RegWrite: "<<RegWrite<<std::endl;
    std::cout << "MemToReg: "<<MemToReg<<std::endl;

}

// --- Destructor ---
ID_EX::~ID_EX() {}