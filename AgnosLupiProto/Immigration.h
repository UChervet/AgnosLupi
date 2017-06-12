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

    void runOneStep();
    void createGermeAlea();

protected:
    //std::vector <string> m_labels //pour après si je fais avec plus de population
    int m_startingRatio; //ratio between the two population from 0 to 100
    char m_iconA;
    char m_iconB;
    std::string m_labelA;
    std::string m_lableB;
};

#endif // IMMIGRATION_H_INCLUDED
