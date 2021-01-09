#ifndef SCORECALCULATORINTERFACE_H
#define SCORECALCULATORINTERFACE_H

class ScoreCalculatorInterface{
public:
    virtual int calculateScore(const int &point, const int &keyCode) const= 0;
};

#endif // SCORECALCULATORINTERFACE_H
