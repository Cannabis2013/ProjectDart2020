#ifndef DARTSSCOREJSONDB_H
#define DARTSSCOREJSONDB_H

#include "dartsinputjsondb.h"
#include "createjsonfromdartsscoremodels.h"
#include "createdartsscoremodelsfromjson.h"
#include "writebytearray.h"
#include "readbytearray.h"

namespace DartsDbContext {
    class DartsScoreJsonDb : public DartsInputJsonDb
    {
    public:
        DartsScoreJsonDb()
        {
            setCreateJsonFromModels(new CreateJsonFromDartsScoreModels);
            setCreateModelsFromJson(new CreateDartsScoreModelsFromjson);
            setWriteJsonToFile(new WriteByteArray(_fileName));
            setReadJsonFromFile(new ReadByteArray(_fileName));
            fetchModels();
        }
    private:
        const QString _fileName = "DartsScoreModels";
    };
}

#endif // DARTSSSCOREJSONDB_H
