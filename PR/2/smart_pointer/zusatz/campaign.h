#ifndef CAMPAIGN_H
#define CAMPAIGN_H
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include "hero.h"

class Hero;
class Monster;

class Campaign
{
private:
    std::string name;
    std::map<unsigned, std::weak_ptr<Hero>> heroes;
    unsigned min_level;

public:
    Campaign(std::string name, unsigned min_level);
    void add_hero(std::shared_ptr<Hero> h);
    void encounter_monster(unsigned id, Monster &m);
    unsigned remove_dead_and_expired();
    std::ostream &print(std::ostream &o) const;

    // Zusatz
    void remove_hero(std::shared_ptr<Hero> hero);
    std::string get_name() const;
};

std::ostream &operator<<(std::ostream &o, const Campaign &p);

#endif
