#include "Trainer.h"

Trainer::Trainer(int trainerID, const std::string& name, Arena favoriteArena, std::vector<Pokemon *>& pokemons){
	this->trainerID = trainerID;
	this->name = name;
	this->favoriteArena = favoriteArena;
	this->pokemons = pokemons;
}

Trainer::~Trainer(){
	for(int i=0; i<pokemons.size(); i++){

		delete pokemons[i];
	}

}


int Trainer::getTrainerID() const{
	return trainerID;
}

const std::string& Trainer::getName() const{
	return name;
}

Arena Trainer::getFavoriteArena() const{
	return favoriteArena;
}

// Own Methods
int Trainer::pokemonCount(){
	return pokemons.size();
}

Pokemon* Trainer::summonPokemon(int n){
	if(n < pokemons.size())
		return pokemons[n];
	else
		return NULL;
}

void Trainer::resetAllPokemons(){
	for(int i=0; i< pokemons.size(); i++){
		pokemons[i]->resetPokemon();
	}
}
