#ifndef ABSTRACTTOURNAMENT_H
#define ABSTRACTTOURNAMENT_H
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
class AbstractTournament : public ITournament
{
public:
    virtual QUuid id() const override
    {
        return _id;
    }
    virtual void setId(const QUuid &val) override
    {
        _id = val;
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
    int _status;
    int _gameMode;
};
#endif // ABSTRACTTOURNAMENT_H
