with open("roms/test.ch8", "wb") as rom:
    rom.write(bytes([
        0x60, 0x0A,
        0x61, 0x05,
        0x70, 0x05
    ]))