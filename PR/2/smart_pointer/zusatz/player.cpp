#include "player.h"
#include "hero_info.h"
#include "hero.h"
#include "campaign.h"
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <stdexcept>

Player::Player(std::string first_name, std::string last_name) : first_name{first_name}, last_name{last_name}
{
    if (first_name.empty() || last_name.empty())
        throw std::runtime_error("Player Name Error");
}

unsigned Player::create_hero(const std::string &name, Hero_Class hero_class, Hero_Species hero_species, unsigned max_hp, const std::map<std::string, unsigned> &abilities)
{
    auto hero = std::make_shared<Hero>(name, hero_class, hero_species, max_hp, abilities);
    unsigned id = hero->get_id();
    heroes[id] = hero;
    return id;
}

void Player::create_campaign(std::string name, unsigned min_level, unsigned id)
{
    if (campaign)
        campaign.reset();

    campaign = std::make_unique<Campaign>(name, min_level);
    auto it = heroes.find(id);

    if (it == heroes.end())
        throw std::runtime_error("Hero not found create_campaign");

    // Zusatz
    if (it->second->is_in_campaign())
        it->second->leave_campaign();

    campaign->add_hero(it->second);
    it->second->join_campaign(*campaign);
}

void Player::join_friends_campaign(Player &pfriend, unsigned id)
{
    if (!pfriend.campaign)
        throw std::runtime_error("Friend has no campaign");

    auto it = heroes.find(id);

    if (it == heroes.end())
        throw std::runtime_error("Hero not found join_friends");

    // Zusatz
    if (it->second->is_in_campaign())
        it->second->leave_campaign();

    pfriend.campaign->add_hero(it->second);
    it->second->join_campaign(*pfriend.campaign);
}

void Player::transfer_campaign(Player &pfriend)
{
    if (!campaign)
        throw std::runtime_error("No campaign to transfer");

    if (pfriend.campaign)
        pfriend.campaign.reset();

    pfriend.campaign = std::move(campaign);
}

unsigned Player::remove_dead()
{
    unsigned count = 0;

    for (auto it = heroes.begin(); it != heroes.end();)
    {
        if (it->second->get_current_hp() == 0)
        {
            it = heroes.erase(it);
            ++count;
        }
        else
            ++it;
    }
    return count;
}

std::ostream &Player::print(std::ostream &o) const
{
    o << "[" << first_name << " " << last_name << ", {";
    bool first = true;
    for (const auto &pair : heroes)
    {
        if (!first)
            o << ", ";
        o << *pair.second;
        first = false;
    }
    o << "}, ";
    this->print_campaign(o);
    o << "]";
    return o;
}

std::ostream &Player::print_campaign(std::ostream &o) const
{
    if (campaign)
        o << *campaign;
    else
        o << "[]";
    return o;
}

void Player::campaign_encounter_monster(unsigned id, Monster &m)
{
    if (campaign.get())
        campaign.get()->encounter_monster(id, m);
    else
        throw std::runtime_error("Player does not have a campaign");
}

// Zusatz
void Player::leave_campaign(unsigned hero_id)
{
    auto it = heroes.find(hero_id);

    if (it == heroes.end())
        throw std::runtime_error("Hero not found");

    if (campaign)
    {
        campaign->remove_hero(it->second); // Pass the shared_ptr<Hero>
        it->second->leave_campaign();
    }
}

void Player::print_hero_logbook(unsigned hero_id, std::ostream &o) const
{
    auto it = heroes.find(hero_id);

    if (it == heroes.end())
        throw std::runtime_error("Hero not found");

    it->second->print_logbook(o);
}

std::ostream &operator<<(std::ostream &o, const Player &p) { return p.print(o); }
