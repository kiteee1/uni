#ifndef HERO_H
#define HERO_H

#include "monster.h"
#include "hero_info.h"

#include <string>
#include <iostream>
#include <map>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <stdexcept>


class Hero{
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
public:
    unsigned get_id() const {
        return id;
    }
    std::string get_name() const {
        return name;
    }
    Hero_Class get_hero_class() const {
    		return hero_class;
    }
    Hero_Species get_hero_species() const {
        return hero_species;
    }
    unsigned get_level() const {
        return level;
    }
    unsigned get_max_hp() const {
        return max_hp;
    }
    unsigned get_current_hp() const {
        return current_hp;
    }
  	

    // Constructor
    Hero(std::string name, Hero_Class classH, Hero_Species speciesH, unsigned max_hp, const std::map<std::string, unsigned>& abilities): hero_class(classH), hero_species(speciesH){
        if(name.empty() || max_hp <= 0)
        	throw std::runtime_error("Error::Hero Name is empty of hp <=0");
        else if (abilities.size() != 6)
           throw std::runtime_error("Error::Hero Too few or to many abilities!!");
      
        if(abilities.size() == 6){
            for(const auto& pair : abilities){
                if(std::find(abilities_names.begin(), abilities_names.end(), pair.first) == abilities_names.end())
                    throw std::runtime_error("Wrong name of the abilitie!!");
                if(pair.second <= 0 || pair.second >= 21)
                    throw std::runtime_error("Wrong value of the abilitie!!");
            }
            this->abilities = abilities;
          	this->level = 1;
            this->name = name;
          	this->id = this->next_id++;
	          this->max_hp = max_hp;
            this->current_hp = this->max_hp;
            
            
        }    
           
    }
    
    // Functions
    unsigned level_up(){
        if(level < 20)
            level++;
        return level;
    }

    bool fight(Monster& m){
    	while(current_hp){
        // std::cout << "Current_hp: " << current_hp << std::endl;
        unsigned max {0};
        for(const auto& [k, v]: abilities){
            v > max ? max = v : max += 0;
        }
        while(current_hp){
            m.take_damage(max * level); 
            if(m.is_dead())
                return true;
            else{
                if(current_hp > m.get_attack())
                    current_hp -= m.get_attack();
                else    
                    current_hp = 0;
            }
        }
      }
      return false;
    }

    friend std::ostream& operator<<(std::ostream& o, const Hero& obj){
        bool first{true};
        o << "[" << obj.id << ", " << obj.name << ", (" << obj.hero_class << ", " << obj.hero_species << ", " << obj.level << "), {";
        for(const auto& pair : obj.abilities){
            if(first){
                o << pair.second;
                first = false;
            } else {
                o << ", " << pair.second;
            }
        }
        o << "}, (" << obj.current_hp << "/" << obj.max_hp << ") HP]";
        return o;
    }
};

inline unsigned Hero::next_id = 0;

#endif
