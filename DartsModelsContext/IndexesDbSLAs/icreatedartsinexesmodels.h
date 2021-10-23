#ifndef ICREATEDARTSINEXESMODELS_H
#define ICREATEDARTSINEXESMODELS_H

#include <quuid.h>
#include <qvector.h>
#include "idartsindex.h"

class IDartsIndexesBuilder
{
public:
    virtual IDartsIndex *index(const QUuid &tournamentId) const = 0;
    virtual IDartsIndex *index(const QByteArray &json) const = 0;
    virtual IDartsIndex *reqIndex(const QByteArray &json) const = 0;
    virtual QVector<IModel<QUuid>*> indexes(const QByteArray &json) const = 0;
};
#endif // ICREATEDARTSINEXESMODELS_H
