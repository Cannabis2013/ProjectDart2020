#ifndef TURNINFO_H
#define TURNINFO_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qstring.h>

class TurnInfo
{
public:
        TurnInfo()
        {}

        QString currentPlayer() const
        {
                return _currentPlayer;
        }

        QByteArray toJson(){
                QJsonObject jsonObj;
                jsonObj["currentPlayerName"] = _currentPlayer;
                jsonObj["type"] = "turnInfo";
                jsonObj["canUndo"] = _canUndo;
                jsonObj["canRedo"] = _canRedo;
                jsonObj["turnIndex"] = _turnIndex;
                jsonObj["average"] = _average;
                jsonObj["low"] = _low;
                jsonObj["high"] = _high;
                jsonObj["finish"] = _finish;
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

        void setCurrentPlayer(const QString& newCurrentPlayer)
        {
                _currentPlayer = newCurrentPlayer;
        }
        void setCanUndo(bool newCanUndo)
        {
                _canUndo = newCanUndo;
        }
        void setCanRedo(bool newCanRedo)
        {
                _canRedo = newCanRedo;
        }
        void setTurnIndex(int newTurnIndex)
        {
                _turnIndex = newTurnIndex;
        }
        void setLow(int newLow)
        {
                _low = newLow;
        }
        void setHigh(int newHigh)
        {
                _high = newHigh;
        }
        void setAverage(double newAverage)
        {
                _average = newAverage;
        }

        QString finish() const
        {
                return _finish;
        }
        void setFinish(const QString& newFinish)
        {
                _finish = newFinish;
        }

private:
        QString _currentPlayer, _finish;
        bool _canUndo, _canRedo;
        int _turnIndex, _low, _high;
        double _average;
};

#endif // TURNINFO_H
