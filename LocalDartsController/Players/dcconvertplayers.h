#ifndef DCBYTEARRAYTOMODELS_H
#define DCBYTEARRAYTOMODELS_H

#include <DartsController/Converters/idcjsontomodels.h>

class QJsonObject;
struct DCPlayer;
class DCConvertPlayers : public IDCJsonToModels<DCPlayer>
{
public:
    Models convert(const QByteArray &byteArray, JsonToModel *jsonToPlayer) const override;
};

#endif // DCBYTEARRAYTOMODELS_H
