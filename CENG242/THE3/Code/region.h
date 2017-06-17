#ifndef REGION_H
#define REGION_H

#include "pokemon.h"
#include <iostream>
#include <exception>

using namespace std;

class Region {
    private:
        // Add private members, methods and constructors here as you need

        int min_x, min_y, min_z;
        int max_x, max_y, max_z;

        int pokemonCount;

        Pokemon* pokemon;
        
        Region* left;
        Region* right;
        Region* parent;

        /* HELPER FUNCTIONS */
        /* Helper functions to placePokemon */
        void RegionDivider(int x, int y, int z, int xmin, int ymin, int zmin, 
            int xmax, int ymax, int zmax, const Pokemon& givenPokemon, Region* region);
        void pokemonCounter(int x, int y, int z, Region* region);
        /* Helper function to getPokemonCount */
        int numberofPokemons(const int minBorder[3], const int maxBorder[3], const Region* subregion) const;
        /* Helper function to Copy Constructor */
        Region* copyRegion(Region* region) const;
        /* Helper function to Destructor */
        void clearRegion(Region* region);
        /* Helper function to () operator */
        Region* isSubregion(const int minBorder[3], const int maxBorder[3], Region* subregion) const;

        
    public:
        // Do NOT make any modifications below
        Region(const int[3], const int[3]);
        Region(const Region&);
        ~Region();
        int getMinBorder(char) const;
        int getMaxBorder(char) const;
        void placePokemon(const Pokemon&, int, int, int);
        Pokemon& operator()(int, int, int);
        int getPokemonCount(const int[3], const int[3]) const;
        Region crop(const int[3], const int[3]) const;
        void patch(Region);
        Region& operator=(const Region&);
};

class pokemonException: public exception {
    virtual const char* what() const throw() {
            return "There does not exist any pokemon in the given coordinates!";
    }
};

#endif
