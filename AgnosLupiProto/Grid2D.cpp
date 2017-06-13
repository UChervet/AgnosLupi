#include "Grid2D.h"
#include "Organism.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>

using namespace std;

Grid2D::Grid2D(int w, int h): m_width(w), m_height(h)
{
    // I change pointer to pointer into a new array of pointers of
    // size of my choice
    m_organisms = new Organism* [m_width * m_height];


    for (int i = 0; i < (m_width * m_height); i++)
    {
        m_organisms[i] = 0; // no organism there yet so points to 0.
    }

}



/*Grid2D::~Grid2D()
{
    clearPtrGrid();
}*/

int Grid2D::getWidth()
{
    return m_width;
}

int Grid2D::getHeight()
{
    return m_height;
}

void Grid2D::setBorders(Organism * obstacle)
{
    addRectangleObst(obstacle, 0, 0, m_width-1, m_height-1);
}

void Grid2D::addRectangleObst(Organism * obstacle, int x1, int y1, int x2, int y2)
{
    for(int y = y1; y <= y2; y ++)
    {
        addOrganism(x1, y,obstacle);
        addOrganism(x2, y, obstacle);
    }
    for(int x = x1+1; x < x2; x ++)
    {
        addOrganism(x,y1,obstacle);
        addOrganism(x,y2,obstacle);
    }
}


// 2-D coordinates to look in 1-D array
Organism* Grid2D::getOrganismAt( int x, int y)
{
    return m_organisms [ m_height * x + y ];
}

void Grid2D::addOrganism(int x, int y, Organism * organism)
{
    m_organisms [ m_height * (x % m_width) + (y % m_height) ] = organism;
}

void Grid2D::addOrganism(Organism * organism)
{
    m_organisms [ m_height * (organism->getX() % m_width) + (organism->getY() % m_height) ] = organism;
}

void Grid2D::removeOrganism(int x, int y)
{
    m_organisms [ m_height * (x % m_width) + (y % m_height) ]  = 0;
}

void Grid2D::supprOrganism(int x, int y)
{
    delete m_organisms [ m_height * (x % m_width) + (y % m_height) ];
    m_organisms [ m_height * (x % m_width) + (y % m_height) ]  = 0;
}

void Grid2D::clearGrid()
{
    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j <m_height; j++)
        {
            supprOrganism(i,j);
        }
    }
}

void Grid2D::displayGrid()
{
    for(int i=0; i < m_width; i++)
    {
        for(int j=0; j < m_height; j++)
        {
            if(!getOrganismAt(i,j))
            {
                //si case vide
                cout<<" "; //"."
            }
            else
            {
                //si case occupee
                color(getOrganismAt(i,j)->getColor(),0);
                cout << getOrganismAt(i,j)->getIcon();
            }
        }
        cout<<endl;
    }
}

int Grid2D::countNeighboor(int x, int y, bool countDiag)
{
    int nbNeighb = 0;

    if(this->getOrganismAt(x+1, y))
    {
        if(strcmp((this->getOrganismAt(x+1, y)->getLabel()).c_str(), "obstacle") != 0 )
            nbNeighb++;
    }
    if(this->getOrganismAt(x-1, y))
    {
        if(strcmp((this->getOrganismAt(x-1, y)->getLabel()).c_str(), "obstacle") != 0 )
            nbNeighb++;
    }
    if(this->getOrganismAt(x, y+1))
    {
        if(strcmp((this->getOrganismAt(x, y+1)->getLabel()).c_str(), "obstacle") != 0 )
            nbNeighb++;
    }
    if(this->getOrganismAt(x, y-1))
    {
        if(strcmp((this->getOrganismAt(x, y-1)->getLabel()).c_str(), "obstacle") != 0 )
            nbNeighb++;
    }

    if(countDiag)
    {
        if(this->getOrganismAt(x+1, y+1))
        {
            if(strcmp((this->getOrganismAt(x+1, y+1)->getLabel()).c_str(), "obstacle") != 0 )
                nbNeighb++;
        }
        if(this->getOrganismAt(x-1, y-1))
        {
            if(strcmp((this->getOrganismAt(x-1, y-1)->getLabel()).c_str(), "obstacle") != 0 )
                nbNeighb++;
        }
        if(this->getOrganismAt(x-1, y+1))
        {
            if(strcmp((this->getOrganismAt(x-1, y+1)->getLabel()).c_str(), "obstacle") != 0 )
                nbNeighb++;
        }
        if(this->getOrganismAt(x+1, y-1))
        {
            if(strcmp((this->getOrganismAt(x+1, y-1)->getLabel()).c_str(), "obstacle") != 0 )
                nbNeighb++;
        }
    }
    return nbNeighb;
}




int Grid2D::countNeighboorType(int x, int y, char* label)
{
    int nbNeighb = 0;

    if(strcmp(label, "all") == 0)
    {
        nbNeighb = countNeighboor(x,y,true);
    }
    else
    {

        if(this->getOrganismAt(x+1, y))
        {
            if(strcmp((this->getOrganismAt(x+1, y)->getLabel()).c_str(), label) == 0 )
                nbNeighb++;
        }
        if(this->getOrganismAt(x-1, y))
        {
            if(strcmp((this->getOrganismAt(x-1, y)->getLabel()).c_str(), label) == 0 )
                nbNeighb++;
        }
        if(this->getOrganismAt(x, y+1))
        {
            if(strcmp((this->getOrganismAt(x, y+1)->getLabel()).c_str(), label) == 0 )
                nbNeighb++;
        }
        if(this->getOrganismAt(x, y-1))
        {
            if(strcmp((this->getOrganismAt(x, y-1)->getLabel()).c_str(), label) == 0 )
                nbNeighb++;
        }

        if(this->getOrganismAt(x+1, y+1))
        {
            if(strcmp((this->getOrganismAt(x+1, y+1)->getLabel()).c_str(), label) == 0 )
                nbNeighb++;
        }
        if(this->getOrganismAt(x-1, y-1))
        {
            if(strcmp((this->getOrganismAt(x-1, y-1)->getLabel()).c_str(), label) == 0 )
                nbNeighb++;
        }
        if(this->getOrganismAt(x-1, y+1))
        {
            if(strcmp((this->getOrganismAt(x-1, y+1)->getLabel()).c_str(), label) == 0 )
                nbNeighb++;
        }
        if(this->getOrganismAt(x+1, y-1))
        {
            if(strcmp((this->getOrganismAt(x+1, y-1)->getLabel()).c_str(), label) == 0 )
                nbNeighb++;
        }
    }

    return nbNeighb;
}



void Grid2D::getListOrganisms(std::vector <Organism *> &listOrganisms)
{
    listOrganisms.clear();

    for(int x = 0; x < m_width; x++)
        {
            for(int y = 0; y < m_height; y++)
            {
                if(getOrganismAt(x, y) != 0)
                {
                    if(getOrganismAt(x, y)->getLabel() != "obstacle")
                    {
                        listOrganisms.push_back(getOrganismAt(x, y));
                    }
                }
            }
        }
}


void color(int t,int f)
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(H,f*16+t);
}
