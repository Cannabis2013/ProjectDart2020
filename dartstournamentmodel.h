#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <quuid.h>
#include <qstring.h>
#include <qlist.h>
#include "idartstournament.h"

class DartsTournamentModel : public IDartsTournament
{
    // IModel interface
public:
    QUuid id() const override
    {
        return _id;
    }
    DartsTournamentModel* setId(const QUuid &val) override
    {
        _id = val;
        return this;
    }

    // ITournament interface
    QString title() const override
    {
        return _title;
    }
    DartsTournamentModel* setTitle(const QString &string) override
    {
        _title = string;
        return this;
    }
    int attempts() const override
    {
        return _numberOfThrows;
    }
    DartsTournamentModel* setAttempts(const int &val) override
    {
        _numberOfThrows = val;
        return this;
    }
    int gameMode() const override
    {
        return _gameMode;
    }
    DartsTournamentModel* setGameMode(const int &val) override
    {
        _gameMode = val;
        return this;
    }
    int keyPoint() const override
    {
        return _keyPoint;
    }
    DartsTournamentModel* setKeyPoint(const int &val) override
    {
        _keyPoint = val;
        return this;
    }
    int status() const override
    {
        return _status;
    }
    DartsTournamentModel* setStatus(const bool &status) override
    {
        _status = status;
        return this;
    }
    QUuid winnerId() const override
    {
        return _winner;
    }
    IDartsTournament* setWinnerId(const QUuid &val) override
    {
        _winner = val;
        return this;
    }

    QVector<QUuid> assignedPlayerIds() const override
    {
        return _assignedPlayerIdentities;
    }
    DartsTournamentModel* setAssignedPlayerIdentities(const QVector<QUuid> &playerIdentities) override
    {
        _assignedPlayerIdentities = playerIdentities;
        return this;
    }
    DartsTournamentModel* assignPlayerIdentity(const QUuid &identity) override
    {
        _assignedPlayerIdentities.append(identity);
        return this;
    }

    int terminalKeyCode() const override
    {
        return _terminalKeyCode;
    }
    DartsTournamentModel* setTerminalKeyCode(const int &keyCode) override
    {
        _terminalKeyCode = keyCode;
        return this;
    }
    static DartsTournamentModel * createInstance()
    {
        return new DartsTournamentModel();
    }
    int displayHint() const override
    {
        return _modelDisplayHint;
    }

    DartsTournamentModel* setDisplayHint(int modelDisplayHint) override
    {
        _modelDisplayHint = modelDisplayHint;
        return this;
    }
    int inputHint() const override
    {
        return _inputMode;
    }
    DartsTournamentModel* setInputMode(const int &inputMode) override
    {
        _inputMode = inputMode;
        return this;
    }

private:
    QString _title;
    int _numberOfThrows;
    int _gameMode;
    int _keyPoint;
    int _status;
    int _modelType;
    int _terminalKeyCode;
    int _modelDisplayHint;
    int _inputMode;
    QUuid _id,_winner;
    QVector<QUuid> _assignedPlayerIdentities;
};

#endif // TOURNAMENT_H
