// Ex Mem Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/27/2022 - Initial Version
// 4/27/2022 - Added data members
// 4/27/2022 - Added constructor, destructor and general methods
// 4/27/2022 - Added get and set methods

#ifndef PROJECT3_EX_MEM_H
#define PROJECT3_EX_MEM_H

// --- Standard Library Includes ---

// --- User Built Includes ---

class EX_Mem {
public:
    // --- Constructor ---
    EX_Mem(); // default constructor
    EX_Mem(EX_Mem const&); //copy constructor

    // --- General Methods ---
    void copyDataToRead(EX_Mem const&);
    bool checkInstructionValues() const; //TODO::

    // --- Instruction Calculations Get Methods ---
    int getALUResult() const;
    int getSWValue() const;
    int getWriteRegNum() const;

    // --- Instruction Calculations Set Methods ---
    void setALUResult(int);
    void setSWValue(int);
    void setWriteRegNum(int);

    // --- Control Get Methods ---
    bool getMemRead() const;
    bool getMemWrite() const;
    bool getRegWrite() const;
    bool getMemToReg() const;

    // --- Control Set Methods ---
    void setMemRead(bool);
    void setMemWrite(bool);
    void setRegWrite(bool);
    void setMemToReg(bool);

    // --- Print Method ---
    void print() const;

    // --- Destructor ---
    ~EX_Mem();

private:
    // Instruction Calculated Information
    int ALUResult{0};
    int SWValue{0};
    int WriteRegNum{0};

    // Control Bits
    bool MemRead{false};
    bool MemWrite{false};
    bool RegWrite{false};
    bool MemToReg{false};

};


#endif //PROJECT3_EX_MEM_H
