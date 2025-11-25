/*
 * Copyright (c) 2025 Alexander Petrov
 *  alexandr_petrov_@mail.ru
 * –азрешаетс€ использование, копирование и модификаци€ этого файла
 * при условии сохранени€ данного уведомлени€ об авторских правах.
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <limits>

struct RaceInfo
{
    int id;
    const char* code;   // enum name
    const char* title;  // human-readable name
};

static const std::vector<RaceInfo> RACES = {
    { 0,  "RACE_NONE",              "None" },
    { 1,  "RACE_HUMAN",             "Human" },
    { 2,  "RACE_ORC",               "Orc" },
    { 3,  "RACE_DWARF",             "Dwarf" },
    { 4,  "RACE_NIGHTELF",          "Night Elf" },
    { 5,  "RACE_UNDEAD_PLAYER",     "Undead" },
    { 6,  "RACE_TAUREN",            "Tauren" },
    { 7,  "RACE_GNOME",             "Gnome" },
    { 8,  "RACE_TROLL",             "Troll" },
    { 9,  "RACE_VULPERA",           "Vulpera" },
    { 10, "RACE_BLOODELF",          "Blood Elf" },
    { 11, "RACE_DRAENEI",           "Draenei" },
    { 12, "RACE_WORGEN",            "Worgen" },
    { 13, "RACE_NIGHTBORNELF",      "Nightborne Elf" },
    { 14, "RACE_HIGHELF",           "High Elf" },
    { 15, "RACE_VOIDELF",           "Void Elf" },
    { 16, "RACE_EREDAR",            "Eredar" },
    { 17, "RACE_DRACTHYR_H",        "Dracthyr (Horde)" },
    { 18, "RACE_TROLL_ZANDALARI",   "Zandalari Troll" },
    { 19, "RACE_LIGHTFORGED",       "Lightforged" },
    { 20, "RACE_GOBLIN",            "Goblin" },
    { 21, "RACE_PANDAREN_H",        "Pandaren (Horde)" },
    { 22, "RACE_PANDAREN_A",        "Pandaren (Alliance)" },
    { 23, "RACE_ILLIDARI_BLOODELF", "Illidari Blood Elf" },
    { 24, "RACE_DARKIRONDWARF",     "Dark Iron Dwarf" },
    { 25, "RACE_DRACTHYR_A",        "Dracthyr (Alliance)" },
    { 26, "RACE_KULTIRAN",          "Kul Tiran" },
    { 27, "RACE_ILLIDARI_NIGHTELF", "Illidari Night Elf" },
};

const RaceInfo* FindRaceById(int id)
{
    for (auto const& r : RACES)
        if (r.id == id)
            return &r;
    return nullptr;
}

// 2^(id-1). For id <= 0 returns 0.
uint64_t RaceMaskFromId(int id)
{
    if (id <= 0)
        return 0;
    return 1ull << (id - 1);
}

void PrintRaceList()
{
    std::cout << "Available races:\n";
    for (auto const& r : RACES)
    {
        std::cout << "  " << std::setw(2) << r.id
            << " : " << std::setw(22) << std::left << r.code
            << " (" << r.title << ")\n";
    }
    std::cout << std::endl;
}

void ModeFromRacesToMask()
{
    PrintRaceList();
    std::cout << "Enter race IDs separated by spaces (e.g. 1 3 10), then press Enter:\n> ";

    std::string line;
    std::getline(std::cin, line);
    if (line.empty())
        std::getline(std::cin, line);

    std::istringstream iss(line);
    int id;
    uint64_t maskSum = 0;

    while (iss >> id)
    {
        const RaceInfo* r = FindRaceById(id);
        if (!r)
        {
            std::cout << "  [WARN] Unknown race ID: " << id << "\n";
            continue;
        }

        uint64_t m = RaceMaskFromId(id);
        maskSum |= m;

        std::cout << "  Added: " << r->code
            << " (id=" << id << "), mask = " << m
            << " (0x" << std::hex << m << std::dec << ")\n";
    }

    std::cout << "\nResulting mask:\n";
    std::cout << "  decimal: " << maskSum << "\n";
    std::cout << "  hex:     0x" << std::hex << maskSum << std::dec << "\n\n";
}

void ModeFromMaskToRaces()
{
    std::cout << "Enter mask sum (decimal or 0x.. for hex):\n> ";

    std::string s;
    std::getline(std::cin, s);
    if (s.empty())
        std::getline(std::cin, s);

    uint64_t mask = 0;

    if (s.rfind("0x", 0) == 0 || s.rfind("0X", 0) == 0)
    {
        std::stringstream ss;
        ss << std::hex << s;
        ss >> mask;
    }
    else
    {
        std::stringstream ss;
        ss << s;
        ss >> mask;
    }

    std::cout << "Mask: " << mask
        << " (0x" << std::hex << mask << std::dec << ")\n";

    std::cout << "Races in mask:\n";

    bool any = false;
    for (auto const& r : RACES)
    {
        uint64_t m = RaceMaskFromId(r.id);
        if (m != 0 && (mask & m))
        {
            any = true;
            std::cout << "  id=" << std::setw(2) << r.id
                << "  code=" << std::setw(22) << std::left << r.code
                << "  bitMask=" << m
                << " (0x" << std::hex << m << std::dec << ")\n";
        }
    }

    if (!any)
        std::cout << "  (no races found in this mask)\n";

    std::cout << std::endl;
}

int main()
{
    for (;;)
    {
        std::cout << "==== RaceMask Utility ====\n";
        std::cout << "1) Build mask from race IDs\n";
        std::cout << "2) Decode mask to race IDs\n";
        std::cout << "0) Exit\n";
        std::cout << "> ";

        int choice = -1;
        if (!(std::cin >> choice))
            return 0;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
            ModeFromRacesToMask();
            break;
        case 2:
            ModeFromMaskToRaces();
            break;
        default:
            std::cout << "Unknown option.\n\n";
            break;
        }
    }

    return 0;
}
