#ifndef GAMEOLIFE_H_INCLUDED
#define GAMEOLIFE_H_INCLUDED

#include "Organism.h"
#include "Grid2D.h"
#include <vector>

class GameOlife
{
public :
    GameOlife();
    GameOlife(int w, int h, int tauxGerme, int nbStep);
    void createGermeAlea();
    void init();
    void displaySimu();
    void runOneStep();
    void runSimu();


protected :
    int m_wGrid, m_hGrid; //dimension grille de simulation
    int m_tauxGerme;
    int m_nbStemSimu;
    Grid2D * m_grid;
    Organism* m_border;
    std::vector <Organism> m_listOrganisms;

};

#endif // GAMEOLIFE_H_INCLUDED
