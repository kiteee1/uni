#ifndef PLAYER_H
#define PLAYER_H

#include "campaign.h"
#include "hero_info.h"
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <cstdlib>
#include <stdexcept>

class Player
{
private:
    std::string first_name;
    std::string last_name;
    std::map<unsigned, std::shared_ptr<Hero>> heroes;
    std::unique_ptr<Campaign> campaign;

public:
    Player(std::string first_name, std::string last_name);
    unsigned create_hero(const std::string &name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string, unsigned> &abilities);
    void create_campaign(std::string name, unsigned min_level, unsigned id);
    void join_friends_campaign(Player &pfriend, unsigned id);
    void transfer_campaign(Player &pfriend);
    unsigned remove_dead();
    std::ostream &print_campaign(std::ostream &) const;
    std::ostream &print(std::ostream &o) const;
    void campaign_encounter_monster(unsigned id, Monster &m);

    // Zusatz
    void leave_campaign(unsigned hero_id);
    void print_hero_logbook(unsigned hero_id, std::ostream &o) const;
};

std::ostream &operator<<(std::ostream &o, const Player &p);

#endif
