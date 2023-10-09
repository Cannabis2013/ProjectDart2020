#ifndef INDEXESIO_H
#define INDEXESIO_H

#include "src/DartsController/indexes/dartsindex.h"
#include <qstring.h>

class IndexesIO
{
public:
        IndexesIO(const QString &filePath);
        bool saveIndexes(const DartsIndex &indexes);
        DartsIndex loadIndexes() const;

private:
        QString _filePath;
};

#endif // INDEXESIO_H
