#ifndef IDARTSINDEXBUILDER_H
#define IDARTSINDEXBUILDER_H
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "ModelsContext/ModelsSLAs/imodel.h"
class IDartsIndexBuilder
{
public:
    virtual IDartsIndex *index() const = 0;
    virtual IDartsIndex *index(const QByteArray &json) const = 0;
    virtual QVector<IDartsIndex*> indexes(const QByteArray &json) const = 0;
    virtual IDartsIndex *reqIndex(const QByteArray &json) const = 0;
};

#endif // IDARTSINDEXBUILDER_H
