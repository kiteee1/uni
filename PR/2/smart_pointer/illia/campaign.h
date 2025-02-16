#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include<iostream>
#include<string>
#include<memory>
#include<map>

#include"hero.h"

class Campaign{
private:
    std::string name;
    std::map<unsigned, std::weak_ptr<Hero>> mapHeros;
    unsigned min_level;
public:
    std::string get_name() const {
        return name;
    }
    unsigned get_min_level() const {
        return min_level;
    }
   
    // Constructor
    Campaign(std::string name, unsigned min_level){
        if(name.empty() || min_level <= 0)
            throw std::runtime_error("Compaign error {name/min_level}");
        this->name = name;
        this-> min_level = min_level;
    }

    //Functions
    void add_hero(std::shared_ptr<Hero> h){
        if(h->get_level() < min_level || mapHeros.find(h->get_id()) != mapHeros.end())
            throw std::runtime_error("The level is to low or the is already a Hero in a campaign");
        else
            mapHeros[h->get_id()] = std::weak_ptr<Hero>(h);
    }

    void encounter_monster(unsigned id, Monster& m){
        if(mapHeros.find(id) != mapHeros.end()){
            std::weak_ptr<Hero> help = mapHeros[id];
            if(help.lock()->fight(m)){
                help.lock()->level_up();
            }
        }
    }

    unsigned remove_dead_and_expired(){
        unsigned count = 0;
        for (auto it = mapHeros.begin(); it != mapHeros.end(); ) {
            if (it->second.expired() || it->second.lock()->get_current_hp() <= 0) {
                it = mapHeros.erase(it);
                count++;
            } else {
                ++it;
            }
        }
        return count;
    }

    friend std::ostream& operator<<(std::ostream& o, const Campaign& p){
        o << "[" << p.name << " Campaign, Min_Level " << p.min_level << ", {";
        bool first {true};
        for(const auto& [k, v] : p.mapHeros){
          if(!v.expired()){
            if(first) {
                o << *(v.lock());
              	first = false;
            }
            else   
                o << ", " << *(v.lock());
          }
        }
        o << "}]";
        return o;
    }
};


#endif
