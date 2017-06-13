/**
 * \file Organism.h
 * \brief Simulation entity
 *
 * Représente une entité vivante pour la simulation. Class mère des différentes
 * particularisation pour les simulations (arbre, prey, predator, etc...)
 * Caractérisé par la grid sur lequel il est place, sa position sur cette grille
 * son étiquette et ses paramètres graphiques
 *
 */


#ifndef ORGANISM_H_INCLUDED
#define ORGANISM_H_INCLUDED

#include <string>


class Grid2D;

class Organism
{
public :
    //constructors
    Organism(int x, int y, int color = 15);
    Organism(int x, int y, Grid2D * grid, int color = 15);
    Organism(int x, int y, Grid2D * grid, char icon, int color = 15);
    Organism(int x, int y, Grid2D * grid, char icon, std::string label, int color = 15);
    Organism(Grid2D * grid, char icon, std::string label = "unlabelled", int color = 15); //random starting x and y

    //init functions
    /*static*/ void setGrid(Grid2D * grid); /// TO DO :faudrait passer ça en static

    //accessors
    int getX();
    int getY();
    void setPosition(int x, int y);
    std::string getLabel();
    void setLabel(std::string label);
    char getIcon();
    void setIcon(char icon);
    int getColor();
    void setColor(int color);

    //utility functions
    void moveTo(int x, int y);
    bool hasFreeNeighbour();
    int countNeighbour(bool countDiag = false);


    //action functions
    bool walk();
    bool reproduce();
    //void eat(); ///TODO
    //void live(); ///TODO
    void die();


protected:
    int m_X;
    int m_Y;
    std::string m_label;
    char m_icon;
    int m_color;
    /*static*/ Grid2D* m_grid; /// TO DO : faudrait passer ça en static

};

#endif // ORGANISM_H_INCLUDED
