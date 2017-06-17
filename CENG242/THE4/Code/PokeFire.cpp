#include "PokeFire.h"
#include <iostream>

using namespace Helpers;

PokeFire::PokeFire(int pokemonID, const std::string& name)
	: Pokemon(pokemonID, name){
		HP = 600;
		ATK = 60;
		MAG_DEF = 20;
		PHY_DEF = 10;

	}

PokeFire::~PokeFire(){
	//name.std::string::~string();
}

void PokeFire::setBurning(bool burning){
	this->burning = false;
}

void PokeFire::attackTo(Pokemon* target, Arena currentArena){
	target->setBurning(true);

	char arenaEffect = arenaPowers(currentArena);

	std::cout << "\t\t\t" << getName() << "(" << getHP() << ")" << " hit " << target->getName() <<
		"(" << target->getHP() << ") " << std::max(1, getATK() - target->getPHY_DEF()) << "(" << 
		arenaEffect << ")" << std::endl;

	target->setHP(target->getHP() - std::max(1, getATK() - target->getPHY_DEF()));
}


char PokeFire::arenaPowers(Arena currentArena){
	if(currentArena == STADIUM){
		return '/';
	}
	else if(currentArena == MAGMA){
		return '+';
	}
	else if(currentArena == OCEAN){
		return '-';
	}
	else if(currentArena == ELECTRICITY){
		return '/';
	}
	else if(currentArena == FOREST){
		return '/';
	}
	else if(currentArena == SKY){
		return '-';
	}
}

void PokeFire::arenaBuffer(Arena currentArena){
	if(currentArena == STADIUM){
		/* Do nothing */
	}
	else if(currentArena == MAGMA){
		HP = HP + HP_MODIFIER;
		ATK = ATK + ATK_MODIFIER;
	}
	else if(currentArena == OCEAN){
		HP = HP - HP_MODIFIER;
		ATK = ATK - ATK_MODIFIER;
	}
	else if(currentArena == ELECTRICITY){
		/* Do nothing */
	}
	else if(currentArena == FOREST){
		/* Do nothing */
	}
	else if(currentArena == SKY){
		HP = HP - HP_MODIFIER;
		ATK = ATK - ATK_MODIFIER;
	}
}

void PokeFire::doubleEffect(){
	if((isDrowning() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(DROWNING) << 
			"!!!!" <<std::endl;
	
		setHP(getHP() - std::max(0, 2*getEffectDamage(DROWNING)-getMAG_DEF()));
	}
	if((isElectrified() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(ELECTRIFIED) << 
			"!!" <<std::endl;
		
		setHP(getHP() - std::max(0, getEffectDamage(ELECTRIFIED)-getMAG_DEF()));
	}
	if((isRooted() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(ROOTED) << 
			"!!" <<std::endl;

		setHP(getHP() - std::max(0, getEffectDamage(ROOTED)-getMAG_DEF()));
	}
	else{
		/* Can not be burning, do nothing */
	}
}

void PokeFire::levelUp(){
	HP = HP+60;
	ATK = ATK+6;
	MAG_DEF = MAG_DEF+2;
	PHY_DEF = PHY_DEF+1;

	level++;
}

void PokeFire::resetPokemon(){
	HP = 600;
	ATK = 60;
	MAG_DEF = 20;
	PHY_DEF = 10;

	burning = false;
	drowning = false;
	electrified = false;
	rooted = false;

	for(int i = 0; i < level; i++){
		HP = HP+60;
		ATK = ATK+6;
		MAG_DEF = MAG_DEF+2;
		PHY_DEF = PHY_DEF+1;
	}
}