#ifndef ABSTRACTDARTSINPUT_H
#define ABSTRACTDARTSINPUT_H
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
#include "DartsModelsContext/InputModels/dartsinputstats.h"

class AbstractDartsInput : public IPlayerInput, public DartsInputStats
{
public:
    virtual int modKeyCode() const = 0;
    virtual AbstractDartsInput* setModKeyCode(const int&) = 0;
    virtual int point() const = 0;
    virtual AbstractDartsInput* setPoint(const int&) = 0;
    virtual int score() const = 0;
    virtual AbstractDartsInput* setScore(const int&) = 0;
    virtual int remainingScore() const = 0;
    virtual AbstractDartsInput *setRemainingScore(const int &score) = 0;
    virtual int roundIndex() const = 0;
    virtual AbstractDartsInput* setRoundIndex(const int &index) = 0;
    virtual int setIndex() const = 0;
    virtual AbstractDartsInput* setSetIndex(const int &index) = 0;
    virtual int attempt() const = 0;
    virtual AbstractDartsInput* setAttempt(const int &) = 0;
    virtual bool inGame() const = 0;
    virtual AbstractDartsInput *setInGame(const bool &value) = 0;
    virtual bool approved() const = 0;
    virtual AbstractDartsInput *setApproved(const bool &val) = 0;
};
#endif // ABSTRACTDARTSINPUT_H
