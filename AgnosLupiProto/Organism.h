#ifndef ORGANISM_H_INCLUDED
#define ORGANISM_H_INCLUDED

#include <string>


class Grid2D;

class Organism
{
public :
    //constructors
    Organism(int x, int y);
    Organism(int x, int y, Grid2D * grid);

    //init functions
    /*static*/ void setGrid(Grid2D * grid); /// TO DO :faudrait passer ça en static

    //tool functions
    void moveTo(int x, int y);
    int getX();
    int getY();
    void setPosition(int x, int y);
    bool hasFreeNeighbour();
    std::string getLabel();
    void setLabel(std::string label);
    char getIcon();
    void setIcon(char icon);

    //action functions
    bool walk();
    bool reproduce();
    //void eat();
    //void live();


protected:
    int m_X;
    int m_Y;
    std::string m_label;
    char m_icon;
    int m_livedspan;
    int m_hunger;
    /*static*/ Grid2D* m_grid; /// TO DO : faudrait passer ça en static

};

#endif // ORGANISM_H_INCLUDED
