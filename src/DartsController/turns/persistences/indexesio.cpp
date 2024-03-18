#include "indexesio.h"
#include "src/DartsController/turns/models/dartsindex.h"
#include "src/FileIO/filejsonio.h"

bool IndexesIO::saveIndexes(const DartsIndex& indexes)
{
        FileJsonIO jsonIO(_filePath);
        return jsonIO.write(indexes.toJson());
}

DartsIndex IndexesIO::loadIndexes() const
{
        FileJsonIO jsonIO (_filePath);
        return DartsIndex(jsonIO.read());
}
