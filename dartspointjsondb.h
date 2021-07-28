#ifndef DARTSPOINTJSONDB_H
#define DARTSPOINTJSONDB_H

#include "dartsinputjsondb.h"
#include "createdartspointsfromjson.h"
#include "dartsdbcreatejsonfrompoints.h"
#include "writebytearray.h"
#include "readbytearray.h"

namespace DartsDbContext
{
    class DartsPointJsonDb : public DartsInputJsonDb
    {
    public:
        DartsPointJsonDb()
        {
            setCreateModelsFromJson(new CreateDartsPointsFromJson);
            setCreateJsonFromModels(new DartsDbCreatejsonFromPoints);
            setReadJsonFromFile(new ReadByteArray(_fileName));
            setWriteJsonToFile(new WriteByteArray(_fileName));
            fetchModels();
        }
    private:
        const QString _fileName = "DartsPointModels";
    };
}


#endif // DARTSPOINTDBSERVICE_H
