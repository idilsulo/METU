#include "pokemon.h"

using namespace std;

/* Default Constructor */
Pokemon::Pokemon(const string& givenName, const string& givenType, int givenEvolver){
	name = givenName;
	type = givenType;
	evolver = givenEvolver;
	experience = 0;
	t_ref_cnt = 0;
}

/* Copy Constructor */
Pokemon::Pokemon(const Pokemon& givenPokemon){
	name = givenPokemon.name;
	type = givenPokemon.type;
	evolver = givenPokemon.evolver;
	experience = givenPokemon.experience;
	t_ref_cnt = givenPokemon.t_ref_cnt;
}

/* Destructor */
Pokemon::~Pokemon(){
	clearPokemon();
}

/* HELPER */
void Pokemon::clearPokemon(){	
	
	this->name.~string();
	this->type.~string();
}

/* getName */
const string& Pokemon::getName() const{
	return name;
}

/* evolve operator: >>*/
bool Pokemon::operator>>(const Pokemon& nextPokemon){
	if(experience >= evolver){
		name = nextPokemon.name;
		type = nextPokemon.type;
		evolver = nextPokemon.evolver;
		return 1;
	}
	else if(evolver == -1){
		return 0;
	}
	else{
		return 0;
	}
}

/* HELPER */
/* Returns the Pokemon with the given type */
Pokemon& getPokemon(Pokemon& firstPokemon, Pokemon& secondPokemon, string givenType){
	if(firstPokemon.type == givenType)
		return firstPokemon;
	else
		return secondPokemon;
} 

/*operator& */
Pokemon operator&(Pokemon& firstPokemon, Pokemon& secondPokemon){
	int local;
	firstPokemon.experience++;
	secondPokemon.experience++;

	if((firstPokemon.type == "fire") || (secondPokemon.type == "fire")){
		if((firstPokemon.type == "water") || (secondPokemon.type == "water"))
			return getPokemon(firstPokemon, secondPokemon, "water");
		else if((firstPokemon.type == "grass") || (secondPokemon.type == "grass"))
			return getPokemon(firstPokemon, secondPokemon, "fire");
		else if((firstPokemon.type == "electric") || (secondPokemon.type == "electric"))
			return getPokemon(firstPokemon, secondPokemon, "fire");
		else
			return getPokemon(firstPokemon, secondPokemon, "flying");
	}
	else if((firstPokemon.type == "water") || (secondPokemon.type == "water")){
		if((firstPokemon.type == "grass") || (secondPokemon.type == "grass"))
			return getPokemon(firstPokemon, secondPokemon, "grass");
		else if((firstPokemon.type == "electric") || (secondPokemon.type == "electric"))
			return getPokemon(firstPokemon, secondPokemon, "electric");
		else
			return getPokemon(firstPokemon, secondPokemon, "water");
	}
	else if((firstPokemon.type == "grass") || (secondPokemon.type == "grass")){
		if((firstPokemon.type == "electric") || (secondPokemon.type == "electric"))
			return getPokemon(firstPokemon, secondPokemon, "grass");
		else
			return getPokemon(firstPokemon, secondPokemon, "flying");		
	}
	else{
		return getPokemon(firstPokemon, secondPokemon, "electric");					
	}
}



/* operator= */
Pokemon& Pokemon::operator=(const Pokemon& givenPokemon){
	if(this != &givenPokemon){ /* Prevents self-assignment */
		clearPokemon();
		// Or should we call clearPokemon() ?
 		name = givenPokemon.name;
		type = givenPokemon.type;
		evolver = givenPokemon.evolver;
		experience = givenPokemon.experience;
		t_ref_cnt = givenPokemon.t_ref_cnt;
	}
	return *this;
}