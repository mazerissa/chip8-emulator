rom = bytes([
    0x60, 0x00,  # V0 = 0
    0x61, 0x00,  # V1 = 0
    0xA2, 0x0C,  # I = 0x20C
    0xD0, 0x15,  # Draw sprite at V0,V1 height 5
    0x12, 0x00,  # Loop

    # Sprite data (8x5)
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF
])

with open("roms/test.ch8", "wb") as f:
    f.write(rom)

print("ROM created")