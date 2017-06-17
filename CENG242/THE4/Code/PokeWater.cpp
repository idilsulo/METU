#include "PokeWater.h"
#include <iostream>

using namespace Helpers;

PokeWater::PokeWater(int pokemonID, const std::string& name)
	: Pokemon(pokemonID, name){
		HP = 700;
		ATK = 50;
		MAG_DEF = 10;
		PHY_DEF = 20;

	}

PokeWater::~PokeWater(){
}

void PokeWater::setDrowning(bool drowning){
	this->drowning = false;
}

void PokeWater::attackTo(Pokemon* target, Arena currentArena){
	target->setDrowning(true);

	char arenaEffect = arenaPowers(currentArena);

	std::cout << "\t\t\t" << getName() << "(" << getHP() << ")" << " hit " << target->getName() <<
		"(" << target->getHP() << ") " << std::max(1, getATK() - target->getPHY_DEF()) << "(" << 
		arenaEffect << ")" << std::endl;
	
	target->setHP(target->getHP() - std::max(1, getATK() - target->getPHY_DEF()));
}

char PokeWater::arenaPowers(Arena currentArena){
	if(currentArena == STADIUM){
		return '/';
	}
	else if(currentArena == MAGMA){
		return '/';
	}
	else if(currentArena == OCEAN){
		return '+';
	}
	else if(currentArena == ELECTRICITY){
		return '-';
	}
	else if(currentArena == FOREST){
		return '-';
	}
	else if(currentArena == SKY){
		return '/';
	}
}

void PokeWater::arenaBuffer(Arena currentArena){
	if(currentArena == STADIUM){
		/* Do nothing */
	}
	else if(currentArena == MAGMA){
		/* Do nothing */
	}
	else if(currentArena == OCEAN){
		HP = HP + HP_MODIFIER;
		ATK = ATK + ATK_MODIFIER;
	}
	else if(currentArena == ELECTRICITY){
		HP = HP - HP_MODIFIER;
		ATK = ATK - ATK_MODIFIER;
	}
	else if(currentArena == FOREST){
		HP = HP - HP_MODIFIER;
		ATK = ATK - ATK_MODIFIER;
	}
	else if(currentArena == SKY){
		/* Do nothing */
	}
}

void PokeWater::doubleEffect(){
	if((isBurning() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(BURNING) << 
			"!!" <<std::endl;
		
		setHP(getHP() - std::max(0, getEffectDamage(BURNING)-getMAG_DEF()));
	}
	if((isElectrified() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(ELECTRIFIED) << 
			"!!!!" <<std::endl;
		
		setHP(getHP() - std::max(0, 2*getEffectDamage(ELECTRIFIED)-getMAG_DEF()));
	}
	if((isRooted() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(ROOTED) << 
			"!!" <<std::endl;
		
		setHP(getHP() - std::max(0, getEffectDamage(ROOTED)-getMAG_DEF()));
	}
	else{
		/* Can not be drowning, do nothing */
	}
}

void PokeWater::levelUp(){
	HP = HP+70;
	ATK = ATK+5;
	MAG_DEF = MAG_DEF+1;
	PHY_DEF = PHY_DEF+2;

	level++;
}

void PokeWater::resetPokemon(){
	HP = 700;
	ATK = 50;
	MAG_DEF = 10;
	PHY_DEF = 20;

	burning = false;
	drowning = false;
	electrified = false;
	rooted = false;

	for(int i = 0; i < level; i++){
		HP = HP+70;
		ATK = ATK+5;
		MAG_DEF = MAG_DEF+1;
		PHY_DEF = PHY_DEF+2;
	}
}