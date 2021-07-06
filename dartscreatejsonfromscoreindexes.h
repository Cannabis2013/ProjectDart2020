#ifndef DARTSCREATEJSONFROMSCOREINDEXES_H
#define DARTSCREATEJSONFROMSCOREINDEXES_H

#include "idartscreatejsonfromscoreindexes.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class DartsCreateJsonFromScoreIndexes : public IDartsCreateJsonFromScoreIndexes
{
public:

    // IDartsCreateJsonFromScoreIndexes interface
public:
    virtual QByteArray createJson(const DartsModelsContext::IDartsScoreIndexes *indexes) const override;
};

#endif // DARTSCREATEJSONFROMSCOREINDEXES_H
