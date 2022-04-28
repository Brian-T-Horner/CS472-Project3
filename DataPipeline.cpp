// Data Pipeline Class Implementation
//
// Author: Brian Horner
// Edit History:
// 4/26/2022 - Initial Version

// --- Standard Library Includes ---

// --- User Build Includes ---
#include "DataPipeline.h"
#include "IF_ID.h"
#include "ID_EX.h"
#include "EX_Mem.h"
#include "Mem_WB.h"

// --- Constructor ---
DataPipeline::DataPipeline() {
    IF_ID IF_ID_Write;
    IF_ID IF_ID_Read;
    ID_EX ID_EX_Write;
    ID_EX ID_EX_Read;
    EX_Mem EX_Mem_Write;
    EX_Mem EX_Mem_Read;
    Mem_WB Mem_WB_Write;
    Mem_WB Mem_WB_Read;
}

// --- General Pipeline Functions ---

// --- Get Methods ---
int DataPipeline::getProgramCounter() {return this->programCounter;}
// --- Set Methods ---
void DataPipeline::setProgramCounter(int newProgramCounter) {
    this->programCounter = newProgramCounter;
}
// --- Destructor ---
DataPipeline::~DataPipeline() {}