#ifndef IDARTSCREATEMETA_H
#define IDARTSCREATEMETA_H
#include "DartsModelsContext/TournamentModels/dartsmetamodel.h"
class IDartsCreateMeta
{
public:
    virtual DartsMetaModel create(const QByteArray &json) const = 0;
    virtual DartsMetaModel create(const QUuid &tournament, const QUuid &player) const = 0;
};
#endif // IDARTSCREATEMETA_H
