#include "Organism.h"
#include "Grid2D.h"
#include <stdlib.h>
#include <string>

using namespace std;


Organism::Organism(int x, int y) : m_X(x), m_Y(y)
{
    m_grid = 0;
    m_label = "unlabelled"; //default unknown label
    m_icon = '�';  //default unknown icon
}

Organism::Organism(int x, int y, Grid2D * grid) : m_X(x), m_Y(y), m_grid(grid)
{
    m_label = "unlabelled"; //default unknown label
    m_icon = '�'; //default unknown icon
}

int Organism::getX()
{
    return m_X;
}

int Organism::getY()
{
    return m_Y;
}

void Organism::setPosition(int x, int y)
{
    m_X = x;
    m_Y = y;
}

void Organism::setGrid(Grid2D * grid)
{
    m_grid = grid;
}

string Organism::getLabel()
{
    return m_label;
}

void Organism::setLabel(string label)
{
    m_label = label;
}

char Organism::getIcon()
{
    return m_icon;
}

void Organism::setIcon(char icon)
{
    m_icon = icon;
}

/*
*   Check if there is a free cell next to this organism
*/
bool Organism::hasFreeNeighbour()
{
    bool isFree = false;

    if(!m_grid->getOrganismAt(m_X+1, m_Y))
        isFree = true;
    if(!m_grid->getOrganismAt(m_X-1, m_Y))
        isFree = true;
    if(!m_grid->getOrganismAt(m_X, m_Y+1))
        isFree = true;
    if(!m_grid->getOrganismAt(m_X, m_Y-1))
        isFree = true;

    return isFree;
}

/*
*   Move an organism to the (x,y) desired position
*   and update the ptr array of organisms
*/
void Organism::moveTo(int x, int y)
{
    m_grid->addOrganism(x,y,this);
    m_grid->removeOrganism(m_X, m_Y);
    m_X = x;
    m_Y = y;
}


/*
*   Move randomly along one of the cardinal position
*   Check before hand to only move on a free cell
*   Aftermoving return true
*   If no free cell, do not move and return false
*/
bool Organism::walk()
{
    int direction;
    bool hasMoved = false;
    if(hasFreeNeighbour())
    {
        while(!hasMoved)
        {
            direction = rand() % 4;
            switch(direction)
            {
            case 0 : //x++
                if((m_X + 1) < m_grid->getWidth())
                {
                    if (!m_grid->getOrganismAt(m_X+1, m_Y))
                    {
                        this->moveTo(m_X+1, m_Y);
                        hasMoved = true;
                    }

                }
                break;
            case 1 : //y ++
                if((m_Y + 1) < m_grid->getHeight())
                {
                    if(!m_grid->getOrganismAt(m_X, m_Y+1) )
                    {
                        this->moveTo(m_X, m_Y+1);
                        hasMoved = true;
                    }
                }
                break;
            case 2 : //x--
                if(m_X > 0)
                {
                    if(!m_grid->getOrganismAt(m_X-1, m_Y))
                    {
                        this->moveTo(m_X-1, m_Y);
                        hasMoved = true;
                    }
                }
                break;
            case 3: //y--
                if(m_Y > 0)
                {
                    if( !m_grid->getOrganismAt(m_X, m_Y-1))
                    {
                        this->moveTo(m_X, m_Y-1);
                        hasMoved = true;
                    }
                }
                break;
            }
        }
    }

    return hasFreeNeighbour();
}


bool Organism::reproduce()
{
    int x_enfant,y_enfant;
    if(hasFreeNeighbour())
    {
        if(!m_grid->getOrganismAt(m_X+1, m_Y))
        {
            x_enfant = m_X+1;
            y_enfant = m_Y;
        } else {
            if(!m_grid->getOrganismAt(m_X-1, m_Y))
            {
                x_enfant = m_X-1;
                y_enfant = m_Y;
            } else {
                if(!m_grid->getOrganismAt(m_X, m_Y+1))
                {
                    x_enfant = m_X;
                    y_enfant = m_Y+1;
                } else {
                    if(!m_grid->getOrganismAt(m_X, m_Y-1))
                    {
                        x_enfant = m_X;
                        y_enfant = m_Y-1;
                    }
                }
            }
        }
        Organism* enfant = new Organism(x_enfant, y_enfant, m_grid);
        m_grid->addOrganism(enfant->getX(), enfant->getY(), enfant);
    }

    return hasFreeNeighbour();
}