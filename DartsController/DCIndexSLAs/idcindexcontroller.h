#ifndef INDEXCONTROLLERINTERFACE_H
#define INDEXCONTROLLERINTERFACE_H

#include "DartsController/DCIndexServices/dcindex.h"

class IDCIndexController
{
public:
    virtual void init(const DCIndex &index = DCIndex()) = 0;
    virtual DCIndex &index() = 0;
    virtual DCIndex &next(const int &playersCount) = 0;
    virtual DCIndex &undo(const int &playerCount) = 0;
    virtual DCIndex &redo(const int &playersCount) = 0;
};

#endif // INDEXCONTROLLERINTERFACE_H
