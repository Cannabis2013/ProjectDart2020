#ifndef IDARTSPOINTMODELSFILTERSERVICE_H
#define IDARTSPOINTMODELSFILTERSERVICE_H

#include <qvector.h>
#include "idartspointdb.h"

class IGetDartsPointByParameters
{
public:
    virtual const DartsModelsContext::IDartsPointInput* getModelByParameters(const IDartsPointDb*,
                                                         const QUuid&,
                                                         const QUuid&,
                                                         const int&,
                                                         const int&) const = 0;
};

#endif // IDARTSPOINTMODELSFILTERSERVICE_H
