#ifndef DCCREATEFINISHES_H
#define DCCREATEFINISHES_H
#include "dartscreatefinishes.h"
#include "dartsboundaries.h"
#include "dartsfieldvalues.h"
#include "dartsdivisors.h"
#include "dartsterminaldivisor.h"
#include "dartsmodidentifiers.h"
#include "dartsdefaultattempts.h"
class DCCreateFinishes : public DartsCreateFinishes
{
public:
    static DCCreateFinishes *createInstance() {return new DCCreateFinishes();}
private:
    DCCreateFinishes();
};
#endif // DPCCONSTRUCTROW_H
