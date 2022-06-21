#ifndef DARTSINDEXBUILDER_H
#define DARTSINDEXBUILDER_H

#include <DartsModelsContext/Contracts/Index/idartsindexbuilder.h>

class QJsonObject;
class QByteArray;
class IDartsIndex;

class DartsIndexBuilder : public IDartsIndexBuilder<IDartsIndex>
{
public:
    virtual Index *create(const ByteArray &vals) const override;
};
#endif // DARTSIDXBUILDER_H
