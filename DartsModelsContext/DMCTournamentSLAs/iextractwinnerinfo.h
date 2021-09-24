#ifndef IEXTRACTWINNERINFO_H
#define IEXTRACTWINNERINFO_H

#include "quuid.h"
struct WinnerDataModel
{
    QUuid tournamentId;
    QUuid winnerId;
    QString winnerName;
};

class IExtractWinnerInfo
{
    // IGetDartsDataFromJson interface
public:
    typedef WinnerDataModel DataModel;
    virtual DataModel createWinnerDataModel(const QByteArray &json) const = 0;
};

#endif // IDEFAULTPLAYERJSONEXTRACTOR_H
