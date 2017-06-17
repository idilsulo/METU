#include "region.h"

/* Default constructor */
Region::Region(const int givenMin[3], const int givenMax[3]){
	
		min_x = givenMin[0];
		min_y = givenMin[1];
		min_z = givenMin[2];

		max_x = givenMax[0];
		max_y = givenMax[1];
		max_z = givenMax[2];

		pokemonCount = 0;
		left = NULL;
		right = NULL;
		parent = NULL;
		pokemon = NULL;
}

/* Copy constructor */
Region::Region(const Region& newRegion){
	this->left = copyRegion(newRegion.left);
	this->right = copyRegion(newRegion.right);
	this->parent = newRegion.parent;
	this->pokemon = newRegion.pokemon;

	this->min_x = newRegion.min_x;
	this->min_y = newRegion.min_y;
	this->min_z = newRegion.min_z;

	this->max_x = newRegion.max_x;
	this->max_y = newRegion.max_y;
	this->max_z = newRegion.max_z;

	this->pokemonCount = newRegion.pokemonCount;
}


Region* Region::copyRegion(Region* region) const{
	if(region == NULL){
		return NULL;
	}

	int minimum[3] = {region->min_x, region->min_y, region->min_z};
	int maximum[3] = {region->max_x, region->max_y, region->max_z};

	Region* newRegion;
	newRegion = new Region(minimum, maximum);
	newRegion->pokemon = region->pokemon;
	newRegion->left = copyRegion(region->left);
	newRegion->right = copyRegion(region->right);
	newRegion->parent = region->parent;
	newRegion->pokemonCount = region->pokemonCount;
}


/* Destructor */
Region::~Region(){

	clearRegion(left);
	clearRegion(right);
	this->pokemon = NULL;
	this->parent = NULL;	
}


void Region::clearRegion(Region* region){

	if(region != NULL){
		clearRegion(region->left);
		clearRegion(region->right);
		if((region->left == NULL) && (region->right == NULL)){
			(region->pokemon)->~Pokemon();
			region->parent = NULL;
			delete region;
		}
	}

	region = NULL;
	//delete region;
}

int Region::getMinBorder(char coordinate) const{
	if(coordinate == 'x')
		return min_x;
	else if(coordinate == 'y')
		return min_y;
	else
		return min_z;
}
int Region::getMaxBorder(char coordinate) const{
	if(coordinate == 'x')
		return max_x;
	else if(coordinate == 'y')
		return max_y;
	else
		return max_z;

}

void Region::placePokemon(const Pokemon& givenPokemon, int x, int y, int z){
	RegionDivider(x, y, z, min_x, min_y, min_z, max_x, max_y, max_z, givenPokemon, this);
	pokemonCounter(x, y, z, this);
}


