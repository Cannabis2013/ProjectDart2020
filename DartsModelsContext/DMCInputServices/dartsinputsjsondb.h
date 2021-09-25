#ifndef DARTSINPUTSJSONDB_H
#define DARTSINPUTSJSONDB_H

#include "DartsModelsContext/DMCInputServices/dmcinputjsondb.h"
#include "createdartspointsfromjson.h"
#include "dartsdbcreatejsonfrominputs.h"
#include "FileOperationsContext/Services/writebytearray.h"
#include "FileOperationsContext/Services/readbytearray.h"

namespace DartsDbContext
{
    class DartsInputsJsonDb : public DMCInputJsonDb
    {
    public:
        DartsInputsJsonDb()
        {
            setCreateModelsFromJson(new CreateDartsPointsFromJson);
            setCreateJsonFromModels(new DartsDbCreatejsonFromInputs);
            setReadJsonFromFile(new ReadByteArray(_fileName));
            setWriteJsonToFile(new WriteByteArray(_fileName));
            fetchModels();
        }
    private:
        const QString _fileName = "DartsInputModels";
    };
}


#endif // DARTSPOINTDBSERVICE_H
