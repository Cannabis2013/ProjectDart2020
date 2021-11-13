#ifndef INDEXCONTROLLERINTERFACE_H
#define INDEXCONTROLLERINTERFACE_H

#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"

class IDCIndexController
{
public:
    virtual void init(IDartsIndex *index = nullptr) = 0;
    virtual IDartsIndex *index() = 0;
    virtual IDartsIndex *next(const int &playersCount) = 0;
    virtual IDartsIndex *undo(const int &playerCount) = 0;
    virtual IDartsIndex *redo(const int &playersCount) = 0;
};

#endif // INDEXCONTROLLERINTERFACE_H
