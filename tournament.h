#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "gamemodelscontext.h"

#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

class Tournament : public ITournament<QUuid,QList<QUuid>,QString>
{
    // IModel interface
public:
    QUuid id() const override
    {
        return _id;
    }
    void setId(const QUuid &val) override
    {
        _id = val;
    }
    int type() const override
    {
        return _modelType;
    }
    void setType(const int &val) override
    {
        _modelType = val;
    }

    // ITournament interface
    QString title() const override
    {
        return _title;
    }
    void setTitle(const QString &string) override
    {
        _title = string;
    }
    int numberOfThrows() const override
    {
        return _numberOfThrows;
    }
    void setNumberOfThrows(const int &val) override
    {
        _numberOfThrows = val;
    }
    int gameMode() const override
    {
        return _gameMode;
    }
    void setGameMode(const int &val) override
    {
        _gameMode = val;
    }
    int keyPoint() const override
    {
        return _keyPoint;
    }
    void setKeyPoint(const int &val) override
    {
        _keyPoint = val;
    }
    bool status() const override
    {
        return _status;
    }
    void setStatus(const bool &status) override
    {
        _status = status;
    }
    QUuid winner() const override
    {
        return _winner;
    }
    void setWinner(const QUuid &val) override
    {
        _winner = val;
    }

    QList<QUuid> assignedPlayerIdentities() const override
    {
        return _assignedPlayerIdentities;
    }
    void setAssignedPlayerIdentities(const QList<QUuid> &playerIdentities) override
    {
        _assignedPlayerIdentities = playerIdentities;
    }
    void assignPlayerIdentity(const QUuid &identity) override
    {
        _assignedPlayerIdentities.append(identity);
    }

    void setParent(const QUuid &) override{

    }

    QUuid parent() const override{
        return QUuid();
    }

private:
    QString _title;

    int _numberOfThrows;
    int _gameMode;
    int _keyPoint;
    int _status;
    int _modelType;

    QUuid _id,_winner;
    QList<QUuid> _assignedPlayerIdentities;
};


#endif // TOURNAMENT_H
