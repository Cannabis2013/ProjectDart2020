#include "TurnInfo.h"

QString TurnInfo::currentPlayer() const
{
        return _currentPlayer;
}

QByteArray TurnInfo::toJson()
{
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
        jsonObj["status"] = _status == IDartsStatus::Running ? "running" : "winner";
        auto jsonDoc = new QJsonDocument(jsonObj);
        return jsonDoc->toJson(QJsonDocument::Compact);
}

void TurnInfo::setCurrentPlayer(const QString& newCurrentPlayer)
{
        _currentPlayer = newCurrentPlayer;
}

void TurnInfo::setCanUndo(bool newCanUndo)
{
        _canUndo = newCanUndo;
}

void TurnInfo::setCanRedo(bool newCanRedo)
{
        _canRedo = newCanRedo;
}

void TurnInfo::setTurnIndex(int newTurnIndex)
{
        _turnIndex = newTurnIndex;
}

void TurnInfo::setLow(int newLow)
{
        _low = newLow;
}

void TurnInfo::setHigh(int newHigh)
{
        _high = newHigh;
}

void TurnInfo::setAverage(double newAverage)
{
        _average = newAverage;
}

QString TurnInfo::finish() const
{
        return _finish;
}

void TurnInfo::setFinish(const QString& newFinish)
{
        _finish = newFinish;
}

void TurnInfo::setStatus(IDartsStatus::Status status)
{
        _status = status;
}
