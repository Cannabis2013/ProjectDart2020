#ifndef CREATEDARTSSTATISTICS_H
#define CREATEDARTSSTATISTICS_H

#include <QtCore/qglobal.h>
#include <DartsStatistics/Contracts/SLAs/idartsstatistics.h>

class  CreateDartsStatistics
{
public:
        IDartsStatistics *create() const;
};

#endif // DARTSSTATISTICSFACTORY_H
