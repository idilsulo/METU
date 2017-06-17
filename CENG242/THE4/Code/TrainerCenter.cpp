#include "TrainerCenter.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>  

#include "PokeFire.h"
#include "PokeWater.h"
#include "PokeElectric.h"
#include "PokeGrass.h"
#include "PokeFlying.h"

TrainerCenter::TrainerCenter(const std::string& inputFileName){
	std::ifstream inputFileStream;

	inputFileStream.open(inputFileName.std::string::c_str(), std::ifstream::in);

	std::string line;
	std::getline(inputFileStream, line);

	int trainercount = atoi((line.std::string::substr(14)).std::string::c_str());
	std::getline(inputFileStream, line);
	int pokemoncount = atoi((line.std::string::substr(14)).std::string::c_str());
	
	std::getline(inputFileStream, line);
			

	for(int i = 0; i < trainercount; i++){
		std::vector<Pokemon *> pokemonVector;
		
		std::getline(inputFileStream, line);

		std::size_t firstpos = line.std::string::find("--");
		std::size_t secondpos = line.std::string::rfind("--");

		int trainerid = atoi((line.std::string::substr(0, firstpos)).std::string::c_str());
		std::string trainername = line.std::string::substr(firstpos+2, secondpos-firstpos-2);
				
		std::string arenaname = line.std::string::substr(secondpos+2);
		Arena arena = getArena(arenaname);

		for(int j = 0; j < pokemoncount; j++){
			std::getline(inputFileStream, line);

			firstpos = line.std::string::find("::");
			secondpos = line.std::string::rfind("::");

			int pokemonid = atoi((line.std::string::substr(0, firstpos)).std::string::c_str());
			std::string pokemonname = line.std::string::substr(firstpos+2, secondpos-firstpos-2);
						
			std::string pokemontype = line.std::string::substr(secondpos+2);
			
			Pokemon* newPokemon = createPokemon(pokemonid, pokemonname, pokemontype);
			pokemonVector.push_back(newPokemon);

		}


		Trainer* newTrainer = new Trainer(trainerid, trainername, arena, pokemonVector);
		allTrainers.push_back(newTrainer);
		
		std::getline(inputFileStream, line);
	}

	/* Close the file */
	inputFileStream.close();

}

Arena TrainerCenter::getArena(std::string arenaname){
	if(arenaname == "Stadium")
		return STADIUM;
	else if(arenaname == "Magma")
		return MAGMA;
	else if(arenaname == "Ocean")
		return OCEAN;
	else if(arenaname == "ElectriCity")
		return ELECTRICITY;
	else if(arenaname == "Forest")
		return FOREST;
	else if(arenaname == "Sky")
		return SKY;
}

Pokemon* TrainerCenter::createPokemon(int pokemonid, std::string pokemonname, std::string pokemontype){
	if(pokemontype == "FIRE"){
		Pokemon* pokemon = new PokeFire(pokemonid, pokemonname);
		return pokemon;
	}
	else if(pokemontype == "WATER"){
		Pokemon* pokemon = new PokeWater(pokemonid, pokemonname);
		return pokemon;
	}
	else if(pokemontype == "ELECTRIC"){
		Pokemon* pokemon = new PokeElectric(pokemonid, pokemonname);
		return pokemon;
	}
	else if(pokemontype == "GRASS"){
		Pokemon* pokemon = new PokeGrass(pokemonid, pokemonname);
		return pokemon;
	}
	else{
		Pokemon* pokemon = new PokeFlying(pokemonid, pokemonname);
		return pokemon;
	}
}



TrainerCenter::~TrainerCenter(){
	for(int i=0; i < allTrainers.size(); i++){
					
		delete allTrainers[i];
	}
}

std::vector<Trainer*>& TrainerCenter::getAllTrainers(){
	return allTrainers;
}

Trainer* TrainerCenter::getTrainerWithID(int trainerID){
	int i = 0;
	for(i; i < allTrainers.size(); i++){
		if(allTrainers[i]->getTrainerID() == trainerID){
			break;
		}
	}
	return allTrainers[i];
}