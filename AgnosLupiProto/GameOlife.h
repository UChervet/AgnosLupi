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
    void init();
    void setConfig(bool config = false);
    void displaySimu();
    void runSimu(bool stepByStep = false);
    void setSurvieRules(std::string mask);
    void setCreationRules(std::string mask);
    void clearGrid();
    void placeOneCell(int x, int y, char icon = 'X', char* label = "unlabelled");
    void placeAglider(int xCenter, int yCenter);


protected :
    int m_wGrid, m_hGrid; //dimension grille de simulation
    int m_tauxGerme;
    int m_nbStemSimu;
    bool m_fixedConfig = false;
    std::vector <int>  m_survieRule;
    std::vector <int>  m_creationRule;
    Grid2D * m_grid;
    Organism* m_border;
    std::vector <Organism> m_listOrganisms;

    void createDroplet(int taille, int center[]);
    void runOneStep();
    void addSurvieRule(int a);
    void addCreationRule(int a);
    void createGermeAlea();
    void createFixGerme();
};

#endif // GAMEOLIFE_H_INCLUDED
