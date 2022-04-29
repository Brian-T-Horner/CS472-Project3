// Data Pipeline Specification
//
// Author: Brian Horner
// Edit History:
// 4/26/2022 - Initial Version

// --- User Built Includes ---
#include "ID_EX.h"


#ifndef DATAPIPELINE_H
#define DATAPIPELINE_H

class DataPipeline{
public:
    // --- Constructor ---
    DataPipeline();

    // --- General Pipeline Functions
    void IF_stage(int64_t);
    void ID_stage();
    void EX_stage();
    void MEM_stage();
    void WB_stage();
    void print_out_everything();
    void copy_write_to_read();
    void resetIDStage(ID_EX &);

    // --- Get Methods ---
    int getClockCycle();

    // --- Set Methods ---
    void setClockCycle(int);

    // Clock Cycle Adder
    void addToClockCycle(int);

    // --- Destructor ---
    ~DataPipeline();
private:
    int ClockCycle{0};
};
#endif
