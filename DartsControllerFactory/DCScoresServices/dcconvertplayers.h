#include "ModelsConverterSLAs/idcmodelsconverter.h"
#ifndef DCBYTEARRAYTOMODELS_H
#define DCBYTEARRAYTOMODELS_Hs
class QJsonObject;
class DCPlayer;
class DCConvertPlayers : public IDCModelsConverter<DCPlayer>
{
public:
    Models convert(const QByteArray &byteArray, ModelBuilder *builder) const override;
};

#endif // DCBYTEARRAYTOMODELS_H
