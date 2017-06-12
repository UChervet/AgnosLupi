#include "GameOlife.h"
#include "Grid2D.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

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

    m_border = new Organism(0, 0, m_grid);
    m_border->setLabel("obstacle");
    m_border->setIcon('@');
    m_grid->setBorders(m_border);

    this->createGermeAlea();
}

void GameOlife::addCreationRule(int a)
{
    m_creationRule.push_back(a);
}

void GameOlife::addSurvieRule(int a)
{
    m_survieRule.push_back(a);
}


void GameOlife::setCreationRules(string mask)
{
    stringstream ss;
    string s2;

    for(int i = 0; i < 9; i++)
    {
        ss.str(string());
        ss.clear();
        s2 = "";
        ss << i;
        s2 = ss.str();
        size_t found = mask.find(s2);
        if(found != string::npos) //en fait faut test différement le find
        {
            m_creationRule.push_back(i);
        }
    }
}

void GameOlife::setSurvieRules(string mask)
{
    stringstream ss;
    string s2;

    for(int i = 0; i < 9; i++)
    {
        ss.str(string());
        ss.clear();
        s2 = "";
        ss << i;
        s2 = ss.str();
        size_t found = mask.find(s2);
        if(found != string::npos)          //en fait faut test différement le find
        {
            m_survieRule.push_back(i);
        }
    }
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
            //survie
            for(int indexS = 0; indexS < m_survieRule.size(); indexS++)
            {
                if(m_grid->countNeighboor(i,j,true) == m_survieRule[indexS])  //utiliser des conversions binaire et un masque pour la suite
                {
                    if(m_grid->getOrganismAt(i, j))
                        newListOrganisms.push_back(Organism(i,j,m_grid, 'X'));
                }
            }
            //reproduction
            for(int indexR = 0; indexR < m_creationRule.size(); indexR++)
            {
                if(m_grid->countNeighboor(i,j,true) == m_creationRule[indexR])  //utiliser des conversions binaire et un masque pour la suite
                {
                        newListOrganisms.push_back(Organism(i,j,m_grid, 'X'));
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

void GameOlife::runSimu(bool stepByStep)
{
    for(int i = 0; i < m_nbStemSimu; i++)
    {
        this->runOneStep();
        if(stepByStep)
        {
            char tempo;
            scanf("%c",&tempo);
        } else {
            //_sleep(80); //si suit recommandation pas c++11 version
            _sleep(80);
        }
        system("cls");
        this->displaySimu();
        cout<<"Step simulation : " << i << endl;

    }
}
