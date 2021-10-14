#ifndef DARTSTOURNAMENT_H
#define DARTSTOURNAMENT_H

#include <quuid.h>
#include <qstring.h>
#include <qlist.h>
#include "DartsModelsContext/TournamentsSLAs/abstractdartstournament.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace ModelsContext{
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

        int displayHint() const override
        {
            return _displayHint;
        }

        DartsTournament* setDisplayHint(int modelDisplayHint) override
        {
            _displayHint = modelDisplayHint;
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
        int _displayHint;
        int _inputHint;
    };
}
#endif // TOURNAMENT_H
