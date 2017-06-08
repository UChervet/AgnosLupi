#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "Grid2D.h"
#include "Organism.h"
#include "GameOlife.h"
#include <time.h>
#include <string>
#include <vector>
#include <stdio.h>

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
    int tauxGerme = 10;
    int nbStep = 10000;

    GameOlife* simulation = new GameOlife(h, w, tauxGerme, nbStep);
    simulation->init();

    simulation->displaySimu();
    char tempo;
    //scanf("%c",&tempo);

    simulation->runSimu();

    return 0;
}




/*//    //INIT
    srand(time(NULL)); // initialisation de rand
    int tfinal = 1000; //time step max
    Grid2D* world = new Grid2D(40,30);
    vector <Organism *> listOrganisms;

    //creation of the obstacle object
    Organism* obstacle = new Organism(0, 0, world);
    obstacle->setLabel("obstacle");
    obstacle->setIcon('@');
    world->setBorders(obstacle);

    //creation et placement organisms
    Organism toto(world);
    toto.setIcon('m');
    world->addOrganism(toto.getX(), toto.getY(), &toto);
    Organism ereer(world);
    ereer.setIcon('m');
    world->addOrganism(ereer.getX(), ereer.getY(), &ereer);
    Organism fqsfqs(world);
    fqsfqs.setIcon('m');
    world->addOrganism(fqsfqs.getX(), fqsfqs.getY(), &fqsfqs);
    Organism sdfsd(world);
    sdfsd.setIcon('m');
    world->addOrganism(sdfsd.getX(), sdfsd.getY(), &sdfsd);
    Organism arerer(world);
    arerer.setIcon('m');
    world->addOrganism(arerer.getX(), arerer.getY(), &arerer);

    Organism jeanjean(world);
    jeanjean.setIcon('n');
    world->addOrganism(jeanjean.getX(), jeanjean.getY(), &jeanjean);

    Organism kevin(world);
    kevin.setIcon('w');
    world->addOrganism(kevin.getX(), kevin.getY(), &kevin);


    for(int step = 0; step < tfinal; step ++)
    {
        _sleep(40);
        system("cls");

        world->getListOrganisms(listOrganisms);
        for(int i =0; i < listOrganisms.size(); i++)
        {
            listOrganisms[i]->walk();
            //if(step%50 == 25)
            //{
                if (rand() % 1000 < 15)
                    listOrganisms[i]->reproduce();

                if (rand() % 1000 < 10)
                {
                    listOrganisms[i]->die();
                }
            //}
        }


        cout<<"Step : "<<step<<endl;
        cout<<"Organims : "<<listOrganisms.size()<<endl;
        world->displayGrid();
    }

    //destruction des ptrs
    delete obstacle;
    obstacle = 0;
    delete world;
    world = 0;
    return 0;*/
