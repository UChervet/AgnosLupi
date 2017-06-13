#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "Grid2D.h"
#include "Organism.h"
#include "GameOlife.h"
#include <time.h>
#include <string>
#include <stdio.h>
#include "Immigration.h"

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
    srand(time(NULL)); // initialisation de rand
    int h = 50;
    int w = 50;
    int tauxGerme = 50;
    int nbStep = 10000;
    int ratioPop = 75;

    Immigration* simulation = new Immigration(h, w, tauxGerme, nbStep, ratioPop);
    simulation->init();
    simulation->createFixGerme();
    //simulation->placeAglider(2,30);

    simulation->setCreationRules("36");
    simulation->setSurvieRules("23");




    //record de grossissement
//    simulation->clearGrid();
//    simulation->placeOneCell(15,15);
//    simulation->placeOneCell(17,15);
//    simulation->placeOneCell(17,16);
//    simulation->placeOneCell(19,17);
//    simulation->placeOneCell(19,18);
//    simulation->placeOneCell(19,19);
//
//    simulation->placeOneCell(21,19);
//    simulation->placeOneCell(21,20);
//    simulation->placeOneCell(21,18);
//    simulation->placeOneCell(22,19);

    //machine tournante
//    simulation->clearGrid();
//    simulation->placeOneCell(15,16);
//    simulation->placeOneCell(15,18);
//    simulation->placeOneCell(16,15);
//    simulation->placeOneCell(17,16);
//    simulation->placeOneCell(17,19);
//    simulation->placeOneCell(18,18);
//    simulation->placeOneCell(18,19);
//    simulation->placeOneCell(18,20);

    //glider
//    simulation->clearGrid();
//    simulation->placeAglider(20,20);


    //jeu de la vie
//    simulation->setSurvieRules("23");
//    simulation->setCreationRules("3");

    simulation->displaySimu();
    char tempo;
    scanf("%c",&tempo);
    simulation->runSimuImmi();

    return 0;
}





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
