#ifndef INDEXESIO_H
#define INDEXESIO_H

#include <qstring.h>

class DartsIndex;

class IndexesIO
{
public:
        bool saveIndexes(const DartsIndex& indexes);
        DartsIndex loadIndexes() const;

private:
        const QString _filePath = "indexes.dat";
};

#endif // INDEXESIO_H
