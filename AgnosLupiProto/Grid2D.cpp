#include "Grid2D.h"
#include "Organism.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Grid2D::Grid2D(int w, int h): m_width(w), m_height(h)
{
    // I change pointer to pointer into a new array of pointers of
    // size of my choice
    m_organisms = new Organism* [m_width * m_height];


    for (int i = 0; i < m_width  * m_height; i++)
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
///TODO osbtacle cercle ?

// 2-D coordinates to look in 1-D array
Organism* Grid2D::getOrganismAt( int x, int y)
{
    return m_organisms [ m_width * x + y ];
}

void Grid2D::addOrganism(int x, int y, Organism * organism)
{
    m_organisms [ m_width * x + y ] = organism;
}

void Grid2D::removeOrganism(int x, int y)
{
    m_organisms [ m_width * x + y ] = 0;
}

void Grid2D::supprOrganism(int x, int y)
{
    delete m_organisms [ m_width * x + y ];
    m_organisms [ m_width * x + y ] = 0;
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
                cout << getOrganismAt(i,j)->getIcon();
            }
        }
        cout<<endl;
    }
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
