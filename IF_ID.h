// If ID Class SPecification
//
// Author: Brian Horner
// Edit History:
// 4/27/2022 - Initial Version
// 4/27/2022 - Added instruction private member
// 4/27/2022 - Added instruction get and set methods
// 4/27/2022 - Changed methods that passed pointer to ID_EX object to const
// reference

#ifndef PROJECT3_IF_ID_H
#define PROJECT3_IF_ID_H


class IF_ID {
public:
    IF_ID(); // Default Constructor
    IF_ID(IF_ID const &); // Copy Constructor

    // --- Copy Data Method ---
    IF_ID copyDataToRead(IF_ID const&);

    // --- Get and Set Methods ---
    void setInstruction(int64_t);
    int64_t getInstruction() const;

    // --- Print Method ---
    void print() const;

    //--- Destructor ---
    ~IF_ID();
private:
    int64_t instruction{0};

};


#endif
