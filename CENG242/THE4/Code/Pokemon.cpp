#include "Pokemon.h"


/* Default constructor */
Pokemon::Pokemon(int pokemonID, const std::string& name){
	this->pokemonID = pokemonID;
	this->name = name;
	HP = 0;
	ATK = 0;
	MAG_DEF = 0;
	PHY_DEF = 0;

	burning = false;
	drowning = false;
	electrified = false;
	rooted = false;

	level = 0;
}

Pokemon::~Pokemon(){

}

/* Getters */
int Pokemon::getPokemonID() const{
	return pokemonID;
}

const std::string& Pokemon::getName() const{
	return name;
}

int Pokemon::getHP() const{
	return HP;
}

int Pokemon::getATK() const{
	return ATK;
}

int Pokemon::getMAG_DEF() const{
	return MAG_DEF;
}

int Pokemon::getPHY_DEF() const{
	return PHY_DEF;
}

bool Pokemon::isBurning() const{
	return burning;
}

bool Pokemon::isDrowning() const{
	return drowning;
}

bool Pokemon::isElectrified() const{
	return electrified;
}

bool Pokemon::isRooted() const{
	return rooted;
}

/* Setters */

/* setBurning */
void Pokemon::setBurning(bool burning){
	this->burning = burning;
}

/* setDrowning */
void Pokemon::setDrowning(bool drowning){
	this->drowning = drowning;
}

/* setElectrified */
void Pokemon::setElectrified(bool electrified){
	this->electrified = electrified;
}

/* setRooted */
void Pokemon::setRooted(bool rooted){
	this->rooted = rooted;
}

/* Own methods */
void Pokemon::setHP(int givenHP){
	HP = givenHP;
}


void Pokemon::refreshPokemon(Pokemon* pokemon){
	pokemon->burning = false;
	pokemon->drowning = false;
	pokemon->electrified = false;
	pokemon->rooted = false;	
}