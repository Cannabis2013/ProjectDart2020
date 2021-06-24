#ifndef DARTSCONTROLLERINDEXES_H
#define DARTSCONTROLLERINDEXES_H

#include "idartspointcontrollerindexes.h"
#include "qbytearray.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsPointControllerContext
{
    class DartsControllerIndexes :
            public IDartsPointControllerIndexes<QByteArray>
    {
    public:
        static DartsControllerIndexes* createInstance()
        {
            return new DartsControllerIndexes();
        }
        int totalTurns() const override
        {
            return _totalTurns;
        }
        DartsControllerIndexes* setTotalTurns(const int& totalTurns)
        {
            _totalTurns = totalTurns;
            return this;
        }
        int turnIndex() const override
        {
            return _turnIndex;
        }
        DartsControllerIndexes* setTurnIndex(const int& turnIndex)
        {
            _turnIndex = turnIndex;
            return this;
        }
        int roundIndex() const override
        {
            return _roundIndex;
        }
        DartsControllerIndexes* setRoundIndex(const int& roundIndex)
        {
            _roundIndex = roundIndex;
            return this;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        DartsControllerIndexes* setSetIndex(const int& setIndex)
        {
            _setIndex = setIndex;
            return this;
        }
        int attemptIndex() const override
        {
            return _attemptIndex;
        }
        DartsControllerIndexes* setAttemptIndex(const int& attemptIndex)
        {
            _attemptIndex = attemptIndex;
            return this;
        }

        JsonFormat toJson() const override
        {
            QJsonObject obj;
            obj["totalTurns"] = _totalTurns;
            obj["turnIndex"] = _turnIndex;
            obj["roundIndex"] = _roundIndex;
            obj["setIndex"] = setIndex();
            obj["attempt"] = _attemptIndex;
            auto json = QJsonDocument(obj).toJson();
            return json;
        }
    private:
        DartsControllerIndexes(){}
        int _totalTurns;
        int _turnIndex;
        int _roundIndex;
        int _setIndex;
        int _attemptIndex;
    };
}

#endif // DARTSSINGLEATTEMPTINDEXES_H
