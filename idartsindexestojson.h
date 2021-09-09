#ifndef ICREATEJSONFROMDARTSPOINTINDEXES_H
#define ICREATEJSONFROMDARTSPOINTINDEXES_H
#include "itojson.h"
#include "idartspointindexes.h"
class IDartsIndexesToJson : public IToJson<const IDartsPointIndexes*>
{
public:
    virtual QByteArray toJson(const IDartsPointIndexes* indexes) const override = 0;
};
#endif // ICREATEJSONFROMDARTSPOINTINDEXES_H
