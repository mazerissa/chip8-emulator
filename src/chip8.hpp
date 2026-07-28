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

    void updateTimers();


public:

    std::array<uint8_t, 4096> memory{};

    std::array<uint8_t, 16> V{};

    std::array<uint16_t, 16> stack{};

    std::array<uint8_t, 64 * 32> display{};

    std::array<uint8_t, 16> keypad{};


    uint16_t I{0};

    uint16_t pc{0x200};

    uint8_t sp{0};


    uint8_t delay_timer{0};

    uint8_t sound_timer{0};


    bool drawFlag{false};


private:

    void loadFontset();

};