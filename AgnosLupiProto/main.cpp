#include <iostream>
#include <cstdlib>
#include <stdlib.h>         /* srand, rand */
#include <time.h>         /* time, init rand */
#include <string>
#include <stdio.h>
#include "Grid2D.h"
#include "Organism.h"
#include "GameOlife.h"
#include "Immigration.h"
#include "FireForest.h"
#include "curses.h"
//#include "panel.h"

/*
*   Version Git de AgnusLupi
*   Documentation à faire
*/

using namespace std;



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

int main()
{
    //init
    initscr();			//Start curses mode
    start_color();     //Start the curses color mode
    keypad(stdscr, true); //enable the use of all the keyboard
    curs_set(0);    //hide the cursor
    raw(); /*disable line buffering*/
    noecho();

    srand(time(NULL)); // initialisation de rand

    int ch;
    int h =  LINES - 3;
    int w = COLS -1;
    int nbStep = 10000;

//    Immigration* simulation = new Immigration(w,h,20,nbStep,50);
//    //GameOlife* simulation = new GameOlife(w,h,40,nbStep);
//    //simulation->setConfig(true);
//    simulation->init();
//    simulation->createFixGerme();
//    //simulation->createGermeAlea();
//    simulation->setCreationRules("36");
//    simulation->setSurvieRules("23");

    FireForest* simulation = new FireForest(w,h,nbStep,60,60);
    simulation->init();

    simulation->runPrettySimu();

    refresh();			/* Print it on to the real screen */
    getch();			/* Wait for user input */
    endwin();			/* End curses mode		  */


    return 0;
}


//    srand(time(NULL)); // initialisation de rand
//    int h = 100;
//    int w = 50;
//    int nbStep = 10000;
//
//    FireForest* simulation = new FireForest(w,h,nbStep,80,40);
//    simulation->init();
//
//    simulation->displaySimu();
//    char tempo;
//    scanf("%c",&tempo);
//    simulation->runSimu();


//int main()
//{
//    srand(time(NULL)); // initialisation de rand
//    int h = 50;
//    int w = 50;
//    int tauxGerme = 80;
//    int nbStep = 10000;
//
//    GameOlife* simulation = new GameOlife(h, w, tauxGerme, nbStep);
//    simulation->setConfig(true);
//    simulation->init();
//
////    //jeu de la vie
////    simulation->setSurvieRules("23");
////    simulation->setCreationRules("3");
//
//    //highlife
////    simulation->setSurvieRules("23");
////    simulation->setCreationRules("36");
//
//    //diamoeba
////    simulation->setSurvieRules("5678");
////    simulation->setCreationRules("35678");
//
//    //amoeba
////    simulation->setSurvieRules("1358");
////    simulation->setCreationRules("357");
//
//    //labyrinth
////    simulation->setSurvieRules("12345");
////    simulation->setCreationRules("3");
//
//    //day&night
////    simulation->setSurvieRules("345678");
////    simulation->setCreationRules("3678");
//
//    //life 3-4
//    simulation->setSurvieRules("34");
//    simulation->setCreationRules("34");
//
//
//    simulation->displaySimu();
//    char tempo;
//    scanf("%c",&tempo);
//    simulation->runSimu();
//
//    return 0;
//}
