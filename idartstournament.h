#ifndef FTPTOURNAMENTMODELINTERFACE_H
#define FTPTOURNAMENTMODELINTERFACE_H

#include "itournament.h"
#include <qvector.h>
#include <quuid.h>
#include <QString>

class IDartsTournament : public ITournament
{
public:
    virtual IDartsTournament* setTitle(const QString &string) = 0;
    virtual int attempts() const = 0;

    virtual IDartsTournament* setAttempts(const int &val) = 0;

    virtual IDartsTournament* setAssignedPlayerIdentities(const QVector<QUuid> &playerIdentities) = 0;

    virtual int keyPoint() const = 0;
    virtual IDartsTournament* setKeyPoint(const int &val) = 0;

    virtual int terminalKeyCode() const = 0;
    virtual IDartsTournament* setTerminalKeyCode(const int &keyCode) = 0;

    virtual int displayHint() const = 0;
    virtual IDartsTournament* setDisplayHint(int modelDisplayHint) = 0;

    virtual int inputHint() const = 0;
    virtual IDartsTournament* setInputMode(const int &inputMode) = 0;
};

#endif // FTPTOURNAMENTMODELINTERFACE_H
