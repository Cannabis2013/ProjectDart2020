#include "indexesio.h"
#include "src/FileIO/filejsonio.h"

IndexesIO::IndexesIO(const QString& filePath)
{
        _filePath = filePath;
}

bool IndexesIO::saveIndexes(const DartsIndex& indexes)
{
        FileJsonIO jsonIO(_filePath);
        return jsonIO.write(indexes.toJson());
}

DartsIndex IndexesIO::loadIndexes() const
{
        FileJsonIO jsonIO (_filePath);
        return DartsIndex::fromJson(jsonIO.read());
}
