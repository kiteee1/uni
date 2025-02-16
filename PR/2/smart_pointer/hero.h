#ifndef HERO_H
#define HERO_H

#include "hero_info.h"
#include <string>
#include <iostream>
#include <map>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <algorithm>
#include <vector>

class Monster;

class Hero
{
private:
    unsigned id;
    std::string name;
    Hero_Class hero_class;
    Hero_Species hero_species;
    unsigned level;
    unsigned max_hp;
    unsigned current_hp;
    std::map<std::string, unsigned> abilities;
    static unsigned next_id;

    //Zusatz
    bool in_campaign;
    std::vector<Campaign> campaigns_history;

public:
    Hero(std::string name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string, unsigned> &abilities);
    unsigned level_up();
    bool fight(Monster &m);
    std::ostream &print(std::ostream &o) const;
    unsigned get_level() const;
    unsigned get_id() const;
    unsigned get_current_hp() const;
    Hero_Class get_hero_class() const;

    //Zusatz
    bool check_campaign_presence();
};

std::ostream &operator<<(std::ostream &o, const Hero &obj);

#endif
