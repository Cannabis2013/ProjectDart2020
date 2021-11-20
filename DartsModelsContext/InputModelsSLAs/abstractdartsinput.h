#ifndef ABSTRACTDARTSINPUT_H
#define ABSTRACTDARTSINPUT_H
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
#include "DartsModelsContext/InputModels/dartsinputstats.h"
class AbstractDartsInput : public IPlayerInput, public DartsInputStats
{
public:
    virtual int modKeyCode() const = 0;
    virtual void setModKeyCode(const int&) = 0;
    virtual int point() const = 0;
    virtual void setPoint(const int&) = 0;
    virtual int score() const = 0;
    virtual void setScore(const int&) = 0;
    virtual int remainingScore() const = 0;
    virtual void setRemainingScore(const int &score) = 0;
    virtual int roundIndex() const = 0;
    virtual void setRoundIndex(const int &index) = 0;
    virtual int setIndex() const = 0;
    virtual void setSetIndex(const int &index) = 0;
    virtual int attempt() const = 0;
    virtual void setAttempt(const int &) = 0;
    virtual bool inGame() const = 0;
    virtual void setInGame(const bool &value) = 0;
    virtual bool approved() const = 0;
    virtual void setApproved(const bool &val) = 0;
};
#endif // ABSTRACTDARTSINPUT_H
