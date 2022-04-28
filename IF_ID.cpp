// IF ID Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/27/2022 - Initial Version

// --- Standard Library Includes ---
#include <iostream>
// --- User Built Includes ----
#include "IF_ID.h"

// --- Constructor ---
IF_ID::IF_ID() {} // Default Constructor
IF_ID::IF_ID(IF_ID *referenceIF_ID) { // Copy Constructor
    if (referenceIF_ID->IF_ID_getInstruction() != 0){
            this->instruction = referenceIF_ID->IF_ID_getInstruction();
    }else{
        std::cout << "No data to use for copy constructor. Set to default "
                     "value" <<std::endl;
        this-> instruction = 0;
    }
}

// --- Copy Data Method ---
void IF_ID::copyDataToRead(IF_ID * referenceIF_ID) {
    this->instruction = referenceIF_ID->IF_ID_getInstruction();
}

// --- Get and Set Functions
int IF_ID::IF_ID_getInstruction() const {return this->instruction;}

void IF_ID::IF_ID_setInstruction(int newInstruction){
    this->instruction = newInstruction;
}

// --- Print Method ---
void IF_ID::print() const {
    std::cout <<"0x"<< std::uppercase<<std::hex << instruction <<std::endl;
}

// --- Destructor ---
IF_ID::~IF_ID() {}