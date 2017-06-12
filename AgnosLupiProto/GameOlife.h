#ifndef GAMEOLIFE_H_INCLUDED
#define GAMEOLIFE_H_INCLUDED

#include "Organism.h"
#include "Grid2D.h"
#include <vector>
#include <string.h>

class GameOlife
{
public :
    GameOlife();
    GameOlife(int w, int h, int tauxGerme, int nbStep);
    void createGermeAlea();
    void init();
    void displaySimu();
    void runOneStep();
    void runSimu(bool stepByStep = false);
    void addSurvieRule(int a);
    void addCreationRule(int a);
    void setSurvieRules(std::string mask);
    void setCreationRules(std::string mask);


protected :
    int m_wGrid, m_hGrid; //dimension grille de simulation
    int m_tauxGerme;
    int m_nbStemSimu;
    std::vector <int>  m_survieRule;
    std::vector <int>  m_creationRule;
    Grid2D * m_grid;
    Organism* m_border;
    std::vector <Organism> m_listOrganisms;

};

#endif // GAMEOLIFE_H_INCLUDED
