#include "PokeElectric.h"
#include <iostream>

using namespace Helpers;

PokeElectric::PokeElectric(int pokemonID, const std::string& name)
	: Pokemon(pokemonID, name){
		HP = 500;
		ATK = 70;
		MAG_DEF = 30;
		PHY_DEF = 0;

	}

PokeElectric::~PokeElectric(){
}

void PokeElectric::setElectrified(bool electrified){
	this->electrified = false;
}

void PokeElectric::attackTo(Pokemon* target, Arena currentArena){
	target->setElectrified(true);

	char arenaEffect = arenaPowers(currentArena);

	std::cout << "\t\t\t" << getName() << "(" << getHP() << ")" << " hit " << target->getName() <<
		"(" << target->getHP() << ") " << std::max(1, getATK() - target->getPHY_DEF()) << "(" << 
		arenaEffect << ")" << std::endl;
	
	target->setHP(target->getHP() - std::max(1, getATK() - target->getPHY_DEF()));
}

char PokeElectric::arenaPowers(Arena currentArena){
	if(currentArena == STADIUM){
		return '/';
	}
	else if(currentArena == MAGMA){
		return '-';
	}
	else if(currentArena == OCEAN){
		return '/';
	}
	else if(currentArena == ELECTRICITY){
		return '+';
	}
	else if(currentArena == FOREST){
		return '-';
	}
	else if(currentArena == SKY){
		return '/';
	}
}

void PokeElectric::arenaBuffer(Arena currentArena){
	if(currentArena == STADIUM){
		/* Do nothing */
	}
	else if(currentArena == MAGMA){
		HP = HP - HP_MODIFIER;
		ATK = ATK - ATK_MODIFIER;
	}
	else if(currentArena == OCEAN){
		/* Do nothing */
	}
	else if(currentArena == ELECTRICITY){
		HP = HP + HP_MODIFIER;
		ATK = ATK + ATK_MODIFIER;
	}
	else if(currentArena == FOREST){
		HP = HP - HP_MODIFIER;
		ATK = ATK - ATK_MODIFIER;
	}
	else if(currentArena == SKY){
		/* Do nothing */
	}
}

void PokeElectric::doubleEffect(){
	if((isBurning() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(BURNING) << 
			"!!" <<std::endl;
		
		setHP(getHP() - std::max(0, getEffectDamage(BURNING)-getMAG_DEF()));
	}
	if((isDrowning() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(DROWNING) << 
			"!!" <<std::endl;
	
		setHP(getHP() - std::max(0, getEffectDamage(DROWNING)-getMAG_DEF()));
	}
	if((isRooted() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(ROOTED) << 
			"!!!!" <<std::endl;
	
		setHP(getHP() - std::max(0, 2*getEffectDamage(ROOTED)-getMAG_DEF()));
	}
	else{
		/* Can not be electrified, do nothing */
	}
}

void PokeElectric::levelUp(){
	HP = HP+50;
	ATK = ATK+7;
	MAG_DEF = MAG_DEF+3;
	PHY_DEF = PHY_DEF+0;	

	level++;
}


void PokeElectric::resetPokemon(){
	HP = 500;
	ATK = 70;
	MAG_DEF = 30;
	PHY_DEF = 0;

	burning = false;
	drowning = false;
	electrified = false;
	rooted = false;

	for(int i = 0; i < level; i++){
		HP = HP+50;
		ATK = ATK+7;
		MAG_DEF = MAG_DEF+3;
		PHY_DEF = PHY_DEF+0;	
	}
}