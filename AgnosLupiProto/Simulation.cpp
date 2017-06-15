#include "Simulation.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "curses.h"
#include "panel.h"

using namespace std;

Simulation::Simulation()
{}

Simulation::Simulation(int w, int h, int nbStep)
    : m_wGrid(w), m_hGrid(h), m_nbStemSimu(nbStep)
{
    m_grid = new Grid2D(w,h);
}

void Simulation::init()
{
    m_border = new Organism(0, 0, m_grid);
    m_border->setLabel("obstacle");
    m_border->setIcon('@');
    m_grid->setBorders(m_border);
}

void Simulation::clearGrid()
{
    m_grid->clearGrid();

    //remettre les bordures
    m_border = new Organism(0, 0, m_grid);
    m_border->setLabel("obstacle");
    m_border->setIcon('@');
    m_grid->setBorders(m_border);
}

void Simulation::displaySimu()
{
    m_grid->displayGrid();
}

void Simulation::prettyDisplay()
{
    m_grid->prettyDisplayGrid();
}

void Simulation::runOneStep()
{}

void Simulation::runSimu(bool stepByStep)
{
    for(int i = 0; i < m_nbStemSimu; i++)
    {
        this->runOneStep();
        if(stepByStep)
        {
            char tempo;
            cout<<"Press enter to start : ";
            scanf("%c",&tempo);
        }
        else
        {
            _sleep(80);
        }
        system("cls");
        this->displaySimu();
        cout<<"Step simulation : " << i << endl;
    }
}

void Simulation::runPrettySimu(bool stepByStep) //ajouter les arrêts reset F1 play pause F2 reset (clear init) double F1 end
{
    for(int i = 0; i < m_nbStemSimu; i++)
    {
        this->runOneStep();
        if(stepByStep)
        {
            getch();
        }
        else
        {
            _sleep(80);
        }
        this->prettyDisplay();
        mvwprintw(stdscr, LINES - 3, 0, "Number of steps : %d",i+1);
        mvwprintw(stdscr, LINES - 2, 0, "Size of the grid : w = %d and h = %d",m_grid->getWidth(),m_grid->getHeight());
        wrefresh(stdscr);

    }
}
