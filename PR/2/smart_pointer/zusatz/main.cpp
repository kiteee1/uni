#include <iostream>
#include <memory>
#include "player.h"
#include "campaign.h"
#include "hero.h"
#include "monster.h"
#include "hero_info.h"

int main()
{
    try
    {
        Player player1("John", "Doe");
        Player player2("Jane", "Smith");

        unsigned hero1_id = player1.create_hero("Thor", Hero_Class::FIGHTER, Hero_Species::HUMAN, 100, {{"Strength", 15}, {"Dexterity", 10}, {"Constitution", 12}, {"Intelligence", 8}, {"Wisdom", 7}, {"Charisma", 10}});
        unsigned hero2_id = player2.create_hero("Loki", Hero_Class::ROGUE, Hero_Species::ELF, 80, {{"Strength", 10}, {"Dexterity", 18}, {"Constitution", 10}, {"Intelligence", 14}, {"Wisdom", 10}, {"Charisma", 12}});

        player1.create_campaign("Save the Kingdom", 1, hero1_id);
        player2.create_campaign("Shadow Invasion", 1, hero2_id);

        player2.join_friends_campaign(player1, hero2_id); // This should make Loki leave the current campaign and join John's campaign

        std::cout << player1 << std::endl;
        std::cout << player2 << std::endl;

        player1.print_hero_logbook(hero1_id, std::cout);
        player2.print_hero_logbook(hero2_id, std::cout);

        player1.leave_campaign(hero1_id);

        std::cout << player1 << std::endl;
        std::cout << player2 << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}