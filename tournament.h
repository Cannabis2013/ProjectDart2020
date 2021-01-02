#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <quuid.h>
#include <qstring.h>
#include <qlist.h>
#include "itournamentmodel.h"

class Tournament : public ITournament<QUuid,QList<QUuid>,QString>
{
    // IModel interface
public:
    QUuid id() const override
    {
        return _id;
    }
    Tournament* setId(const QUuid &val) override
    {
        _id = val;
        return this;
    }
    int type() const override
    {
        return _modelType;
    }
    Tournament* setType(const int &val) override
    {
        _modelType = val;
        return this;
    }

    // ITournament interface
    QString title() const override
    {
        return _title;
    }
    ITournament<QUuid,QList<QUuid>,QString>* setTitle(const QString &string) override
    {
        _title = string;
        return this;
    }
    int numberOfThrows() const override
    {
        return _numberOfThrows;
    }
    ITournament<QUuid,QList<QUuid>,QString>* setNumberOfThrows(const int &val) override
    {
        _numberOfThrows = val;
        return this;
    }
    int gameMode() const override
    {
        return _gameMode;
    }
    ITournament<QUuid,QList<QUuid>,QString>* setGameMode(const int &val) override
    {
        _gameMode = val;
        return this;
    }
    int keyPoint() const override
    {
        return _keyPoint;
    }
    ITournament<QUuid,QList<QUuid>,QString>* setKeyPoint(const int &val) override
    {
        _keyPoint = val;
        return this;
    }
    bool status() const override
    {
        return _status;
    }
    ITournament<QUuid,QList<QUuid>,QString>* setStatus(const bool &status) override
    {
        _status = status;
        return this;
    }
    QUuid winner() const override
    {
        return _winner;
    }
    ITournament<QUuid,QList<QUuid>,QString>* setWinner(const QUuid &val) override
    {
        _winner = val;
        return this;
    }

    QList<QUuid> assignedPlayerIdentities() const override
    {
        return _assignedPlayerIdentities;
    }
    ITournament<QUuid,QList<QUuid>,QString>*setAssignedPlayerIdentities(const QList<QUuid> &playerIdentities) override
    {
        _assignedPlayerIdentities = playerIdentities;
        return this;
    }
    ITournament<QUuid,QList<QUuid>,QString>* assignPlayerIdentity(const QUuid &identity) override
    {
        _assignedPlayerIdentities.append(identity);
        return this;
    }

    ITournament* setParent(const QUuid &) override{
        /*
         * No parent
         */
        return this;
    }

    QUuid parent() const override{
        return QUuid();
    }

    int terminateKeyCondition() const override
    {
        return _terminateConditionKeyCode;
    }
    ITournament<QUuid,QList<QUuid>,QString>* setTerminateKeyCondition(const int &keyCode) override
    {
        _terminateConditionKeyCode = keyCode;
        return this;
    }
    static ITournament<QUuid,QList<QUuid>,QString> * createInstance()
    {
        return new Tournament();
    }
    int modelDisplayHint() const override
    {
        return _modelDisplayHint;
    }

    ITournament* setModelDisplayHint(int modelDisplayHint) override
    {
        _modelDisplayHint = modelDisplayHint;
        return this;
    }
private:
    QString _title;
    int _numberOfThrows;
    int _gameMode;
    int _keyPoint;
    int _status;
    int _modelType;
    int _terminateConditionKeyCode;
    int _modelDisplayHint;
    QUuid _id,_winner;
    QList<QUuid> _assignedPlayerIdentities;
};


#endif // TOURNAMENT_H
