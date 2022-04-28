// If ID Class SPecification
//
// Author: Brian Horner
// Edit History:
// 4/27/2022 - Initial Version

#ifndef PROJECT3_IF_ID_H
#define PROJECT3_IF_ID_H


class IF_ID {
public:
    IF_ID(); // Default Constructor
    IF_ID(IF_ID*); // Copy Constructor

    // --- Copy Data Method ---
    void copyDataToRead(IF_ID*);

    // --- Get and Set Methods ---
    void IF_ID_setInstruction(int);
    int IF_ID_getInstruction() const;

    // --- Print Method ---
    void print() const;

    //--- Destructor ---
    ~IF_ID();
private:
    int instruction;

};


#endif //PROJECT3_IF_ID_H
