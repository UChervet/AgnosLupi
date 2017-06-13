/**
 * \file Grid2D.h
 * \brief 2 dimensional grid
 *
 * Grille 2D a taille régleable sur laquelle peuvent être placé des
 * des obstacles et des objets Organims.
 *
 * NB: les obstacles sont en réalité des Organims particuliers
 *
 */


#ifndef GRID2D_H_INCLUDED
#define GRID2D_H_INCLUDED

#include "Organism.h"
#include <vector>



class Organism;

class Grid2D
{
public :
    //constructors
    Grid2D(int w = 20, int h = 20);
    //~Grid2D();

    //setup functions
    void setBorders(Organism * obstacle);
    void addRectangleObst(Organism * obstacle, int x1, int y1, int x2, int y2);
    void clearGrid();
    void addOrganism(int x, int y, Organism * organism);
    void addOrganism(Organism * organism);
    void supprOrganism(int x, int y);
    void removeOrganism(int x, int y);

    //accessors
    int getWidth();
    int getHeight();
    Organism * getOrganismAt(int x, int y);
    void getListOrganisms( std::vector <Organism *> &listOrganisms);

    //utility functions
    int countNeighboor(int x, int y, bool countDiag = false);
    int countNeighboorType(int x, int y, char* label);

    //display functions
    void displayGrid();
    void prettyDisplayGrid();


protected :
    int m_width;
    int m_height;
    // This is a pointer to pointer to Organism. I will use it as
	// 1-D array of pointers to Organism, and not 2D array.
	// I used pointers to Organisms rather that char, because
	// it gives you the way of calling this WorldMap inhabinants
	// member functions directly form the WorldMap class.
	// Is it clear, or am I hard to follow?
	Organism** m_organisms; // flattened, not to add pointer confusion
				// getOrganismAt() will handle doind 2d calculations
};

void color(int t,int f); //fonction pour ajouter des couleurs dans la console windows

#endif // GRID2D_H_INCLUDED
