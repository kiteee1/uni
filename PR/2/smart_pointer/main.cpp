#include "Hero.h"
#include "Monster.h"
#include "Campaign.h"
#include "Player.h"
#include <iostream>

int main()
{
    try
    {
        std::map<std::string, unsigned> abilities1 = {
            {"Strength", 10}, {"Dexterity", 12}, {"Constitution", 14}, {"Intelligence", 16}, {"Wisdom", 18}, {"Charisma", 20}};

        std::map<std::string, unsigned> abilities2 = {
            {"Strength", 8}, {"Dexterity", 10}, {"Constitution", 12}, {"Intelligence", 14}, {"Wisdom", 16}, {"Charisma", 18}};

        // Create heroes
        auto hero1 = std::make_shared<Hero>("John Doe", Hero_Class::BARBARIAN, Hero_Species::HALF_ELF, 100, abilities1, 5);
        auto hero2 = std::make_shared<Hero>("Jane Doe", Hero_Class::WIZARD, Hero_Species::HUMAN, 80, abilities2, 8);

        // Create monsters
        Standard_Monster monster1("Goblin", 50, 8);
        Elite_Monster monster2("Dragon", 150, 20, 10);

        // Create players
        Player player1("Alice", "Smith");
        Player player2("Bob", "Johnson");

        // Player1 creates heroes
        unsigned hero1_id = player1.create_hero("John Doe", Hero_Class::BARBARIAN, Hero_Species::HALF_ELF, 100, abilities1);
        unsigned hero2_id = player1.create_hero("Jane Doe", Hero_Class::WIZARD, Hero_Species::HUMAN, 80, abilities2);

        // Player1 creates a campaign
        player1.create_campaign("Epic Quest", 5, hero1_id);

        // Player2 joins Player1's campaign with hero2
        player1.join_friends_campaign(player2, hero2_id);

        // Encounter monsters
        player1.create_campaign("Another Quest", 5, hero2_id);
        player1.create_campaign("Epic Quest", 5, hero1_id);
        player1.join_friends_campaign(player2, hero2_id);
        player1.create_campaign("Third Quest", 5, hero2_id);
        player1.transfer_campaign(player2);

        // Remove dead heroes
        unsigned removed_count = player1.remove_dead();
        std::cout << "Removed " << removed_count << " expired heroes." << std::endl;

        // Print campaigns
        std::cout << player1 << std::endl;
        std::cout << player2 << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}