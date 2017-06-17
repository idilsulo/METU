#ifndef POKEFLYING_H
#define POKEFLYING_H

#include "Pokemon.h"

class PokeFlying : public Pokemon
{
public:
	// Add your public methods/attributes here.
	PokeFlying(int pokemonID, const std::string& name);
	~PokeFlying();
	void attackTo(Pokemon* target, Arena currentArena);
	void levelUp();

	char arenaPowers(Arena currentArena);
	void arenaBuffer(Arena currentArena);
	void doubleEffect();

	void setBurning(bool burning);
	void setDrowning(bool drowning);
	void setElectrified(bool electrified);
	void setRooted(bool rooted);
	void resetPokemon();

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif