// IF ID Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/27/2022 - Initial Version
// 4/27/2022 - Initial Version
// 4/27/2022 - Added instruction private member
// 4/27/2022 - Added instruction get and set methods
// 4/27/2022 - Changed methods that passed pointer to ID_EX object to const
// reference

// --- Standard Library Includes ---
#include <iostream>
// --- User Built Includes ----
#include "IF_ID.h"

// --- Constructor ---
IF_ID::IF_ID() {} // Default Constructor
IF_ID::IF_ID(IF_ID const &referenceIF_ID) { // Copy Constructor
    if (referenceIF_ID.getInstruction() != 0){
        setInstruction(referenceIF_ID.getInstruction());
    }else{
        std::cout << "No data to use for copy constructor. Set to default "
                     "value" <<std::endl;
        this-> instruction = 0;
    }
}

// --- Copy Data Method ---
IF_ID IF_ID::copyDataToRead(IF_ID  const &referenceIF_ID) {
    setInstruction(referenceIF_ID.getInstruction());
}

// --- Get and Set Functions
int64_t IF_ID::getInstruction() const {return instruction;}
void IF_ID::setInstruction(int64_t newInstruction){instruction = newInstruction;}

// --- Print Method ---
void IF_ID::print() const {
    std::cout <<"0x"<< std::uppercase<<std::hex << instruction <<std::endl;
}

// --- Destructor ---
IF_ID::~IF_ID() {}