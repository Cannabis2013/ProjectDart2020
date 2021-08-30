#ifndef IDCWINNERSERVICE_H
#define IDCWINNERSERVICE_H

#include <quuid.h>

class IDCWinnerService
{
public:
    virtual void *setWinner(const QUuid& id, const QString &name) = 0;
    virtual QUuid winnerId() const = 0;
    virtual QString winnerName() const = 0;
};
#endif // USERSCORESCONTROLLERINTERFACE_H
