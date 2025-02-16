#ifndef HERO_INFO_H
#define HERO_INFO_H

#include <iostream>
#include <vector>

enum Hero_Class { BARBARIAN, BARD, CLERIC, DRUID, FIGHTER, MONK, PALADIN, RANGER, ROGUE, SORCERER, WARLOCK, WIZARD };
enum Hero_Species { DRAGONBORN, DWARF, ELF, GNOME, HALF_ELF, HALFLING, HALF_ORC, HUMAN, TIEFLING };
const std::vector<std::string> hero_class_names{"Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue", "Sorcerer", "Warlock", "Wizard"};
const std::vector<std::string> hero_species_names{"Dragonborn", "Dwarf", "Elf", "Gnome", "Half-Elf", "Halfling", "Half-Orc", "Human", "Tiefling"};
const std::vector<std::string> abilities_names{"Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"};


inline std::ostream& operator<<(std::ostream& o, Hero_Class m){
    o << hero_class_names.at(static_cast<int>(m));
    return o;
}

inline std::ostream& operator<<(std::ostream& o, Hero_Species m){
    o << hero_species_names.at(static_cast<int>(m));
    return o;
}

#endif
