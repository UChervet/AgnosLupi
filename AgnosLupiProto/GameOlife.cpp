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

GameOlife::GameOlife(int w, int h, int tauxGerme, int nbStep, bool config)
    : Simulation(w,h,nbStep), m_tauxGerme(tauxGerme), m_fixedConfig(config)
{ }

void GameOlife::createGermeAlea()
{
    int nbCellStart = (m_hGrid*m_wGrid*m_tauxGerme)/100;
    for(int i = 0; i < nbCellStart; i++)
    {
        m_listOrganisms.push_back(Organism(m_grid, m_iconCell, "unlabelled"));
    }
    for(int i = 0; i < m_listOrganisms.size(); i++)
    {
        m_grid->addOrganism(&m_listOrganisms[i]);
    }
}

void GameOlife::createDroplet(int taille, int center[])
{
    for(int i = 0; i < taille; i ++)
    {
        for(int j = 0; j < taille; j++)
        {
            if(rand() % 100 < m_tauxGerme)
                m_listOrganisms.push_back(Organism(center[0]-taille/2+i+j, center[1]-taille/2+i-j,m_grid, m_iconCell, "unlabelled"));
        }
    }

    for(int i = 0; i < m_listOrganisms.size(); i++)
    {
        m_grid->addOrganism(&m_listOrganisms[i]);
    }

}

void GameOlife::createFixGerme()
{
    int c[2] = {m_wGrid/4,m_hGrid/4}; //centre du carre
    createDroplet(m_hGrid/8, c);

    c[0] = 3*m_hGrid/4;
    c[1] = 3*m_wGrid/4;
    createDroplet(m_hGrid/10, c);

    c[0] = 3*m_hGrid/4;
    c[1] = m_wGrid/2;
    createDroplet(m_hGrid/10, c);
}

void GameOlife::init()
{
    m_simuName = "Game Of Life.";
    m_border = new Organism(0, 0, m_grid);
    m_border->setLabel("obstacle");
    m_border->setIcon('@');
    m_border->setColor(10);
    m_grid->setBorders(m_border);

    if (m_fixedConfig)
    {
        this->createFixGerme();
    } else {
        this->createGermeAlea();
    }
}

void GameOlife::placeOneCell(int x, int y, char icon, char* label)
{
    m_listOrganisms.push_back(Organism(x, y, m_grid, icon, label));
    m_grid->addOrganism(&m_listOrganisms.back());
}

void GameOlife::placeAglider(int xCenter, int yCenter)
{
    this->placeOneCell(xCenter-1,yCenter-1);
    this->placeOneCell(xCenter,yCenter-1);
    this->placeOneCell(xCenter+1,yCenter-1);
    this->placeOneCell(xCenter+1,yCenter);
    this->placeOneCell(xCenter,yCenter+1);
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


void GameOlife::setConfig(bool config)
{
    m_fixedConfig = config;
}


void GameOlife::runOneStep()
{
    std::vector <Organism> newListOrganisms;

    for(int i = 1; i < m_wGrid-1; i++) //ne pas parcourir les bords
    {
        for(int j = 1; j < m_hGrid-1; j++)
        {
            //survie
            if(m_grid->getOrganismAt(i, j))
            {
                for(int indexS = 0; indexS < m_survieRule.size(); indexS++)
                {
                    if(m_grid->countNeighboorType(i,j,"all") == m_survieRule[indexS])
                        newListOrganisms.push_back(Organism(i,j,m_grid, m_iconCell, "unlabelled"));
                }
            }
            //reproduction
            if(!m_grid->getOrganismAt(i, j))
            {
                for(int indexR = 0; indexR < m_creationRule.size(); indexR++)
                {
                    if(m_grid->countNeighboorType(i,j,"all") == m_creationRule[indexR])  //utiliser des conversions binaire et un masque pour la suite
                    {
                        newListOrganisms.push_back(Organism(i,j,m_grid, m_iconCell, "unlabelled"));
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

