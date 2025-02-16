#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include "hero.h"
#include "campaign.h"
#include "monster.h"

Campaign::Campaign(std::string name, unsigned min_level) : name{name}, min_level{min_level}
{
    if (name.empty())
        throw std::runtime_error("Campaign Name Empty");
    if (min_level <= 0)
        throw std::runtime_error("Min Level <=0");
}

void Campaign::add_hero(std::shared_ptr<Hero> h)
{
    if (heroes.find(h->get_id()) != heroes.end() || h->get_level() < min_level)
        throw std::runtime_error("add_hero error");
    heroes[h->get_id()] = h;
}

void Campaign::encounter_monster(unsigned id, Monster &m)
{
    auto it = heroes.find(id);
    if (it == heroes.end())
        throw std::runtime_error("Hero not in campaign.");

    auto hero = it->second.lock();
    if (hero && hero->fight(m))
        hero->level_up();
}

unsigned Campaign::remove_dead_and_expired()
{
    unsigned count = 0;
    for (auto it = heroes.begin(); it != heroes.end();)
    {
        auto hero = it->second.lock();
        if (!hero || hero->get_current_hp() == 0)
        {
            it = heroes.erase(it);
            ++count;
        }
        else
            ++it;
    }
    return count;
}

std::ostream &Campaign::print(std::ostream &o) const
{
    o << "[" << name << " Campaign, Min_Level " << min_level << ", {";
    bool first = true;
    for (const auto &pair : heroes)
    {
        auto hero = pair.second.lock();
        if (hero)
        {
            if (!first)
                o << ", ";
            o << *hero;
            first = false;
        }
    }
    o << "}]";
    return o;
}

// Zusatz
void Campaign::remove_hero(std::shared_ptr<Hero> hero)
{
    auto it = heroes.find(hero->get_id());
    if (it != heroes.end())
    {
        heroes.erase(it);
    }
}

std::string Campaign::get_name() const
{
    return name;
}

std::ostream &operator<<(std::ostream &o, const Campaign &p) { return p.print(o); }