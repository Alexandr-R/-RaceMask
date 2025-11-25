# RaceMask Utility

Small console helper to work with race masks for a World of Warcraft–like server/core.  
It can:

- Build a bitmask from selected race IDs
- Decode an existing bitmask back into race IDs

The list of races is hardcoded in the program (Human, Orc, Blood Elf, Draenei, Vulpera, etc.). :contentReference[oaicite:0]{index=0}

---

## Features

1. **Build mask from race IDs**

   - Shows all available races with:
     - numeric ID  
     - enum code (e.g. `RACE_HUMAN`)  
     - human-readable name (e.g. `Human`)
   - You enter several IDs (e.g. `1 3 10`)
   - Program prints the bit value for each race and the final mask in:
     - decimal
     - hexadecimal (e.g. `0x1234`)

2. **Decode mask to race IDs**

   - You enter an existing mask:
     - either decimal (e.g. `123456`)
     - or hexadecimal with `0x` prefix (e.g. `0x1F`)
   - Program prints:
     - each race contained in the mask  
     - its ID, enum code and bit value (both decimal and hex)

---

## Build

You only need a C++ compiler with C++11+ support (tested with C++17).

Example (g++ / clang++):

```bash
g++ -std=c++17 -O2 Racemask_calc.cpp -o racemask
