#include "Tournament.h"
#include <iostream>

using namespace Helpers;

Tournament::Tournament(const std::string& tournamentName){
	this->tournamentName = tournamentName;
}

Tournament::~Tournament(){
	
	/*for(int i=0; i < competitors.size(); i++){
			//competitors[i]->Trainer::~Trainer();
			delete competitors[i];
		}
	
	
	for(int i=0; i < winners.size(); i++){
			//winners[i]->Trainer::~Trainer();
		delete winners[i];
		}
	*/
	//tournamentName.std::string::~string();
}

void Tournament::registerTrainers(const std::vector<Trainer*>& trainers){
	competitors = trainers;
}
    
// Commence the tournament, and return the champion.
Trainer* Tournament::commence(){
	if(competitors.size() > 1){
	
	int winner = 0;

	int i = 0;
	int j = competitors.size()-1;

		while(competitors.size() > 1){
			Trainer* trainer1 = competitors.front();
			Trainer* trainer2 = competitors.back();

			std::cout << "Started Round: " << i << " vs " << j << std::endl;
			threeMatchWinner(trainer1, trainer2, winner);

			std::cout << "Round Winner: " << winners[i]->getName() << "!" << std::endl;
			
			i++;
			j--;
		}

		while(!winners.empty()){

			competitors.push_back(winners.front());
			winners.erase(winners.begin());
		}
	commence();
	}
	else{
		//std::cout << competitors.front()-> << std::endl;
		Trainer* Winner = competitors.front();
		return Winner;
	}
}


void Tournament::threeMatchWinner(Trainer* trainer1, Trainer* trainer2, int winner){

	std::cout << "\t" << trainer1->getName() << " vs " << trainer2->getName() << ": " << getArenaName(trainer1->getFavoriteArena()) << std::endl;
	winner = duelBetween(trainer1, trainer2, trainer1->getFavoriteArena());
	
	std::cout << "\t" << trainer2->getName() << " vs " << trainer1->getName() << ": " << getArenaName(trainer2->getFavoriteArena()) << std::endl;
	winner -= duelBetween(trainer2, trainer1, trainer2->getFavoriteArena());
	
	std::cout << "\t" << trainer1->getName() << " vs " << trainer2->getName() << ": " << getArenaName(STADIUM) << std::endl;
	winner += duelBetween(trainer1, trainer2, STADIUM);


	if(winner >= 1){

		winners.push_back(trainer1);

		competitors.erase(competitors.begin());

		if(competitors.size() > 1)
			competitors.pop_back();
		else
			competitors.clear();
	}
	else if(winner <= -1){

		winners.push_back(trainer2);

		competitors.erase(competitors.begin());

		if(competitors.size() > 1)
			competitors.pop_back();
		else
			competitors.clear();
	}
}

// Return 1 if Trainer1 wins.
// Return -1 if Trainer2 wins.
// It may be called from main.cpp, aside from a Tournament.
int Tournament::duelBetween(Trainer* trainer1, Trainer* trainer2, Arena currentArena){

	Pokemon* pokemon1 = NULL;
	Pokemon* pokemon2 = NULL;

	int winner = 0;
	int firsttrainer_n = 0;
	int secondtrainer_n = 0;

	int pokemoncount = trainer1->pokemonCount();
	//std::cout << pokemoncount << std::endl;

	while((pokemoncount > firsttrainer_n) || (pokemoncount > secondtrainer_n)){

		if((pokemon1 == NULL) && (pokemon2 == NULL)){

			pokemon1 = trainer1->summonPokemon(firsttrainer_n);			
			pokemon2 = trainer2->summonPokemon(secondtrainer_n);
			
			pokemon1->arenaBuffer(currentArena);
			pokemon2->arenaBuffer(currentArena);
			
			winner = duelBetween(pokemon1, pokemon2, currentArena);
		}
		
		if(pokemon2->getHP() <= 0){
			pokemon1->levelUp(); 
			pokemon2->refreshPokemon(pokemon2);

			secondtrainer_n++;
			
			pokemon2 = trainer2->summonPokemon(secondtrainer_n);
			
			if(pokemon2 != NULL){
			
				pokemon2->arenaBuffer(currentArena);

				winner = duelBetween(pokemon2, pokemon1, currentArena);
			}
			else{
				break;
			}
		}
		else if(pokemon1->getHP() <= 0){
			pokemon2->levelUp();
			pokemon1->refreshPokemon(pokemon1);
			
			firsttrainer_n++;
			
			pokemon1 = trainer1->summonPokemon(firsttrainer_n);

			if(pokemon1 != NULL){
				pokemon1->arenaBuffer(currentArena);

				winner = duelBetween(pokemon1, pokemon2, currentArena);
			}
			else{
				break;
			}
		}
	}

	trainer1->resetAllPokemons();
	trainer2->resetAllPokemons();

	if(pokemoncount == firsttrainer_n){
		std::cout << "\t" << "WinnerT:" << trainer2->getName() << std::endl << std::endl;

		return -1;
	}
	else if(pokemoncount == secondtrainer_n){
		std::cout << "\t" << "WinnerT:" << trainer1->getName() << std::endl << std::endl;

		return 1;
	}
}


const std::string& Tournament::getTournamentName() const{
	return tournamentName;
}

// Return 1 if Pokemon1 wins.
// Return -1 if Pokemon2 wins.
// It won't (can't) be called from main.cpp, this method is for your own convenience.
int Tournament::duelBetween(Pokemon *pokemon1, Pokemon *pokemon2, Arena currentArena){
	if((pokemon1->getHP() > 0) && (pokemon2->getHP() > 0)){
		while((pokemon1->getHP() > 0) && (pokemon2->getHP() > 0)){

			if(pokemon1->getHP() > 0){
				pokemon1->doubleEffect();
			}
			else{
				/* Pokemon1 is dead, Pokemon2 wins */
				std::cout << "\t\t" << "WinnerP:" << pokemon2->getName() << std::endl; 
				
				return -1;
			}

			if(pokemon1->getHP() > 0){
				pokemon1->attackTo(pokemon2, currentArena);
			}
			else{
				/* Pokemon1 is dead, Pokemon2 wins */
				std::cout << "\t\t" << "WinnerP:" << pokemon2->getName() << std::endl; 

				return -1;
			}

			if(pokemon2->getHP() > 0){
				pokemon2->doubleEffect();
			}
			else{
				/* Pokemon2 is dead, Pokemon1 wins */
				std::cout << "\t\t" << "WinnerP:" << pokemon1->getName() << std::endl;

				return 1;
			}

			if(pokemon2->getHP() > 0){
				pokemon2->attackTo(pokemon1, currentArena);
			}
			else{
				/* Pokemon2 is dead, Pokemon1 wins */
				std::cout << "\t\t" << "WinnerP:" << pokemon1->getName() << std::endl;

				return 1;
			}
		}
	}
	if(pokemon1->getHP() <= 0){
		std::cout << "\t\t" << "WinnerP:" << pokemon2->getName() << std::endl;
		return -1;
	}
	else if(pokemon2->getHP() <= 0){
		std::cout << "\t\t" << "WinnerP:" << pokemon1->getName() << std::endl; 
		return 1;
	}
}
