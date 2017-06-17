#ifndef POKEGRASS_H
#define POKEGRASS_H

#include "Pokemon.h"

class PokeGrass : public Pokemon
{
public:
	// Add your public methods/attributes here.
	PokeGrass(int pokemonID, const std::string& name);
	~PokeGrass();
	void attackTo(Pokemon* target, Arena currentArena);
	void levelUp();

	/* Helpers */
	char arenaPowers(Arena currentArena);
	void arenaBuffer(Arena currentArena);
	void doubleEffect();
	void setRooted(bool rooted);
	void resetPokemon();
	
protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif