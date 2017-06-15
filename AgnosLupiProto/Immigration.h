#ifndef IMMIGRATION_H_INCLUDED
#define IMMIGRATION_H_INCLUDED

#include "GameOlife.h"
#include <string>
#include <vector>

class Immigration : public GameOlife
{
public:
    Immigration(int w, int h, int tauxGerme, int nbStep, int startingRatio);

    void init();
    void initColor();
    void createGermeAlea();
    void createFixGerme();

protected:
    int m_startingRatio; //ratio between the two population from 0 to 100
    chtype m_iconA = ACS_LANTERN;
    chtype m_iconB = ACS_DIAMOND;
    char* m_labelA = "Atype";
    char* m_labelB = "Btype";
    int m_colorA = 2;
    int m_colorB = 3;

    void runOneStep();
};

#endif // IMMIGRATION_H_INCLUDED
