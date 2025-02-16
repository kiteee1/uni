#include "hero.h"
#include "hero_info.h"
#include "monster.h"
#include <string>
#include <cstdlib>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <stdexcept>

inline unsigned Hero::next_id = 0;

Hero::Hero(std::string name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string, unsigned> &abilities) : name{name}, hero_class{hero_class}, hero_species{hero_species}, max_hp{max_hp}, abilities{abilities}
{

    this->level = 1;
    this->id = next_id;
    this->current_hp = max_hp;

    if (name.empty())
        throw std::runtime_error("Emtpty Hero name");
    if (max_hp == 0)
        throw std::runtime_error("max_hp hero = 0");
    if (level <= 0 || level >= 21)
        throw std::runtime_error("Level must be greater than 0 and less than 21.");

    const std::unordered_set<std::string> valid_abilities(abilities_names.begin(), abilities_names.end());

    if (abilities.size() != valid_abilities.size())
        throw std::runtime_error("Map size != 6");

    for (const auto &ability : abilities)
    {
        if (valid_abilities.find(ability.first) == valid_abilities.end())
            throw std::runtime_error("Invalid map first");

        if (ability.second <= 0 || ability.second >= 21)
            throw std::runtime_error("Map second not in range");
    }
    ++next_id;
}

unsigned Hero::level_up()
{
    if (level < 20)
        ++level;
    return level;
}

bool Hero::fight(Monster &m)
{
    while (current_hp > 0 && !m.is_dead())
    {
        unsigned damage_to_monster = level * std::max_element(abilities.begin(), abilities.end(), [](const auto &a, const auto &b)
                                                              { return a.second < b.second; })
                                                 ->second;
        m.take_damage(damage_to_monster);

        if (!m.is_dead())
        {
            unsigned damage_to_hero = m.get_attack();
            current_hp = (damage_to_hero >= current_hp) ? 0 : current_hp - damage_to_hero;
        }
    }
    return current_hp > 0;
}

std::ostream &Hero::print(std::ostream &o) const
{
    o << "[" << id << ", " << name << ", (" << hero_class << ", " << hero_species << ", " << level << "), {";

    bool first = true;
    for (const auto &ability : abilities)
    {
        if (!first)
            o << ", ";
        o << ability.second;
        first = false;
    }

    o << "}, (" << current_hp << "/" << max_hp << ") HP]";
    return o;
}

unsigned Hero::get_level() const { return level; }
unsigned Hero::get_id() const { return id; }
unsigned Hero::get_current_hp() const { return current_hp; }
Hero_Class Hero::get_hero_class() const { return hero_class; }

std::ostream &operator<<(std::ostream &o, const Hero &obj) { return obj.print(o); }
