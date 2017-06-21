#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "Organism.h"
#include "Grid2D.h"
#include <vector>


class Simulation
{
public:
    Simulation();
    Simulation(int w, int h, int nbStep);

    std::string getSimuName();

    virtual void init() = 0;

    void clearGrid();
    void displaySimu();
    void prettyDisplay();
    void runSimu(bool stepByStep = false);
    void runPrettySimu(bool stepByStep = false);

protected:
    int m_wGrid, m_hGrid; //dimension grille de simulation
    void resetSimu(bool stepByStep = false);
    Grid2D * m_grid;
    Organism* m_border;
    std::vector <Organism> m_listOrganisms;
    int m_nbStemSimu;
    std::string m_simuName;

    virtual void runOneStep() = 0;
};

#endif // SIMULATION_H_INCLUDED
