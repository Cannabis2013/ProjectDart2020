#ifndef DCCREATEFINISHES_H
#define DCCREATEFINISHES_H
#include "dartscreatefinishes.h"
class DCCreateFinishes : public DartsCreateFinishes
{
public:
    static DCCreateFinishes *createInstance() {return new DCCreateFinishes();}
private:
    DCCreateFinishes();
};
#endif // DPCCONSTRUCTROW_H
