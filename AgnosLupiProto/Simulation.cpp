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

string Simulation::getSimuName()
{
    return m_simuName;
}

void Simulation::resetSimu(bool stepByStep)
{
    wclear(stdscr);
    this->clearGrid();
    this->init();
    runPrettySimu(stepByStep);
}

void Simulation::clearGrid()
{
    m_grid->clearGrid();

    while(!m_listOrganisms.empty())
        m_listOrganisms.pop_back();

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

void Simulation::runPrettySimu(bool stepByStep) //ajouter les arr�ts reset F1 play pause F2 reset (clear init) double F1 end
{
    bool pause = false;
    int interrup = 0; //will get the value of pressed keyboard keys

    for(int i = 0; i < m_nbStemSimu; i++)
    {
        if(!pause) //boucle de simulation play/pause par F1 key
        {
            timeout(10); //remet un timeout pour eviter de rendre le getch bloquant
            this->runOneStep();
            if(stepByStep)
            {
                getch(); //bloquant, passe pas � l'�tape suivant tant qu'aucune touche n'est press�e
            }
            else
            {
                _sleep(70);
            }
            this->prettyDisplay();
            string jeanjean = getSimuName() + " Number of steps : %d";
            mvwprintw(stdscr, LINES - 3, 0, jeanjean.c_str(),i+1);
            mvwprintw(stdscr, LINES - 2, 0, "Size of the grid : w = %d, h = %d and %d cases.",m_grid->getWidth(),m_grid->getHeight(), (m_grid->getWidth() -1)*(m_grid->getHeight() -1));
            wrefresh(stdscr);

            interrup = getch(); //non bloquant gr�ce au timeout(10)
            if(interrup == KEY_F(1)) //pause sur F1
                pause = !pause;
        }


        while(pause) //boucle (bloquante) de pause avec la touche F1
        {
            mvwprintw(stdscr, LINES/2, COLS/2, "PAUSE",i+1);
            wrefresh(stdscr);
            timeout(-1); //d�sactive le timeout pour rendre le getch bloquant
            interrup = getch();
            /// TODO switch-case
            if(interrup == KEY_F(1))
                pause = !pause;

            if(interrup == KEY_F(2))
            {
                //termine la simu en cours et en lance une autre avec le reset
                resetSimu(stepByStep);
                return; //en r�alit� la fonction simu en cours s'arr�tera une fois sortie du resetSimu (�vite le bug des F3)
            }

            if(interrup == KEY_F(3)) //force quit depuis la pause
            {
                return;
            }
        }

        if(interrup == KEY_F(3)) //force quit depuis le play
        {
            timeout(-1);
            return;
        }

    }
}
