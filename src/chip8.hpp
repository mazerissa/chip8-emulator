#pragma once // run once

#include <cstdint> // library of fixed-width integer types

// chip class
class Chip_8 {

    uint8_t memory[4096]; // 4KB of memory 

    uint8_t V[16]; // 16 registers

    uint16_t I; // Index register

    uint16_t pc; // Program counter
    
    uint16_t stack[16]; // Stack for subroutine calls

    uint8_t sp; // Stack pointer

    void initialize(); // reseting

    void emulateCycle(); // eun one cycle of CPU
}