void Region::RegionDivider(int x, int y, int z, int xmin, int ymin, int zmin, 
	int xmax, int ymax, int zmax, const Pokemon& givenPokemon, Region* region){
	
	int* minimum = new int[3];
	int* maximum = new int[3];
	
	minimum[0] = xmin;
	minimum[1] = ymin;
	minimum[2] = zmin;

	maximum[0] = xmax;
	maximum[1] = ymax;
	maximum[2] = zmax; 


	if((xmax == x) && (xmin == x) && (ymax == y) && (ymin == y) && (zmax == z) && (zmin == z)){
		
		region->pokemon = new Pokemon(givenPokemon);
	}
 	else{
	 	if(xmin != xmax){
	 		if( (xmin <= x) && (x <= ((xmin+xmax)/2)) ){

	 			maximum[0] = ((xmin+xmax)/2);
				xmax = ((xmin+xmax)/2);

				if(region->left == NULL){

	 				region->left = new Region(minimum, maximum);
	 				region->left->parent = region;
	 			}

	 			region = region->left;

	 		}
	 		else{

	 			minimum[0] = ((xmin+xmax)/2)+1;
	 			xmin = ((xmin+xmax)/2)+1;

	 			if(region->right == NULL){

	 				region->right = new Region(minimum, maximum);
	 				region->right->parent = region;
	 			}
	 			
	 			region = region->right;

	 		}
	 	}
	 	if(ymin != ymax){
	 		if( (ymin <= y) && (y <= ((ymin+ymax)/2)) ){


	 			maximum[1] = ((ymin+ymax)/2);
	 			ymax = ((ymin+ymax)/2);

	 			if(region->left == NULL){
					
					region->left= new Region(minimum, maximum);
					region->left->parent = region;
				}

				region = region->left;

			}
			else{

				minimum[1] = ((ymin+ymax)/2)+1;
				ymin = ((ymin+ymax)/2)+1;

				if(region->right == NULL){
					
					region->right = new Region(minimum, maximum);
					region->right->parent = region;
				}

				region = region->right;

			}
	 	}
	 	if(zmin != zmax){
	 		if( (zmin <= z) && (z <= ((zmin+zmax)/2)) ){

	 			maximum[2] = ((zmin+zmax)/2);
	 			zmax = ((zmin+zmax)/2);

	 			if(region->left == NULL){
	 			
	 				region->left = new Region(minimum, maximum);
	 				region->left->parent = region;
	 			}

	 			region = region->left;

	 		}
	 		else{
	 			
	 			minimum[2] = ((zmin+zmax)/2)+1;
	 			zmin = ((zmin+zmax)/2)+1;

	 			if(region->right == NULL){
	 			
	 				region->right = new Region(minimum, maximum);
	 				region->right->parent = region;
	 			}

	 			region = region->right;

	 		}
	 	}
 		RegionDivider(x, y, z, xmin, ymin, zmin, xmax, ymax, zmax, givenPokemon, region);
	}
	
	delete[] minimum;
	delete[] maximum;
 }

void Region::pokemonCounter(int x, int y, int z, Region* region){
	if((region->left == NULL) && (region->right == NULL)){
		if((region->pokemon != NULL) && (x == region->min_x) && (x == region->max_x) && (y == region->min_y) && (y == region->max_y) && (z == region->min_z) && (z == region->max_z)/*(region->pokemon == &givenPokemon)*/){
			while(region != NULL){
				(region->pokemonCount)++;
				region = region->parent;
			}
		}
	}
	else{
		if(region->left != NULL)
			pokemonCounter(x, y, z, region->left);
		if(region->right != NULL)
			pokemonCounter(x, y, z, region->right);
	}

}


Pokemon& Region::operator()(int x, int y, int z){
	int minBorder[3] = {x, y, z};
	int maxBorder[3] = {x, y, z};

	Region* subregion = isSubregion(minBorder, maxBorder, this);
	Pokemon* p = NULL;

	if(subregion != NULL){
		p = subregion->pokemon;
	}

	while((subregion != NULL)){
		--(subregion->pokemonCount);
		subregion = subregion->parent;
	} 

	subregion = isSubregion(minBorder, maxBorder, this);

	while((subregion != NULL) && (subregion->parent != NULL) && (subregion->pokemonCount == 0)){
		Region* tmp = subregion;

		subregion = subregion->parent;

		if(subregion->left == tmp)
			subregion->left = NULL;
		else if(subregion->right == tmp)
			subregion->right = NULL;
			
		delete tmp;
	}

	if (p != NULL){
		return *p;
	}
	else{
		pokemonException pokemonEx;
		throw pokemonEx;
	}
}

Region* Region::isSubregion(const int minBorder[3], const int maxBorder[3], Region* subregion) const{
	if(subregion == NULL){
		return NULL;
	}
	else if((minBorder[0] == subregion->min_x) && (minBorder[1] == subregion->min_y) && (minBorder[2] == subregion->min_z) && 
		(maxBorder[0] == subregion->max_x) && (maxBorder[1] == subregion->max_y) && (maxBorder[2] == subregion->max_z) 
		/*&& (subregion->pokemon != NULL)*/){
		return subregion;
	}
	else{
		Region* tmp = isSubregion(minBorder, maxBorder, subregion->left); 
		if(tmp != NULL)
			return tmp;
		else
			return isSubregion(minBorder, maxBorder, subregion->right);
	}
}



