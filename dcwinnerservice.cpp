#include "dcwinnerservice.h"

QUuid DCWinnerService::winnerId() const
{
    return _winnerId;
}

QString DCWinnerService::winnerName() const
{
    return _winnerName;
}

void *DCWinnerService::setWinner(const QUuid &id, const QString &name)
{
    _winnerId = id;
    _winnerName = name;
}

