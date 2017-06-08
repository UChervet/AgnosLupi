#ifndef GRID2D_H_INCLUDED
#define GRID2D_H_INCLUDED

#include "Organism.h"
#include <vector>



class Organism;

class Grid2D
{
public :
    Grid2D(int w = 20, int h = 20);
    //~Grid2D();
    void setBorders(Organism * obstacle);
    int getWidth();
    int getHeight();

    void displayGrid();
    void addRectangleObst(Organism * obstacle, int x1, int y1, int x2, int y2);
    void addOrganism(int x, int y, Organism * organism);
    void supprOrganism(int x, int y);
    void removeOrganism(int x, int y);
    Organism * getOrganismAt(int x, int y);

    void getListOrganisms( std::vector <Organism *> &listOrganisms);


protected :
    int m_width; //coord en x
    int m_height; //coord en y
    // This is a pointer to pointer to Organism. I will use it as
	// 1-D array of pointers to Organism, and not 2D array.
	// I used pointers to Organisms rather that char, because
	// it gives you the way of calling this WorldMap inhabinants
	// member functions directly form the WorldMap class.
	// Is it clear, or am I hard to follow?
	Organism** m_organisms; // flattened, not to add pointer confusion
				// getOrganismAt() will handle doind 2d calculations
};

#endif // GRID2D_H_INCLUDED
