#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"

class Tournament : public ITournament
{
public:
    virtual QUuid id() const override
    {
        return _id;
    }
    virtual ITournament *setId(const QUuid &val) override
    {
        _id = val;
        return this;
    }
    virtual QString title() const override
    {
        return _title;
    }
    virtual ITournament *setTitle(const QString &string) override
    {
        _title = string;
        return this;
    }
    virtual QVector<QUuid> assignedPlayerIds() const override
    {
        return _assignedPlayerIdentities;
    }
    virtual ITournament *setAssignedPlayerIdentities(const QVector<QUuid> &playerIdentities) override
    {
        _assignedPlayerIdentities = playerIdentities;
        return this;
    }
    virtual QVector<QString> assignedPlayerNames() const override
    {
        return _assignedPlayerNames;
    }
    virtual ITournament *setAssignedPlayerNames(const QVector<QString> &names) override
    {
        _assignedPlayerNames = names;
        return this;

    }
    virtual int gameMode() const override
    {
        return _gameMode;
    }
    virtual ITournament *setGameMode(const int &val) override
    {
        _gameMode = val;
        return this;
    }
    virtual int status() const override
    {
        return _status;
    }
    virtual ITournament *setStatus(const bool &active) override
    {
        _status = active;
        return this;
    }
    virtual QUuid winnerId() const override
    {
        return _winnerId;
    }
    virtual ITournament *setWinnerId(const QUuid &val) override
    {
        _winnerId = val;
        return this;
    }
    virtual QString winnerName() const override
    {
        return _winnerName;
    }
    virtual ITournament *setWinnerName(const QString &name) override
    {
        _winnerName = name;
        return this;
    }
private:
    QString _title;
    QUuid _id;
    QUuid _winnerId;
    QString _winnerName;
    QVector<QUuid> _assignedPlayerIdentities;
    QVector<QString> _assignedPlayerNames;
    int _status;
    int _gameMode;
};

#endif // TOURNAMENT_H
