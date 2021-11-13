#ifndef ITOURNAMENT_H
#define ITOURNAMENT_H
#include "ModelsContext/ModelsSLAs/imodel.h"
#include <qvector.h>
#include <quuid.h>
class ITournament : public IModel<QUuid>
{
public:
    virtual QString title() const = 0;
    virtual ITournament* setTitle(const QString &string) = 0;
    virtual QVector<QUuid> assignedPlayerIds() const = 0;
    virtual ITournament* setAssignedPlayerIds(const QVector<QUuid> &playerIdentities) = 0;
    virtual int gameMode() const = 0;
    virtual ITournament* setGameMode(const int &val) = 0;
    virtual int status() const = 0;
    virtual ITournament* setStatus(const bool &active) = 0;
    virtual QUuid winnerId() const = 0;
    virtual ITournament* setWinnerId(const QUuid &val) = 0;
    virtual QString winnerName() const = 0;
    virtual ITournament *setWinnerName(const QString &name) = 0;
};
#endif // ITOURNAMENT_H
