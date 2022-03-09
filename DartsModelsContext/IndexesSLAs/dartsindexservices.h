#ifndef DARTSINDEXSERVICES_H
#define DARTSINDEXSERVICES_H

#include "idartsidxbuilder.h"

class IDartsIndex;
class QUuid;

class DartsIndexServices
{
public:
    typedef IDartsIdxBuilder<IDartsIndex> IdxBuilder;
    IdxBuilder *indexBuilder() const {return _indexBuilder;}
    void setIndexBuilder(IdxBuilder *newIndexBuilder) {_indexBuilder = newIndexBuilder;}
private:
    IdxBuilder *_indexBuilder;
};
#endif // DARTSINDEXSERVICES_H