int Region::getPokemonCount(const int minBorder[3], const int maxBorder[3]) const{
	if((minBorder[0] == this->min_x) && (minBorder[1] == this->min_y) && (minBorder[2] == this->min_z) && 
		(maxBorder[0] == this->max_x) && (maxBorder[1] == this->max_y) && (maxBorder[2] == this->max_z))
		return pokemonCount;
	else
		return numberofPokemons(minBorder, maxBorder, this->left) + numberofPokemons(minBorder, maxBorder, this->right);
}

 int Region::numberofPokemons(const int minBorder[3], const int maxBorder[3], const Region* subregion) const{
 	if(subregion == NULL){
 	 	return 0;
 	}
	else if((minBorder[0] == subregion->min_x) && (minBorder[1] == subregion->min_y) && (minBorder[2] == subregion->min_z) && 
		(maxBorder[0] == subregion->max_x) && (maxBorder[1] == subregion->max_y) && (maxBorder[2] == subregion->max_z) /*&& (subregion->pokemon != NULL)*/){
		return subregion->pokemonCount;
	}
	else{
		return numberofPokemons(minBorder, maxBorder, subregion->left) + numberofPokemons(minBorder, maxBorder, subregion->right);
	}
}


Region Region::crop(const int minBorder[3], const int maxBorder[3]) const{
	Region* region = isSubregion(minBorder, maxBorder, this->left);
	if(region == NULL)
		region = isSubregion(minBorder, maxBorder, this->right);

	Region* newRegion = new Region(minBorder, maxBorder);
	newRegion->left = copyRegion(region->left);
	newRegion->right = copyRegion(region->right);
	newRegion->parent = region->parent;
	newRegion->pokemon = region->pokemon;

	newRegion->min_x = region->min_x;
	newRegion->min_y = region->min_y;
	newRegion->min_z = region->min_z;

	newRegion->max_x = region->max_x;
	newRegion->max_y = region->max_y;
	newRegion->max_z = region->max_z;

	newRegion->pokemonCount = region->pokemonCount;
	return *newRegion;
}



void Region::patch(Region givenRegion){
	Region* region = &givenRegion;
	Region* tmp;
	int minBorder[3] = {givenRegion.min_x, givenRegion.min_y, givenRegion.min_z};
	int maxBorder[3] = {givenRegion.max_x, givenRegion.max_y, givenRegion.max_z};
	region = isSubregion(minBorder, maxBorder, region);
	tmp = region;
	tmp = tmp->parent;

	if(tmp->left == region){
		clearRegion(region);
		tmp->left = &givenRegion;
	}
	else if(tmp->right == region){
		clearRegion(region);
		tmp->right = &givenRegion;
	}
	else{
		tmp = &givenRegion;
	}
	//clearRegion(region->right);
	//region->left = NULL;
	//region->right = NULL;
	//region->pokemon = NULL;
	//region->parent = NULL;
	//delete tmp;
	//delete region;

}

Region& Region::operator=(const Region& newRegion){
	if(this != &newRegion){ /* Prevents self-assignment */
		clearRegion(left);
		clearRegion(right);
		this->pokemon = NULL;
		this->pokemonCount = 0;

		this->left = copyRegion(newRegion.left);
		this->right = copyRegion(newRegion.right);
		this->parent = newRegion.parent;
		this->pokemon = newRegion.pokemon;

		this->min_x = newRegion.min_x;
		this->min_y = newRegion.min_y;
		this->min_z = newRegion.min_z;

		this->max_x = newRegion.max_x;
		this->max_y = newRegion.max_y;
		this->max_z = newRegion.max_z;

		this->pokemonCount = newRegion.pokemonCount;
	}
}
