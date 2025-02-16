#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>
#include <string>
#include <stdexcept>

class Monster
{
private:
    std::string name;
    unsigned health;
    unsigned attack;

public:
    Monster(std::string name, unsigned health, unsigned attack);
    virtual ~Monster();
    virtual unsigned calculate_damage(unsigned dmg) const = 0;
    void take_damage(unsigned dmg);
    bool is_dead() const;
    virtual std::string additional_information() const = 0;
    std::ostream &print(std::ostream &o) const;
    unsigned get_attack() const;
};

std::ostream &operator<<(std::ostream &o, const Monster &h);

class Elite_Monster : public Monster
{
private:
    unsigned defense;

public:
    Elite_Monster(std::string name, unsigned health, unsigned attack, unsigned defense);
    unsigned calculate_damage(unsigned dmg) const override;
    std::string additional_information() const override;
};

class Standard_Monster : public Monster
{
public:
    Standard_Monster(std::string name, unsigned health, unsigned attack);
    unsigned calculate_damage(unsigned dmg) const override;
    std::string additional_information() const override;
};

#endif
