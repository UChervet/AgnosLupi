#ifndef GAMEOLIFE_H_INCLUDED
#define GAMEOLIFE_H_INCLUDED

#include "Simulation.h"
#include "Organism.h"
#include "Grid2D.h"
#include <vector>
#include <string.h>

class GameOlife : public Simulation
{
public :
    GameOlife();
    GameOlife(int w, int h, int tauxGerme, int nbStep, bool config = false);

    void init();
    void setConfig(bool config = false);
    void setSurvieRules(std::string mask);
    void setCreationRules(std::string mask);
    void placeOneCell(int x, int y, char icon = 'X', char* label = "unlabelled");
    void placeAglider(int xCenter, int yCenter);

protected :
    int m_tauxGerme;
    chtype m_iconCell = ACS_LANTERN;

    bool m_fixedConfig = false;
    std::vector <int>  m_survieRule;
    std::vector <int>  m_creationRule;

    void createDroplet(int taille, int center[]);

    void runOneStep();

    void addSurvieRule(int a);
    void addCreationRule(int a);
    void createGermeAlea();
    void createFixGerme();
};

#endif // GAMEOLIFE_H_INCLUDED
