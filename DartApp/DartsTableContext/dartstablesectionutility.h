#ifndef DARTSTABLESECTIONUTILITY_H
#define DARTSTABLESECTIONUTILITY_H

#include "idartstablesectionutility.h"

class DartsTableSectionUtility : public IDartsTableSectionUtility
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
