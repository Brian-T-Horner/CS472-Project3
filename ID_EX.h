// ID EX Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/27/2022 - Initial Version
// 4/27/2022 - Added instruction and control private members
// 4/27/2022 - Added control get and set methods
// 4/27/2022 - Added instruction get and set methods
// 4/27/2022 - Changed methods that passed pointer to ID_EX object to const
// reference
// 4/28/2022 - Added function code get/set methods & data member

#ifndef PROJECT3_ID_EX_H
#define PROJECT3_ID_EX_H

// --- Standard Library Includes ---

// --- User Built Includes ---

#include "IF_ID.h"

class ID_EX {
public:
    // --- Constructor ---
    ID_EX(); //default constructor
    ID_EX(ID_EX const&); // copy constructor

    // --- General Methods ---
    ID_EX copyDataToRead(ID_EX const&);
    bool checkInstructionValues() const;

    // --- Instruction Get Methods ---
    int getReadReg1 () const;
    int getReadReg2() const;
    int getOffset() const;
    int getWriteReg_20_16() const;
    int getWriteReg_15_11() const;
    int getOpCode() const;

    // --- Instruction Set Methods ---
    void setReadReg1(int);
    void setReadReg2(int);
    void setOffset(int);
    void setWriteReg_20_16(int);
    void setWriteReg_15_11(int);
    void setOpCode(int);
    void setFunction(int);

    // --- Control Bits Get Methods ---
    bool getRegDest() const;
    bool getALUOp() const;
    bool getALUSrc() const;
    bool getMemRead() const;
    bool getMemWrite() const;
    bool getRegWrite() const;
    bool getMemToReg() const;
    int getFunction() const;


    // --- Control Bits Set Methods ---
    void setRegDest(bool);
    void setALUOp(bool);
    void setALUSrc(bool);
    void setMemRead(bool);
    void setMemWrite(bool);
    void setRegWrite(bool);
    void setMemToReg(bool);


    // --- Print Method ---
    void print() const;

    // --- Destructor ---
    ~ID_EX();
private:


    // Instruction Information
    int ReadReg1{0};
    int ReadReg2{0}; //TODO: NEED or same as writereg_20_16???
    int Offset{0};
    int WriteReg_20_16{0};
    int WriteReg_15_11{0};
    int OpCode{0};
    int Function{0};

    // Control Bits
    bool RegDest{false};
    bool ALUOp{false};
    bool ALUSrc{false};
    bool MemRead{false};
    bool MemWrite{false};
    bool RegWrite{false};
    bool MemToReg{false};



};


#endif
