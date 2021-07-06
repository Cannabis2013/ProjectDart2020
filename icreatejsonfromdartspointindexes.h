#ifndef ICREATEJSONFROMDARTSPOINTINDEXES_H
#define ICREATEJSONFROMDARTSPOINTINDEXES_H

#include "icreatejsonfrom.h"
#include "idartspointindexes.h"
namespace DartsModelsContext {
    class ICreateJsonfromDartsPointIndexes : public ICreateJsonFrom<const IDartsPointIndexes*>
    {
    public:
        virtual QByteArray createJson(const IDartsPointIndexes* indexes) const override = 0;
    };
}

#endif // ICREATEJSONFROMDARTSPOINTINDEXES_H
