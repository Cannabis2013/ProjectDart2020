#ifndef DARTSTOURNAMENT_H
#define DARTSTOURNAMENT_H

#include <quuid.h>
#include <qstring.h>
#include <qlist.h>
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class DartsTournament : public AbstractDartsTournament
{
public:
    static DartsTournament * createInstance()
    {
        return new DartsTournament();
    }

    int keyPoint() const override
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
