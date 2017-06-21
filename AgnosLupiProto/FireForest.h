#ifndef FIREFOREST_H_INCLUDED
#define FIREFOREST_H_INCLUDED

#include "Simulation.h"
#include "Organism.h"
#include "Grid2D.h"
#include "curses.h"

class FireForest : public Simulation
{
public:
    FireForest();
    FireForest(int w, int h, int nbStep, int densite, int probaPropa);

    void init();



protected:
    void initColor();
    void createForest();
    void startFire();
    int m_densite;
    double m_probaPropa;

    char* m_arbreLb = "arbre";
    char* m_feuLb = "feu";
    char* m_cendreLb = "arbre";

    //symbol color for the window console (obsolete)
//    char m_arbreChar = '0';
//    char m_feuChar = 'w';
//    char m_cendreChar = '#';
    int m_arbreColor = 2;
    int m_feuColor = 3;
    int m_cendreColor = 4;



    //symbol and color for curses
    int m_arbrePdColor = 2;
    int m_feuPdColor = 3;
    int m_cendrePdColor = 4;
    chtype m_arbreChar = ACS_PLMINUS;
    chtype m_feuChar = 'W';
    chtype m_cendreChar = '#';

    void runOneStep();
};


#endif // FIREFOREST_H_INCLUDED
