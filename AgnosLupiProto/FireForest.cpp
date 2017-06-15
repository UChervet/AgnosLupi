#include "FireForest.h"
#include "Organism.h"
#include "Grid2D.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

FireForest::FireForest()
{}

FireForest::FireForest(int w, int h, int nbStep, int densite, int probaPropa) : Simulation(w,h,nbStep), m_densite(densite), m_probaPropa(probaPropa)
{ }

void FireForest::init()
{
    m_border = new Organism(0, 0, m_grid);
    m_border->setLabel("obstacle");
    m_border->setIcon('@');
    m_border->setColor(1);
    m_grid->setBorders(m_border);

    initColor();
    createForest();
    startFire();
}

void FireForest::initColor()
{
    standend();
    init_pair(3, COLOR_YELLOW, COLOR_RED);  //fire
    init_pair(2, COLOR_GREEN, COLOR_BLACK);  //tree
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);  //cendre
    init_pair(1, COLOR_WHITE, COLOR_BLACK);  //default

}

void FireForest::createForest()
{
    for(int i = 1; i < m_grid->getWidth()-1; i++)
    {
        for(int j = 1; j < m_grid->getHeight()-1; j++)
        {
            if(rand() % 100 < m_densite)
                m_listOrganisms.push_back(Organism(i,j,m_grid, m_arbreChar, m_arbreLb, m_arbreColor));
        }
    }
    for(int i = 0; i < m_listOrganisms.size(); i++)
    {
        m_grid->addOrganism(&m_listOrganisms[i]);
    }
}

void FireForest::startFire()
{
    int fireStartingPoint = rand() % m_listOrganisms.size();
    m_listOrganisms[fireStartingPoint].setColor(m_feuColor);
    m_listOrganisms[fireStartingPoint].setLabel(m_feuLb);
    m_listOrganisms[fireStartingPoint].setIcon(m_feuChar);
}

void FireForest::runOneStep()
{
    std::vector <Organism> newListOrganisms;

    for(int i = 1; i < m_wGrid-1; i++) //ne pas parcourir les bords
    {
        for(int j = 1; j < m_hGrid-1; j++)
        {
            if(m_grid->getOrganismAt(i,j))
            {

                if(m_grid->getOrganismAt(i,j)->getIcon() == m_feuChar)
                {
                    //s'eteint
                    newListOrganisms.push_back(Organism(i,j,m_grid, m_cendreChar, m_cendreLb, m_cendreColor));
                }
                else if(m_grid->countNeighboorType(i,j, m_feuLb) != 0 && m_grid->getOrganismAt(i,j)->getIcon() != m_cendreChar)
                {
                    if(rand() % 100 < m_probaPropa)
                    {
                        //brûle
                        newListOrganisms.push_back(Organism(i,j,m_grid, m_feuChar, m_feuLb, m_feuColor));
                    }
                    else
                    {
                        newListOrganisms.push_back(Organism(i,j,m_grid, m_grid->getOrganismAt(i,j)->getIcon(), m_grid->getOrganismAt(i,j)->getLabel(), m_grid->getOrganismAt(i,j)->getColor() ));
                    }
                }
                else
                {
                    newListOrganisms.push_back(Organism(i,j,m_grid, m_grid->getOrganismAt(i,j)->getIcon(), m_grid->getOrganismAt(i,j)->getLabel(), m_grid->getOrganismAt(i,j)->getColor() ));
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
