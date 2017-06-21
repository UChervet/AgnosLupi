#include <iostream>
#include <cstdlib>
#include <stdlib.h>         /* srand, rand */
#include <time.h>         /* time, init rand */
#include <string>
#include <stdio.h>
#include "curses.h"         /* better console */
//#include "panel.h"

/**< custom files */
#include "Grid2D.h"
#include "Organism.h"
#include "GameOlife.h"
#include "Immigration.h"
#include "FireForest.h"


/*
*   Version Git de AgnusLupi
*   Documentation à faire
*/

using namespace std;



void Daf();

int main()
{
    //init
    initscr();			//Start curses mode
    start_color();     //Start the curses color mode
    keypad(stdscr, true); //enable the use of all the keyboard
    curs_set(0);    //hide the cursor
    raw(); /*disable line buffering*/
    noecho();
    timeout(10); //permet d'éviter de rendre bloquant les getch()

    srand(time(NULL)); // initialisation de rand

    int ch;
    int h =  LINES - 3;
    int w = COLS -1;
    int nbStep = 10000;

//    FireForest* simulation = new FireForest(w,h,nbStep,80,40);
    Immigration* simulation = new Immigration(w,h,10,nbStep,50);
    //GameOlife* simulation = new GameOlife(w,h,40,nbStep);
    simulation->setCreationRules("3");
    simulation->setSurvieRules("12345");

    simulation->init();
    simulation->runPrettySimu();


    endwin();			/* End curses mode		  */
    return 0;
}




void pbDaf()
{
    cout<<"Compute probleme du mouton de Daf" << endl;

    int nbRepetition = 100000;
    int nbMvtparJour = 120; //120
    int scoreIN = 0, scoreOut = 0, scoreSorti =0;
    bool estSorti = false;
    Grid2D* world = new Grid2D(250,250);

    //le mouton est placé au centre de la grille
    Organism mouton(world->getWidth()/2, world->getHeight()/2, world);
    world->addOrganism(mouton.getX(), mouton.getY(), &mouton);

    cout<<"Nombre de repetions : "<<nbRepetition<<endl;
    for(int repetition = 0; repetition < nbRepetition; repetition ++)
    {
        mouton.moveTo(world->getWidth()/2, world->getHeight()/2);
        estSorti = false;
        for(int step=0; step < nbMvtparJour; step ++)
        {
            mouton.walk();
            if(!estSorti)
            {
                if((mouton.getX() >= (world->getWidth()/2 +20)) || (mouton.getX() <= (world->getWidth()/2 - 20)) || (mouton.getY() <= (world->getHeight()/2 - 20)) || (mouton.getY() >= (world->getHeight()/2 + 20)))
                {
                    scoreSorti++;
                    estSorti = true;
                }
            }
        }
        if((mouton.getX() < (world->getWidth()/2 +20)) && (mouton.getX() > (world->getWidth()/2 - 20)) && (mouton.getY() > (world->getHeight()/2 - 20)) && (mouton.getY() < (world->getHeight()/2 + 20)))
        {
            scoreIN++;
        }
        else
        {
            scoreOut++;
        }
    }
    cout<<"% de jours ou le mouton est dans le champ le soir : "<<((double)scoreIN)/nbRepetition<<endl;
    cout<<"% de jours ou le mouton est hors du champ le soir : "<<(double)scoreOut/nbRepetition<<endl;
    cout<<"% de jours ou le mouton est sorti du champ : "<<(double)scoreSorti/nbRepetition<<endl;


    //destruction des ptrs
    delete world;
    world = 0;

}
