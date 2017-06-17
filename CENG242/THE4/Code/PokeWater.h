#ifndef POKEWATER_H
#define POKEWATER_H

#include "Pokemon.h"

class PokeWater : public Pokemon
{
public:
	// Add your public methods/attributes here.
	PokeWater(int pokemonID, const std::string& name);
	~PokeWater();
	void attackTo(Pokemon* target, Arena currentArena);
	void levelUp();

	/* Helpers */
	char arenaPowers(Arena currentArena);
	void arenaBuffer(Arena currentArena);
	void doubleEffect();
	void setDrowning(bool drowning);
	void resetPokemon();

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif