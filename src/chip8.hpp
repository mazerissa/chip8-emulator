#pragma once

#include <array>
#include <cstdint>
#include <string>

class Chip_8 
{
public:

    void initialize();
    bool loadROM(const std::string& filename);
    void emulateCycle();

    std::array<uint8_t, 4096> memory{};
    std::array<uint8_t, 16>   V{};
    std::array<uint16_t, 16>  stack{};

    uint16_t I{0};
    uint16_t pc{0};
    uint8_t  sp{0};
};