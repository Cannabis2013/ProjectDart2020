#ifndef ICREATEJSONFROMDARTSPOINTINDEXES_H
#define ICREATEJSONFROMDARTSPOINTINDEXES_H
#include "DartsModelsContext/DMCIndexesSLAs/idartsindexes.h"
#include <qbytearray.h>
class IDartsIndexesToJson
{
public:
    virtual QByteArray toJson(const IDartsIndexes* indexes) const = 0;
};
#endif // ICREATEJSONFROMDARTSPOINTINDEXES_H
