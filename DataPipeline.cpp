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

IF_ID IF_ID_Write;
IF_ID IF_ID_Read(IF_ID_Write);
ID_EX ID_EX_Write;
ID_EX ID_EX_Read(ID_EX_Write);
EX_Mem EX_Mem_Write;
EX_Mem EX_Mem_Read(EX_Mem_Write);
Mem_WB Mem_WB_Write;
Mem_WB Mem_WB_Read(Mem_WB_Write);

// --- Constructor ---
DataPipeline::DataPipeline() {

}

// --- General Pipeline Functions ---
void DataPipeline::copy_write_to_read() {
    IF_ID_Read.copyDataToRead(IF_ID_Write);
    ID_EX_Read.copyDataToRead(ID_EX_Write);
    EX_Mem_Read.copyDataToRead(EX_Mem_Write);
}

// --- Get Methods ---
int DataPipeline::getProgramCounter() {return this->programCounter;}
// --- Set Methods ---
void DataPipeline::setProgramCounter(int newProgramCounter) {
    this->programCounter = newProgramCounter;
}
// --- Destructor ---
DataPipeline::~DataPipeline() {}