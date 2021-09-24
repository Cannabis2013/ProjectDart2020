#ifndef ICREATEJSONFROMDARTSPOINTINDEXES_H
#define ICREATEJSONFROMDARTSPOINTINDEXES_H
#include "itojson.h"
#include "DartsModelsContext/DMCIndexesSLAs/idartsindexes.h"
class IDartsIndexesToJson : public IToJson<const IDartsIndexes*>
{
public:
    virtual QByteArray toJson(const IDartsIndexes* indexes) const override = 0;
};
#endif // ICREATEJSONFROMDARTSPOINTINDEXES_H
