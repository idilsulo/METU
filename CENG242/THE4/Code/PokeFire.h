#ifndef POKEFIRE_H
#define POKEFIRE_H

#include "Pokemon.h"

class PokeFire : public Pokemon
{
public:
	// Add your public methods/attributes here.
	PokeFire(int pokemonID, const std::string& name);
	~PokeFire();
	void attackTo(Pokemon* target, Arena currentArena);
	void levelUp();

	/* Helpers */
	char arenaPowers(Arena currentArena);
	void arenaBuffer(Arena currentArena);
	void doubleEffect();
	void setBurning(bool burning);
	void resetPokemon();

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif