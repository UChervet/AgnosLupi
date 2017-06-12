#include "Immigration.h"
#include "GameOlife.h"
#include <string>
#include <vector>
#include <stdlib.h>

Immigration::Immigration(int w, int h, int tauxGerme, int nbStep, int startingRatio) : GameOlife(w, h, tauxGerme, nbStep), m_startingRatio(startingRatio)
{ }

void Immigration::init()
{
    m_border = new Organism(0, 0, m_grid);
    m_border->setLabel("obstacle");
    m_border->setIcon('@');
    m_grid->setBorders(m_border);
}

void Immigration::createGermeAlea()
{
    int nbCellStart = (m_hGrid*m_wGrid*m_tauxGerme)/100;
    for(int i = 0; i < nbCellStart; i++)
    {
        if(rand() % 100 < m_startingRatio)
        {
            m_listOrganisms.push_back(Organism(m_grid, 'X', "cross"));
        }
        else
        {
            m_listOrganisms.push_back(Organism(m_grid, 'O', "cercle"));
        }

    }
    for(int i = 0; i < m_listOrganisms.size(); i++)
    {
        m_grid->addOrganism(&m_listOrganisms[i]);
    }
}



void Immigration::runOneStep()
{
    std::vector <Organism> newListOrganisms;

    for(int i = 1; i < m_wGrid-1; i++) //ne pas parcourir les bords
    {
        for(int j = 1; j < m_hGrid-1; j++)
        {
            //survie
            for(int indexS = 0; indexS < m_survieRule.size(); indexS++)
            {
                if(m_grid->countNeighboorType(i,j,"all") == m_survieRule[indexS])
                {
                    if(m_grid->getOrganismAt(i, j))
                    {
                        //en cas de survie la cellule reste du même type
                        newListOrganisms.push_back(Organism(i,j,m_grid, m_grid->getOrganismAt(i, j)->getIcon(), m_grid->getOrganismAt(i, j)->getLabel()));
                    }
                }
            }
            //reproduction
            for(int indexR = 0; indexR < m_creationRule.size(); indexR++)
            {
                if(m_grid->countNeighboorType(i,j,"all") == m_creationRule[indexR])  //utiliser des conversions binaire et un masque pour la suite
                {
                    //en cas de naissance la cellule sera du type majoritaire dans son voisinnage
                    if(m_grid->countNeighboorType(i,j,"cross") > m_grid->countNeighboorType(i,j,"cercle"))
                    {
                        newListOrganisms.push_back(Organism(i,j,m_grid, 'X', "cross"));
                    } else {
                        newListOrganisms.push_back(Organism(i,j,m_grid, 'O', "cercle"));
                    }
                }
            }
        }
    }

    for(int i = 0; i < m_listOrganisms.size(); i++)
    {
        m_grid->removeOrganism(m_listOrganisms[i].getX(), m_listOrganisms[i].getY());
    }

    m_listOrganisms = newListOrganisms;
    for(int i = 0; i < m_listOrganisms.size(); i++)
    {
        m_grid->addOrganism(&m_listOrganisms[i]);
    }
}


