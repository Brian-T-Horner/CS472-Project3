// Mem WB Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/27/2022 - Initial Version

#ifndef PROJECT3_MEM_WB_H
#define PROJECT3_MEM_WB_H

// --- Standard Library Includes ---

// --- User Built Includes ---

class Mem_WB {
public:
    // --- Constructor ---
    Mem_WB(); // default constructor
    Mem_WB(Mem_WB const&); //copy constructor

    // --- General Methods ---
    void copyDataToRead(Mem_WB const&);
    bool checkInstructionValues() const;

    // --- Instruction Calculations Get Methods ---
    int getLWDataValue() const;
    int getALUResult() const;
    int getWriteRegNum() const;

    // --- Instruction Calculations Set Methods ---
    void setLWDataValue(int);
    void setALUResult(int);
    void setWriteRegNum(int);

    // --- Control Get Methods ---
    bool getMemToReg() const;
    bool getRegWrite() const;

    // --- Control Set Methods ---
    void setMemToReg(bool);
    void setRegWrite(bool);

    // --- Print Method ---
    void print() const;

    // --- Destructor ---
    ~Mem_WB();

private:
    // Instruction Calculations
    int LWDataValue{0};
    int ALUResult{0};
    int WriteRegNum{0};

    // Control Bits
    bool MemToReg{false};
    bool RegWrite{false};

};


#endif //PROJECT3_MEM_WB_H
