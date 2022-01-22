#ifndef DARTSSTATISTICS_H
#define DARTSSTATISTICS_H
#include <QtCore/qglobal.h>
#include "SLAs/IDartsStatistics.h"
#ifdef DARTSSTATISTICS_LIBRARY
#  define DARTSSTATISTICS_EXPORT Q_DECL_EXPORT
#else
#  define DARTSSTATISTICS_EXPORT Q_DECL_IMPORT
#endif
class DARTSSTATISTICS_EXPORT DartsStatistics : public IDartsStatistics
{
public:
    virtual void init(const QVector<Input*> &data) override;
};

#endif // DARTSSTATISTICS_H
