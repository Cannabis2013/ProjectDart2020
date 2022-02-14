#include "Converters/idcjsontomodels.h"
#ifndef DCBYTEARRAYTOMODELS_H
#define DCBYTEARRAYTOMODELS_Hs
class QJsonObject;
class DCPlayer;
class DCConvertPlayers : public IDCJsonToModels<DCPlayer>
{
public:
    Models convert(const QByteArray &byteArray, JsonToModel *jsonToPlayer) const override;
};

#endif // DCBYTEARRAYTOMODELS_H
