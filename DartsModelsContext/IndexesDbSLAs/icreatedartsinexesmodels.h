#ifndef ICREATEDARTSINEXESMODELS_H
#define ICREATEDARTSINEXESMODELS_H

#include <quuid.h>
#include <qvector.h>
#include "idartsindexes.h"

class IDartsIndexesBuilder
{
public:
    virtual IDartsIndexes *buildIndexes(const QUuid &tournamentId) const = 0;
    virtual IDartsIndexes *buildIndexes(const QByteArray &json) const = 0;
    virtual QVector<IModel<QUuid>*> indexesModels(const QByteArray &json) const = 0;
};
#endif // ICREATEDARTSINEXESMODELS_H
