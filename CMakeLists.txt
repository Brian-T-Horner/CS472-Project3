cmake_minimum_required(VERSION 3.20)
project(Project3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project3 main.cpp DataPipeline.cpp IF_ID.cpp
               ID_EX.cpp EX_Mem.cpp  Mem_WB.cpp)
