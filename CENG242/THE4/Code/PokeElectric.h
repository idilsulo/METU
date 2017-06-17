#ifndef POKEELECTRIC_H
#define POKEELECTRIC_H

#include "Pokemon.h"

class PokeElectric : public Pokemon
{
public:
	// Add your public methods/attributes here.
	PokeElectric(int pokemonID, const std::string& name);
	~PokeElectric();
	void attackTo(Pokemon* target, Arena currentArena);
	void levelUp();

	/* Helpers */
	char arenaPowers(Arena currentArena);
	void arenaBuffer(Arena currentArena);
	void doubleEffect();
	void setElectrified(bool electrified);
	void resetPokemon();

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif