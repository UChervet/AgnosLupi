#ifndef FIREFOREST_H_INCLUDED
#define FIREFOREST_H_INCLUDED

#include "Simulation.h"
#include "Organism.h"
#include "Grid2D.h"

class FireForest : public Simulation
{
public:
    FireForest();
    FireForest(int w, int h, int nbStep, int densite, int probaPropa);

    void init();
    void createForest();
    void startFire();


protected:
    int m_densite;
    double m_probaPropa;

    char m_arbreChar = '0';
    char m_feuChar = 'w';
    char m_cendreChar = '#';

    char* m_arbreLb = "arbre";
    char* m_feuLb = "feu";
    char* m_cendreLb = "arbre";

    int m_arbreColor = 2;
    int m_feuColor = 12;
    int m_cendreColor = 8;

    void runOneStep();
};


#endif // FIREFOREST_H_INCLUDED
