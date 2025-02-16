#ifndef PLAYER_H
#define PLAYER_H

#include"campaign.h"
#include "hero.h"

#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <cstdlib>
#include <stdexcept>

class Player{
private:
    std::string first_name;
    std::string last_name;
    std::map<unsigned, std::shared_ptr<Hero>> heroes;
    std::unique_ptr<Campaign> campaign;
public:
    std::string get_first_name() const {
        return first_name;
    }
    std::string get_last_name() const {
        return last_name;
    }

    // Constructor
    Player(std::string first_name, std::string last_name){
        if(first_name.empty() || last_name.empty())
            throw std::runtime_error("Player name is empty");
        this->first_name = first_name;
        this->last_name = last_name;
    }

    // Functions
    unsigned create_hero(const std::string& name, Hero_Class classH, Hero_Species speciesH, unsigned health, const std::map<std::string, unsigned>& abilities) {
        //Hero* hero1 = new Hero(name, classH, speciesH, health, abilities);
        std::shared_ptr<Hero> heroPtr = std::make_shared<Hero>(name, classH, speciesH, health, abilities);
        heroes[heroPtr->get_id()] = heroPtr; 
        return heroPtr->get_id();
    }

    void create_campaign(std::string name, unsigned min_level, unsigned id){
        std::unique_ptr<Campaign> newCampaign = std::make_unique<Campaign>(name, min_level);
        if (heroes.find(id) != heroes.end()) {
            std::shared_ptr<Hero> heroPtr = heroes.find(id)->second;
            if (heroPtr) 
                newCampaign->add_hero(heroPtr);
            else 
                throw std::runtime_error("The hero has expired");
            
        } else  
            throw std::runtime_error("Player no hero in the map");
      
      	if(campaign.get())
          campaign.release();
              
	      //this->campaign = std::move(newCampaign);
      	this->campaign.swap(newCampaign);
      	
    }

    void join_friends_campaign(Player& f, unsigned id){
        if(f.campaign.get() != nullptr){
            if(heroes.find(id) != heroes.end())
                f.campaign->add_hero(heroes[id]);
          	else
              throw std::runtime_error("A hero does not exist");
        }
        else 
            throw std::runtime_error("Friend does not have a campaign");
    }

    void transfer_campaign(Player& pfriend){
        if(campaign.get() == nullptr)
            throw std::runtime_error("Player does not have a campaign");
      	if(pfriend.campaign.get() != nullptr)
          	pfriend.campaign.release();

        pfriend.campaign = std::move(campaign);
    }

    unsigned remove_dead(){
        unsigned count {0};
        for(auto it = heroes.begin(); it != heroes.end();){
            if(it->second->get_current_hp() <= 0){
              	it = heroes.erase(it);
                count++;
            } else {
            	it++;
            }
        }
        return count;
    }

  	void campaign_encounter_monster(unsigned id,Monster& m){
    	if(campaign.get())
      	campaign.get()->encounter_monster(id, m);
      else 
        throw std::runtime_error("Player does not have a campaign");
    }
  
    std::ostream& print_campaign(std::ostream& o){
        if(!campaign)
            o << "[]";
        else    
            o << *campaign.get();
        return o;
    }

    friend std::ostream& operator<<(std::ostream& o, Player& p){
        o << "[" << p.first_name << " " << p.last_name << ", {";
        bool first{true};
        for(const auto& [k, v] : p.heroes){
          if(v.get()){
            if(first){
                o << *v;
            		first = false;
            }
            else 
                o << ", " << *v;
          }
        }
        o << "}, ";
      	p.print_campaign(o);
        o << "]";
        return o;
    }
};


#endif
