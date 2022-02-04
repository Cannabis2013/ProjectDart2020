#ifndef DARTSSTATISTICS_H
#define DARTSSTATISTICS_H
#include <QtCore/qglobal.h>
#include "Routines/routineservices.h"
#include "SLAs/servicesprovider.h"
#include "SLAs/idartsstatistics.h"
#ifdef DARTSSTATISTICS_LIBRARY
#  define DARTSSTATISTICS_EXPORT Q_DECL_EXPORT
#else
#  define DARTSSTATISTICS_EXPORT Q_DECL_IMPORT
#endif
class DARTSSTATISTICS_EXPORT DartsStatistics : public IDartsStatistics,
                                               public ServicesProvider,
                                               public RoutineServices
{
public:
    void initPlayers(const ByteArray &data) override;
    void initInputs(const ByteArray &data) override;
    void reset() override;
    void clear() override;
    void update(const QString &name, const int &point, const int &score, const int &modCode) override;
    QByteArray createReport(const QString &name) const override;
    virtual bool takeInput(const QString &name) override;
};

#endif // DARTSSTATISTICS_H
