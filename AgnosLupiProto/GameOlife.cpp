#include "GameOlife.h"
#include "Grid2D.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

GameOlife::GameOlife()
{ }

GameOlife::GameOlife(int w, int h, int tauxGerme, int nbStep)
    : m_wGrid(w), m_hGrid(h), m_tauxGerme(tauxGerme), m_nbStemSimu(nbStep)
{
    m_grid = new Grid2D(w,h);
}

void GameOlife::createGermeAlea()
{
    int nbCellStart = (m_hGrid*m_wGrid*m_tauxGerme)/100;
    for(int i = 0; i < nbCellStart; i++)
    {
        m_listOrganisms.push_back(Organism(m_grid, 'X'));
    }
    for(int i = 0; i < m_listOrganisms.size(); i++)
    {
        m_grid->addOrganism(&m_listOrganisms[i]);
    }
}

void GameOlife::init()
{
    this->createGermeAlea();
    m_border = new Organism(0, 0, m_grid);
    m_border->setLabel("obstacle");
    m_border->setIcon('@');
    m_grid->setBorders(m_border);
}

void GameOlife::displaySimu()
{
    m_grid->displayGrid();
}

void GameOlife::runOneStep()
{
    std::vector <Organism> newListOrganisms;

    for(int i = 1; i < m_wGrid-1; i++) //ne pas parcourir les bords
    {
        for(int j = 1; j < m_hGrid-1; j++)
        {
            if(m_grid->countNeighboor(i,j,true) == 2)  //utiliser des conversions binaire et un masque pour la suite
            {
                if(m_grid->getOrganismAt(i, j))
                    newListOrganisms.push_back(Organism(i,j,m_grid, 'X'));
            }
            if(m_grid->countNeighboor(i,j,true) == 3)  //utiliser des conversions binaire et un masque pour la suite
            {
                if(!m_grid->getOrganismAt(i, j))
                    newListOrganisms.push_back(Organism(i,j,m_grid, 'X'));
            }
        }
    }

    for(int i = 0; i < m_listOrganisms.size(); i++)
    {
        m_grid->supprOrganism(m_listOrganisms[i].getX(), m_listOrganisms[i].getY());
    }

    m_listOrganisms = newListOrganisms;
    for(int i = 0; i < m_listOrganisms.size(); i++)
    {
        m_grid->addOrganism(&m_listOrganisms[i]);
    }
}

void GameOlife::runSimu()
{
    for(int i = 0; i < m_nbStemSimu; i++)
    {
        this->runOneStep();
        _sleep(80);
        system("cls");
        this->displaySimu();
        cout<<"Step simulation : " << i << endl;
    }
}
