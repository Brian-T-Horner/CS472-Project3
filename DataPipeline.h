// Data Pipeline Specification
//
// Author: Brian Horner
// Edit History:
// 4/26/2022 - Initial Version


#ifndef DATAPIPELINE_H
#define DATAPIPELINE_H

class DataPipeline{
public:
    // --- Constructor ---
    DataPipeline();

    // --- General Pipeline Functions
    void IF_stage(int []);
    void ID_stage();
    void EX_stage();
    void MEM_stage();
    void WB_stage();
    void print_out_everything();
    void copy_write_to_read();

    // --- Get Methods ---
    int getProgramCounter();

    // --- Set Methods ---
    void setProgramCounter(int);

    // --- Destructor ---
    ~DataPipeline();
private:
    int programCounter{0};
};
#endif DATAPIPELINE_H
