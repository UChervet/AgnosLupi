#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "Grid2D.h"
#include "Organism.h"
#include <time.h>
#include <string>
#include <vector>

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
    //INIT
    srand(time(NULL)); // initialisation de rand
    int tfinal = 500; //time step max
    Grid2D* world = new Grid2D(15,15);
    vector <Organism *> listOrganisms;

    //creation of the obstacle object
    Organism* obstacle = new Organism(0, 0, world);
    obstacle->setLabel("obstacle");
    obstacle->setIcon('@');
    world->setBorders(obstacle);
    /*world->addRectangleObst(obstacle,2,2,4,8);
    world->addRectangleObst(obstacle,2,10,4,12);
    world->addRectangleObst(obstacle,6,2,8,4);
    world->addRectangleObst(obstacle,6,6,8,12);
    world->addRectangleObst(obstacle,12,6,12,12);
    world->addRectangleObst(obstacle,10,10,12,10);
    world->addRectangleObst(obstacle,10,4,14,4);*/

    //creation et placement organisms
    Organism toto(3,10, world);
    toto.setIcon('m');
    world->addOrganism(toto.getX(), toto.getY(), &toto);

    Organism jeanjean(8, 13, world);
    jeanjean.setIcon('n');
    world->addOrganism(jeanjean.getX(), jeanjean.getY(), &jeanjean);

    Organism kevin(10, 2, world);
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
            if(step%50 == 25)
            {
                listOrganisms[i]->reproduce();
                if (rand() % 100 < 20)
                {
                    listOrganisms[i]->die();
                }
            }
        }

        world->displayGrid();
        cout<<"Step : "<<step<<endl;
        cout<<"Organims : "<<listOrganisms.size()<<endl;
    }

    //destruction des ptrs
    delete obstacle;
    obstacle = 0;
    delete world;
    world = 0;
    return 0;
}




/*//INIT
    srand(time(NULL));
    int tfinal = 500; //time step max
    Grid2D* world = new Grid2D(15,15);

    //creation of the obstacle object
	Organism* obstacle = new Organism(0, 0, world);
	obstacle->setLabel("obstacle");
	world->setBorders(obstacle);

    //creation et placement organisms
    Organism toto(7, 7, world);
    world->addOrganism(toto.getX(), toto.getY(), &toto);
    //Organism jeanjean(11, 11, world);
    //world->addOrganism(jeanjean.getX(), jeanjean.getY(), &jeanjean);
    //world->displayGrid();
    for(int step = 0; step < tfinal;step ++)
    {
        _sleep(50);
        system("cls");
        //jeanjean.walk();
        toto.walk();
        world->displayGrid();
    }

    //world->displayGrid();


    //destruction des ptrs
    delete obstacle;
    obstacle = 0;
    delete world;
    world = 0;
    return 0;*/
