#include "PokeFlying.h"
#include <iostream>

using namespace Helpers;

PokeFlying::PokeFlying(int pokemonID, const std::string& name)
	: Pokemon(pokemonID, name){
		HP = 650;
		ATK = 55;
		MAG_DEF = 0;
		PHY_DEF = 15;
	}

PokeFlying::~PokeFlying(){
}

void PokeFlying::setBurning(bool burning){
	this->burning = false;
}

void PokeFlying::setDrowning(bool drowning){
	this->drowning = false;
}

void PokeFlying::setElectrified(bool electrified){
	this->electrified = false;
}

void PokeFlying::setRooted(bool rooted){
	this->rooted = false;
}

void PokeFlying::attackTo(Pokemon* target, Arena currentArena){
	/* Does not activate any effect */

	char arenaEffect = arenaPowers(currentArena);

	std::cout << "\t\t\t" << getName() << "(" << getHP() << ")" << " hit " << target->getName() <<
		"(" << target->getHP() << ") " << std::max(1, getATK() - target->getPHY_DEF()) << "(" << 
		arenaEffect << ")" << std::endl;
	
	target->setHP(target->getHP() - std::max(1, getATK() - target->getPHY_DEF()));
}

char PokeFlying::arenaPowers(Arena currentArena){
	if(currentArena == STADIUM){
		return '/';
	}
	else if(currentArena == MAGMA){
		return '/';
	}
	else if(currentArena == OCEAN){
		return '-';
	}
	else if(currentArena == ELECTRICITY){
		return '-';
	}
	else if(currentArena == FOREST){
		return '/';
	}
	else if(currentArena == SKY){
		return '+';
	}
}

void PokeFlying::arenaBuffer(Arena currentArena){
	if(currentArena == STADIUM){
		/* Do nothing */
	}
	else if(currentArena == MAGMA){
		/* Do nothing */
	}
	else if(currentArena == OCEAN){
		HP = HP - HP_MODIFIER;
		ATK = ATK - ATK_MODIFIER;
	}
	else if(currentArena == ELECTRICITY){
		HP = HP - HP_MODIFIER;
		ATK = ATK - ATK_MODIFIER;
	}
	else if(currentArena == FOREST){
		/* Do nothing */
	}
	else if(currentArena == SKY){
		HP = HP + HP_MODIFIER;
		ATK = ATK + ATK_MODIFIER;
	}
}

void PokeFlying::doubleEffect(){
	/* Immune to all */
	/* Can not be burning, drowning, electrified or rooted; do nothing */
}

void PokeFlying::levelUp(){
	HP = HP+65;
	ATK = ATK+5;
	MAG_DEF = MAG_DEF+0;
	PHY_DEF = PHY_DEF+3;

	level++;
}


void PokeFlying::resetPokemon(){
	HP = 650;
	ATK = 55;
	MAG_DEF = 0;
	PHY_DEF = 15;

	burning = false;
	drowning = false;
	electrified = false;
	rooted = false;

	for(int i = 0; i < level; i++){
		HP = HP+65;
		ATK = ATK+5;
		MAG_DEF = MAG_DEF+0;
		PHY_DEF = PHY_DEF+3;
	}
}