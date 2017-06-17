#include "PokeFire.h"
#include "PokeWater.h"
#include "PokeElectric.h"
#include "PokeGrass.h"
#include "PokeFlying.h"

#include <iostream>

bool attributeTest();
bool levelUpTest();
bool effectTest();

bool checkAttributes(int level);
bool neq(int correctValue, int proposedValue);

void introduceYourself(Pokemon *pokemon);

int main(int argc, char** argv)
{
	int totalGrade = 0;

	if(attributeTest())
		totalGrade += 5;
	if(levelUpTest())
		totalGrade += 5;
	if(effectTest())
		totalGrade += 10;

	return totalGrade;
}

bool attributeTest()
{
	return checkAttributes(0);
}

bool levelUpTest()
{
	return checkAttributes(1) && checkAttributes(10) && checkAttributes(100);
}

bool effectTest()
{
	PokeFire fire(0, "Charmander");
	PokeWater water(1, "Psyduck");
	PokeElectric electric(2, "Pikachu");
	PokeGrass grass(3, "Bulbasaur");
	PokeFlying flying(4, "Zapdos?");

	PokeFire anotherFire(5, "Charizard");
	PokeWater anotherWater(6, "Golduck");
	PokeElectric anotherElectric(7, "Raichu");
	PokeGrass anotherGrass(8, "Venasaur");

	Arena arena = STADIUM;

	// You are free to print anything in attackTo, only the after-effects will be tested separately.
	fire.attackTo(&anotherFire, arena);
	fire.attackTo(&water, arena);
	fire.attackTo(&electric, arena);
	fire.attackTo(&grass, arena);
	fire.attackTo(&flying, arena);

	if(anotherFire.isBurning() || !water.isBurning() || !electric.isBurning() || !grass.isBurning() || flying.isBurning())
	{
		std::cout << "Problem in setBurning" << std::endl;

		return false;
	}

	water.attackTo(&fire, arena);
	water.attackTo(&anotherWater, arena);
	water.attackTo(&electric, arena);
	water.attackTo(&grass, arena);
	water.attackTo(&flying, arena);

	if(!fire.isDrowning() || anotherWater.isDrowning() || !electric.isDrowning() || !grass.isDrowning() || flying.isDrowning())
	{
		std::cout << "Problem in setDrowning" << std::endl;

		return false;
	}

	electric.attackTo(&fire, arena);
	electric.attackTo(&water, arena);
	electric.attackTo(&anotherElectric, arena);
	electric.attackTo(&grass, arena);
	electric.attackTo(&flying, arena);

	if(!fire.isElectrified() || !water.isElectrified() || anotherElectric.isElectrified() || !grass.isElectrified() || flying.isElectrified())
	{		
		std::cout << "Problem in setElectrified" << std::endl;

		return false;
	}

	grass.attackTo(&fire, arena);
	grass.attackTo(&water, arena);
	grass.attackTo(&electric, arena);
	grass.attackTo(&anotherGrass, arena);
	grass.attackTo(&flying, arena);

	if(!fire.isRooted() || !water.isRooted() || !electric.isRooted() || anotherGrass.isRooted() || flying.isRooted())
	{
		std::cout << "Problem in setElectrified" << std::endl;

		return false;
	}

	PokeFlying anotherFlying(9, "Articuno?");

	flying.attackTo(&anotherFlying, arena);

	if(anotherFlying.isBurning() || anotherFlying.isDrowning() || anotherFlying.isElectrified() || anotherFlying.isDrowning())
	{
		std::cout << "Problem in Articuno" << std::endl;

		return false;
	}

	return true;
}

void introduceYourself(Pokemon *pokemon)
{
	std::cout << pokemon->getPokemonID() << " " << pokemon->getName() << std::endl;
}

bool checkAttributes(int levelUp)
{
	PokeFire fire(0, "Charmander");
	PokeWater water(1, "Psyduck");
	PokeElectric electric(2, "Pikachu");
	PokeGrass grass(3, "Bulbasaur");
	PokeFlying flying(4, "Zapdos?");

	introduceYourself(&fire);
	introduceYourself(&water);
	introduceYourself(&electric);
	introduceYourself(&grass);
	introduceYourself(&flying);

	for(int i = 0; i < levelUp; i++)
	{
		fire.levelUp();
		water.levelUp();
		electric.levelUp();
		grass.levelUp();
		flying.levelUp();
	}

	if(neq(fire.getHP(), 600 + levelUp * 60)
	|| neq(water.getHP(), 700 + levelUp * 70)
	|| neq(electric.getHP(), 500 + levelUp * 50)
	|| neq(grass.getHP(), 800 + levelUp * 80)
	|| neq(flying.getHP(), 650 + levelUp * 65))
	{
		std::cout << "Problem in getHP" << std::endl;

		return false;
	}

	if(neq(fire.getATK(), 60 + levelUp * 6)
	|| neq(water.getATK(), 50 + levelUp * 5)
	|| neq(electric.getATK(), 70 + levelUp * 7)
	|| neq(grass.getATK(), 40 + levelUp * 4)
	|| neq(flying.getATK(), 55 + levelUp * 5))
	{
		std::cout << "Problem in getATK" << std::endl;

		return false;
	}

	if(neq(fire.getMAG_DEF(), 20 + levelUp * 2)
	|| neq(water.getMAG_DEF(), 10 + levelUp * 1)
	|| neq(electric.getMAG_DEF(), 30 + levelUp * 3)
	|| neq(grass.getMAG_DEF(), 0)
	|| neq(flying.getMAG_DEF(), 0))
	{
		std::cout << "Problem in getMAG_DEF" << std::endl;

		return false;
	}

	if(neq(fire.getPHY_DEF(), 10 + levelUp * 1)
	|| neq(water.getPHY_DEF(), 20 + levelUp * 2)
	|| neq(electric.getPHY_DEF(), 0)
	|| neq(grass.getPHY_DEF(), 30 + levelUp * 3)
	|| neq(flying.getPHY_DEF(), 15 + levelUp * 3))
	{
		std::cout << "Problem in getPHY_DEF" << std::endl;

		return false;
	}

	return true;
}

bool neq(int correctValue, int proposedValue)
{
	return correctValue != proposedValue;
}
