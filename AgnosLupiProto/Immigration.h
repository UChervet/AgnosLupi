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

    void runOneStepImmi();
    void runSimuImmi(bool stepByStep = false);
    void createGermeAlea();
    void createFixGerme();

protected:
    //std::vector <string> m_labels //pour après si je fais avec plus de population
    int m_startingRatio; //ratio between the two population from 0 to 100
    char m_iconA = 'X';
    char m_iconB = '#';
    char* m_labelA = "Atype";
    char* m_labelB = "Btype";
    int m_colorA = 12;
    int m_colorB = 13;
};

#endif // IMMIGRATION_H_INCLUDED
