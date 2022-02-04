#ifndef CREATEDARTSSTATISTICS_H
#define CREATEDARTSSTATISTICS_H
#include <QtCore/qglobal.h>
class IDartsStatistics;
#if defined(DARTSSTATISTICSFACTORY_LIBRARY)
#  define DARTSSTATISTICSFACTORY_EXPORT Q_DECL_EXPORT
#else
#  define DARTSSTATISTICSFACTORY_EXPORT Q_DECL_IMPORT
#endif
class DARTSSTATISTICSFACTORY_EXPORT CreateDartsStatistics
{
public:
    IDartsStatistics *create() const;
private:

};

#endif // DARTSSTATISTICSFACTORY_H
