#ifndef DARTSIDXBUILDER_H
#define DARTSIDXBUILDER_H
#include "IndexesSLAs/idartsidxbuilder.h"
struct TnmVals;
class IDartsIndex;
class DartsIdxBuilder : public IDartsIdxBuilder<IDartsIndex,TnmVals>
{
public:
    virtual Index *create(const Functor &vals) const override;
};
#endif // DARTSIDXBUILDER_H
