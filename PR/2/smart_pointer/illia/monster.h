#ifndef MONSTER_H
#define MONSTER_H
#include<iostream>
#include<string>

class Monster{
private:
    std::string name;
    unsigned health;
    unsigned attack;
public:
  	// Getters
    std::string get_name() const {
        return name;
    }
    unsigned get_health() const {
        return health;
    }
    unsigned get_attack() const {
        return attack;
    }

    // Constructor / Destructor
    Monster(std::string name, unsigned health, unsigned attack){
        if(name.empty() || health == 0 || attack == 0)
            throw std::runtime_error("Monster error {name/health/attack}");
        this->name = name;
        this->health = health;
        this->attack = attack;
    }

    virtual ~Monster(){}

    // Functions
    virtual unsigned calculate_damage(unsigned dmg) const = 0;
  
    void take_damage(unsigned dmg){
      	if (calculate_damage(dmg) < health)
            health -= calculate_damage(dmg);
        else    
            health = 0;
    }
    bool is_dead() const {
        return health == 0;
    }
    virtual std::string additional_information() const = 0;

    friend std::ostream& operator<<(std::ostream& o, const Monster& h){
        o << "[" << h.name << ", " << h.health << " HP, " << h.attack << " ATK" << h.additional_information() << "]";
        return o;
    } 
};

class Elite_Monster : public Monster {
private:
    unsigned defense;
public:
    unsigned get_defense() const {
        return defense;
    }

    // Constructor
    Elite_Monster(std::string name, unsigned health, unsigned attack, unsigned defense): Monster(name, health, attack){
        if(defense <= 0)
            throw std::runtime_error("Elite_Monter defence ist 0");
        this->defense = defense;  
    }

    // Functions
    unsigned calculate_damage(unsigned dmg) const override {
        return dmg > defense ? dmg - defense : 0;
    }
    
    std::string additional_information() const override {
        return ", " + std::to_string(defense) + " DEF";
    }
};

class Standard_Monster : public Monster {
public:
    // Constructor
    Standard_Monster(std::string name, unsigned health, unsigned attack) : Monster(name, health, attack){}

    // Functions
    unsigned calculate_damage(unsigned dmg) const override {
        return dmg;
    }
    std::string additional_information() const override {
        return "";
    }
};
    
#endif
