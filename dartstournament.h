#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <quuid.h>
#include <qstring.h>
#include <qlist.h>
#include "idartstournament.h"

class DartsTournament : public IDartsTournament
{
    // IModel interface
public:
    QUuid id() const override
    {
        return _id;
    }
    DartsTournament* setId(const QUuid &val) override
    {
        _id = val;
        return this;
    }

    // ITournament interface
    QString title() const override
    {
        return _title;
    }
    DartsTournament* setTitle(const QString &string) override
    {
        _title = string;
        return this;
    }
    int attempts() const override
    {
        return _attempts;
    }
    DartsTournament* setAttempts(const int &val) override
    {
        _attempts = val;
        return this;
    }
    int gameMode() const override
    {
        return _gameMode;
    }
    DartsTournament* setGameMode(const int &val) override
    {
        _gameMode = val;
        return this;
    }
    int keyPoint() const override
    {
        return _keyPoint;
    }
    DartsTournament* setKeyPoint(const int &val) override
    {
        _keyPoint = val;
        return this;
    }
    int status() const override
    {
        return _status;
    }
    DartsTournament* setStatus(const bool &status) override
    {
        _status = status;
        return this;
    }
    QUuid winnerId() const override
    {
        return _winner;
    }
    DartsTournament* setWinnerId(const QUuid &val) override
    {
        _winner = val;
        return this;
    }

    QVector<QUuid> assignedPlayerIdentities() const override
    {
        return _assignedPlayerIdentities;
    }
    DartsTournament* setAssignedPlayerIdentities(const QVector<QUuid> &playerIdentities) override
    {
        _assignedPlayerIdentities = playerIdentities;
        return this;
    }
    DartsTournament* assignPlayerIdentity(const QUuid &identity) override
    {
        _assignedPlayerIdentities.append(identity);
        return this;
    }

    int terminalKeyCode() const override
    {
        return _terminalKeyCode;
    }
    DartsTournament* setTerminalKeyCode(const int &keyCode) override
    {
        _terminalKeyCode = keyCode;
        return this;
    }
    static DartsTournament * createInstance()
    {
        return new DartsTournament();
    }
    int displayHint() const override
    {
        return _modelDisplayHint;
    }

    DartsTournament* setDisplayHint(int modelDisplayHint) override
    {
        _modelDisplayHint = modelDisplayHint;
        return this;
    }
    int inputHint() const override
    {
        return _inputMode;
    }
    DartsTournament* setInputMode(const int &inputMode) override
    {
        _inputMode = inputMode;
        return this;
    }

private:
    QString _title;
    int _attempts;
    int _gameMode;
    int _keyPoint;
    int _status;
    int _terminalKeyCode;
    int _modelDisplayHint;
    int _inputMode;
    QUuid _id,_winner;
    QVector<QUuid> _assignedPlayerIdentities;
};

#endif // TOURNAMENT_H
