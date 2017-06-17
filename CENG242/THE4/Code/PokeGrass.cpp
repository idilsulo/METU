#include "PokeGrass.h"
#include <iostream>

using namespace Helpers;

PokeGrass::PokeGrass(int pokemonID, const std::string& name)
	: Pokemon(pokemonID, name){
		HP = 800;
		ATK = 40;
		MAG_DEF = 0;
		PHY_DEF = 30;

		//rooted = true;
	}

PokeGrass::~PokeGrass(){
	//name.std::string::~string();
}

void PokeGrass::setRooted(bool rooted){
	this->rooted = false;
}

void PokeGrass::attackTo(Pokemon* target, Arena currentArena){
	target->setRooted(true);

	char arenaEffect = arenaPowers(currentArena);

	std::cout << "\t\t\t" << getName() << "(" << getHP() << ")" << " hit " << target->getName() <<
		"(" << target->getHP() << ") " << std::max(1, getATK() - target->getPHY_DEF()) << "(" << 
		arenaEffect << ")" << std::endl;
	
	target->setHP(target->getHP() - std::max(1, getATK() - target->getPHY_DEF()));
}

char PokeGrass::arenaPowers(Arena currentArena){
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
		return '/';
	}
	else if(currentArena == FOREST){
		return '+';
	}
	else if(currentArena == SKY){
		return '-';
	}
}

void PokeGrass::arenaBuffer(Arena currentArena){
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
		/* Do nothing */
	}
	else if(currentArena == FOREST){
		HP = HP + HP_MODIFIER;
		ATK = ATK + ATK_MODIFIER;
	}
	else if(currentArena == SKY){
		HP = HP - HP_MODIFIER;
		ATK = ATK - ATK_MODIFIER;
	}
}



void PokeGrass::doubleEffect(){
	if((isBurning() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(BURNING) << 
			"!!!!" <<std::endl;
		
		setHP(getHP() - std::max(0, 2*getEffectDamage(BURNING)-getMAG_DEF()));
	}
	if((isDrowning() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(DROWNING) << 
			"!!" <<std::endl;
	
		setHP(getHP() - std::max(0, getEffectDamage(DROWNING)-getMAG_DEF()));
	}
	if((isElectrified() == true) && (getHP() > 0)){
		std::cout << "\t\t\t" << getName() << "(" << getHP() << ") " <<  getEffectName(ELECTRIFIED) << 
			"!!" <<std::endl;
		
		setHP(getHP() - std::max(0, getEffectDamage(ELECTRIFIED)-getMAG_DEF()));
	}
	else{
		/* Can not be rooted, do nothing */
	}
}

void PokeGrass::levelUp(){
	HP = HP+80;
	ATK = ATK+4;
	MAG_DEF = MAG_DEF+0;
	PHY_DEF = PHY_DEF+3;

	level++;
}


void PokeGrass::resetPokemon(){
	HP = 800;
	ATK = 40;
	MAG_DEF = 0;
	PHY_DEF = 30;

	burning = false;
	drowning = false;
	electrified = false;
	rooted = false;

	for(int i = 0; i < level; i++){
		HP = HP+80;
		ATK = ATK+4;
		MAG_DEF = MAG_DEF+0;
		PHY_DEF = PHY_DEF+3;
	}
}