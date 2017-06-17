#include "trainer.h"

/* Default constructor */
Trainer::Trainer(const string& givenName, const Pokemon& givenPokemon, 
	const int minBorder[3], const int maxBorder[3]){
	name = givenName;
	pokemons.push_back(&givenPokemon);

	minimumView[0] = minBorder[0];
	minimumView[1] = minBorder[1];
	minimumView[2] = minBorder[2];

	maximumView[0] = maxBorder[0];
	maximumView[1] = maxBorder[1];
	maximumView[2] = maxBorder[2];

	index = 0;

	givenPokemon.t_ref_cnt++;
}

/* Copy Constructor */
Trainer::Trainer(const Trainer& givenTrainer){
	typename vector<const Pokemon*>::const_iterator itr = (givenTrainer.pokemons).end();

	for(itr; itr != (givenTrainer.pokemons).begin(); itr--){
		(*itr)->t_ref_cnt++;
		pokemons.push_back(*itr);
	}
	minimumView[0] = givenTrainer.minimumView[0];
	minimumView[1] = givenTrainer.minimumView[1];
	minimumView[2] = givenTrainer.minimumView[2];

	maximumView[0] = givenTrainer.maximumView[0];
	maximumView[1] = givenTrainer.maximumView[1];
	maximumView[2] = givenTrainer.maximumView[2];

	index = 0;


}

/* Destructor */
Trainer::~Trainer(){

	name.~string();

	for(int i=0; i<pokemons.size(); i++){
		(pokemons[i])->t_ref_cnt--;
		pokemons.pop_back();
	}
}

/* scanRegion function */
void Trainer::scanRegion(Region& givenRegion){
	int minimum[3] = {givenRegion.getMinBorder('x'), givenRegion.getMinBorder('y'), givenRegion.getMinBorder('z')};
	int maximum[3] = {givenRegion.getMaxBorder('x'), givenRegion.getMaxBorder('y'), givenRegion.getMaxBorder('z')};

	if(minimum[0] <= minimumView[0]){
		minimum[0] = minimumView[0];
	}
	if(minimum[1] <= minimumView[1]){
		minimum[1] = minimumView[1];
	}
	if(minimum[2] <= minimumView[2]){
		minimum[2] = minimumView[2];
	}
	if(maximum[0] >= maximumView[0]){
		maximum[0] = maximumView[0];
	}
	if(maximum[1] >= maximumView[1]){
		maximum[1] = maximumView[1];
	}
	if(maximum[2] >= maximumView[2]){
		maximum[2] = maximumView[2];
	}
	for(int i=minimum[0]; i<=maximum[0]; i++){
		for(int j=minimum[1]; j<=maximum[1]; j++){
			for(int k=minimum[2]; k<=maximum[2]; k++){
				try{
					catchPokemon(givenRegion(i,j,k));
				}
				catch(exception &e){

				}
			}
		}
	}
}





ostream& showPokemons(ostream& out, const Trainer& givenTrainer){

	for(int i=0; i<givenTrainer.pokemons.size(); i++){
		out << (givenTrainer.pokemons[i])->getName();
		if(i != (givenTrainer.pokemons.size())-1){
			out << ", ";
		}
		else{
			out << endl;
		}
	}
	return out;
}
