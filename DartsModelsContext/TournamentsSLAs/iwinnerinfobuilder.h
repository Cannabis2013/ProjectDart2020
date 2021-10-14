#ifndef IWINNERINFOBUILDER_H
#define IWINNERINFOBUILDER_H

#include "quuid.h"
struct WinnerDataModel
{
    QUuid tournamentId;
    QUuid winnerId;
    QString winnerName;
};

class IWinnerInfoBuilder
{
public:
    typedef WinnerDataModel DataModel;
    virtual DataModel create(const QByteArray &json) const = 0;
};

#endif // IDEFAULTPLAYERJSONEXTRACTOR_H
