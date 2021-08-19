#ifndef DARTSPMCSECTIONUTILITY_H
#define DARTSPMCSECTIONUTILITY_H

#include "idartstablesectionutility.h"

class DartsPMCSectionUtility : public IDartsTableSectionUtility
{
public:
    virtual bool isSectionEmpty(const int &column, const Rows &data) const override
    {
        for (auto pairsRow : qAsConst(data)) {
            auto pair = pairsRow.at(column);
            auto point = pair.first;
            if(point != -1)
                return false;
        }
        return true;
    }
};

#endif // DARTSTABLESECTIONUTILITY_H