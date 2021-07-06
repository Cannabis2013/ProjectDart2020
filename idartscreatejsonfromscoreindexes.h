#ifndef IDARTSCREATEJSONFROMSCOREINDEXES_H
#define IDARTSCREATEJSONFROMSCOREINDEXES_H

#include "idartsscoreindexes.h"
#include <qbytearray.h>
#include "icreatejsonfrom.h"

class IDartsCreateJsonFromScoreIndexes : public ICreateJsonFrom<const DartsModelsContext::IDartsScoreIndexes*>
{
public:
    virtual QByteArray createJson(const DartsModelsContext::IDartsScoreIndexes *indexes) const override = 0;
};

#endif // IDARTSCREATEJSONFROMSCOREINDEXES_H
