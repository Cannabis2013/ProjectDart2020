#ifndef SCORECALCULATORINTERFACE_H
#define SCORECALCULATORINTERFACE_H

class IScoreCalculator{
public:
    virtual int calculateScoreFromDartsPoint(const int &point, const int &keyCode) const= 0;
};

#endif // SCORECALCULATORINTERFACE_H
