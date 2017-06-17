#ifndef POKEMON_H
#define POKEMON_H

#include <string>

using namespace std;

class Pokemon {
	private:
		// Add private members, methods and constructors here as you need
		/* Name of the pokemon */
		string name;
		/* Type of the pokemon */
		string type;
		/* Minimum number of battle experiences required to evolve */
		int evolver; /* Same as evolution level? */
		/* Experience points that pokemon has currently */
		int experience;
		/* Helper function to operator& */
		friend Pokemon& getPokemon(Pokemon& firstPokemon, Pokemon& secondPokemon, string givenType);
		/* Helper function to destructor */
		void clearPokemon();
	public:
		// Do NOT make any modifications below
		mutable int t_ref_cnt;	// stores how many trainers have this pokemon
		Pokemon(const string&, const string&, int);
		Pokemon(const Pokemon&);
		~Pokemon();
		const string& getName() const;
		bool operator>>(const Pokemon&);
		friend Pokemon operator&(Pokemon&, Pokemon&);
		Pokemon& operator=(const Pokemon&);
};

#endif
