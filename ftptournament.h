#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <quuid.h>
#include <qstring.h>
#include <qlist.h>
#include "ftptournamentmodelinterface.h"

class FTPTournament : public FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString>
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
    FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString>* setTitle(const QString &string) override
    {
        _title = string;
        return this;
    }
    int attemps() const override
    {
        return _numberOfThrows;
    }
    FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString>* setNumberOfThrows(const int &val) override
    {
        _numberOfThrows = val;
        return this;
    }
    int gameMode() const override
    {
        return _gameMode;
    }
    FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString>* setGameMode(const int &val) override
    {
        _gameMode = val;
        return this;
    }
    int initialPoint() const override
    {
        return _keyPoint;
    }
    FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString>* setKeyPoint(const int &val) override
    {
        _keyPoint = val;
        return this;
    }
    bool status() const override
    {
        return _status;
    }
    FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString>* setStatus(const bool &status) override
    {
        _status = status;
        return this;
    }
    QUuid winnerId() const override
    {
        return _winner;
    }
    FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString>* setWinner(const QUuid &val) override
    {
        _winner = val;
        return this;
    }

    QVector<QUuid> assignedPlayerIdentities() const override
    {
        return _assignedPlayerIdentities;
    }
    FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString>*setAssignedPlayerIdentities(const QVector<QUuid> &playerIdentities) override
    {
        _assignedPlayerIdentities = playerIdentities;
        return this;
    }
    FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString>* assignPlayerIdentity(const QUuid &identity) override
    {
        _assignedPlayerIdentities.append(identity);
        return this;
    }

    FTPTournamentModelInterface* setParent(const QUuid &) override{
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
    FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString>* setTerminateKeyCondition(const int &keyCode) override
    {
        _terminateConditionKeyCode = keyCode;
        return this;
    }
    static FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString> * createInstance()
    {
        return new FTPTournament();
    }
    int displayHint() const override
    {
        return _modelDisplayHint;
    }

    FTPTournamentModelInterface* setModelTableViewHint(int modelDisplayHint) override
    {
        _modelDisplayHint = modelDisplayHint;
        return this;
    }
    int inputHint() const override
    {
        return _inputMode;
    }
    FTPTournamentModelInterface* setInputMode(const int &inputMode) override
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
