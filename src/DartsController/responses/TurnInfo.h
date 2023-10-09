#ifndef TURNINFO_H
#define TURNINFO_H

#include "src/DartsController/status/IDartsStatus.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qstring.h>

class TurnInfo
{
public:
        QString currentPlayer() const;
        QByteArray toJson();

        void setCurrentPlayer(const QString& newCurrentPlayer);
        void setCanUndo(bool newCanUndo);
        void setCanRedo(bool newCanRedo);
        void setTurnIndex(int newTurnIndex);
        void setLow(int newLow);
        void setHigh(int newHigh);
        void setAverage(double newAverage);

        QString finish() const;
        void setFinish(const QString& newFinish);

        void setStatus(IDartsStatus::Status status);

private:
        QString _currentPlayer, _finish;
        IDartsStatus::Status _status;
        bool _canUndo, _canRedo;
        int _turnIndex, _low, _high;
        double _average;
};

#endif // TURNINFO_H
