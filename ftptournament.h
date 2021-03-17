#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <quuid.h>
#include <qstring.h>
#include <qlist.h>
#include "iftptournament.h"

class FTPTournament : public IFTPTournament<QUuid,QVector<QUuid>,QString>
{
    // IModel interface
public:
    QUuid id() const override
    {
        return _id;
    }
    FTPTournament* setId(const QUuid &val) override
    {
        _id = val;
        return this;
    }
    int type() const override
    {
        return _modelType;
    }
    FTPTournament* setType(const int &val) override
    {
        _modelType = val;
        return this;
    }

    // ITournament interface
    QString title() const override
    {
        return _title;
    }
    FTPTournament* setTitle(const QString &string) override
    {
        _title = string;
        return this;
    }
    int attempts() const override
    {
        return _numberOfThrows;
    }
    FTPTournament* setAttempts(const int &val) override
    {
        _numberOfThrows = val;
        return this;
    }
    int gameMode() const override
    {
        return _gameMode;
    }
    FTPTournament* setGameMode(const int &val) override
    {
        _gameMode = val;
        return this;
    }
    int keyPoint() const override
    {
        return _keyPoint;
    }
    FTPTournament* setKeyPoint(const int &val) override
    {
        _keyPoint = val;
        return this;
    }
    bool status() const override
    {
        return _status;
    }
    FTPTournament* setStatus(const bool &status) override
    {
        _status = status;
        return this;
    }
    QUuid winnerId() const override
    {
        return _winner;
    }
    IFTPTournament<QUuid,QVector<QUuid>,QString>* setWinner(const QUuid &val) override
    {
        _winner = val;
        return this;
    }

    QVector<QUuid> assignedPlayerIdentities() const override
    {
        return _assignedPlayerIdentities;
    }
    FTPTournament* setAssignedPlayerIdentities(const QVector<QUuid> &playerIdentities) override
    {
        _assignedPlayerIdentities = playerIdentities;
        return this;
    }
    FTPTournament* assignPlayerIdentity(const QUuid &identity) override
    {
        _assignedPlayerIdentities.append(identity);
        return this;
    }

    FTPTournament* setParent(const QUuid &) override{
        /*
         * No parent
         */
        return this;
    }

    QUuid parent() const override{
        return QUuid();
    }

    int terminalKeyCode() const override
    {
        return _terminateConditionKeyCode;
    }
    FTPTournament* setTerminalKeyCode(const int &keyCode) override
    {
        _terminateConditionKeyCode = keyCode;
        return this;
    }
    static FTPTournament * createInstance()
    {
        return new FTPTournament();
    }
    int displayHint() const override
    {
        return _modelDisplayHint;
    }

    FTPTournament* setDisplayHint(int modelDisplayHint) override
    {
        _modelDisplayHint = modelDisplayHint;
        return this;
    }
    int inputHint() const override
    {
        return _inputMode;
    }
    FTPTournament* setInputMode(const int &inputMode) override
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
    int _terminateConditionKeyCode;
    int _modelDisplayHint;
    int _inputMode;
    QUuid _id,_winner;
    QVector<QUuid> _assignedPlayerIdentities;
};

#endif // TOURNAMENT_H
