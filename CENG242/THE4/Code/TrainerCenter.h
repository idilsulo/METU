#ifndef TRAINER_CENTER_H
#define TRAINER_CENTER_H

#include "Trainer.h"
#include "Pokemon.h"

#include <vector>
#include <string>

class TrainerCenter
{
public:
	// Public Methods

	TrainerCenter(const std::string& inputFileName);
    ~TrainerCenter();
    
	std::vector<Trainer*>& getAllTrainers();

	Trainer* getTrainerWithID(int trainerID);

	// Own Methods
	Arena getArena(std::string arenaname);
	Pokemon* createPokemon(int pokemonid, std::string pokemonname, std::string pokemontype);

private:
	// Own Attributes
	std::vector<Trainer *> allTrainers;
};

#endif
