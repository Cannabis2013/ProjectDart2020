#ifndef DARTSSCOREMULTIATTEMPINDEXES_H
#define DARTSSCOREMULTIATTEMPINDEXES_H

#include "idscindexes.h"
#include <qbytearray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
// Darts Multiple Attempts(DMA) indexes
namespace DSCContext {
    class DMAIndexes : public IDSCIndexes
    {
    public:
        static DMAIndexes *createInstance()
        {
            return new DMAIndexes;
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

        virtual QByteArray toJson() const override
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
