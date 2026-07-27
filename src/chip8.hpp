#pragma once

#include <array>
#include <cstdint>

class Chip_8 
{
public:

    void initialize();
    void emulateCycle();

    std::array<uint8_t, 4096> memory{};
    std::array<uint8_t, 16>   V{};
    std::array<uint16_t, 16>  stack{};

    uint16_t I{0};
    uint16_t pc{0};
    uint8_t  sp{0};
};