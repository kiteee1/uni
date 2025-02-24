#include "monster.h"

Monster::Monster(std::string name, unsigned health, unsigned attack) : name{name}, health{health}, attack{attack}
{
    if (name.empty())
        throw std::runtime_error("Name Monster empty");
    if (health == 0)
        throw std::runtime_error("Health 0 monster");
    if (attack == 0)
        throw std::runtime_error("Health 0 monster");
}

Monster::~Monster() {}

void Monster::take_damage(unsigned dmg)
{
    unsigned received_damage = calculate_damage(dmg);
    if (health > received_damage)
        health -= received_damage;
    else
        health = 0;
}

bool Monster::is_dead() const
{
    return health == 0;
}

std::ostream &Monster::print(std::ostream &o) const
{
    o << "[" << this->name << ", " << this->health << " HP, " << this->attack << " ATK" << this->additional_information() << "]";
    return o;
}

unsigned Monster::get_attack() const { return attack; }

std::ostream &operator<<(std::ostream &o, const Monster &h) { return h.print(o); }

Elite_Monster::Elite_Monster(std::string name, unsigned health, unsigned attack, unsigned defense) : Monster{name, health, attack}
{
    if (defense == 0)
    {
        throw std::runtime_error("Defense 0 monster");
    }
    this->defense = defense;
}

unsigned Elite_Monster::calculate_damage(unsigned dmg) const
{
    if (dmg > defense)
        return dmg - defense;
    else
        return 0;
}

std::string Elite_Monster::additional_information() const { return std::string(", ") + std::to_string(this->defense) + std::string(" DEF"); }

Standard_Monster::Standard_Monster(std::string name, unsigned health, unsigned attack) : Monster{name, health, attack} {}

unsigned Standard_Monster::calculate_damage(unsigned dmg) const { return dmg; }

std::string Standard_Monster::additional_information() const { return ""; }
