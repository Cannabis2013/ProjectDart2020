#ifndef DARTSSCOREMULTIATTEMPINDEXES_H
#define DARTSSCOREMULTIATTEMPINDEXES_H

#include "idartsscorecontrollerindexes.h"
#include <qbytearray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsScoreControllerContext {
    class DartsMultiAttemptIndexes : public
            IDartsScoreControllerIndexes<QByteArray>
    {
    public:
        static DartsMultiAttemptIndexes* createInstance()
        {
            return new DartsMultiAttemptIndexes;
        }
        int totalTurns() const override
        {
            return _totalTurns;
        }
        int turnIndex() const override
        {
            return _turnIndex;
        }
        int roundIndex() const override
        {
            return _roundIndex;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        void setTotalTurns(int newTotalTurns)
        {
            _totalTurns = newTotalTurns;
        }

        void setTurnIndex(int newTurns)
        {
            _turnIndex = newTurns;
        }

        void setRoundIndex(int newRoundIndex)
        {
            _roundIndex = newRoundIndex;
        }

        void setSetIndex(int newSetIndex)
        {
            _setIndex = newSetIndex;
        }

        virtual JsonFormat toJson() const override
        {
            QJsonObject obj;
            obj["totalTurns"] = _totalTurns;
            obj["turnIndex"] = _turnIndex;
            obj["roundIndex"] = _roundIndex;
            obj["setIndex"] = setIndex();
            auto json = QJsonDocument(obj).toJson();
            return json;
        }
    private:
        int _totalTurns;
        int _turnIndex;
        int _roundIndex;
        int _setIndex;
    };
}

#endif // DARTSSCOREMULTIATTEMPINDEXES_H
