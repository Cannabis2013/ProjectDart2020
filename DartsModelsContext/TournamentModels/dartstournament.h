#ifndef DARTSTOURNAMENT_H
#define DARTSTOURNAMENT_H
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
class DartsTournament : public AbstractDartsTournament
{
public:
    static DartsTournament * createInstance()
    {
        return new DartsTournament();
    }
    int initialRemaining() const override
    {
        return _keyPoint;
    }
    DartsTournament* setKeyPoint(const int &val) override
    {
        _keyPoint = val;
        return this;
    }
    int inputHint() const override
    {
        return _inputHint;
    }
    DartsTournament* setInputMode(const int &inputMode) override
    {
        _inputHint = inputMode;
        return this;
    }
private:
    int _keyPoint;
    int _inputHint;
};
#endif // TOURNAMENT_H
