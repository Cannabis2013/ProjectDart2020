#ifndef DARTSINDEXBUILDER_H
#define DARTSINDEXBUILDER_H
#include "IndexesSLAs/idartsidxbuilder.h"
class QJsonObject;
class QByteArray;
class IDartsIndex;
class DartsIndexBuilder : public IDartsIdxBuilder<IDartsIndex,QByteArray>
{
public:
    virtual Index *create(const ByteArray &vals) const override;
};
#endif // DARTSIDXBUILDER_H
