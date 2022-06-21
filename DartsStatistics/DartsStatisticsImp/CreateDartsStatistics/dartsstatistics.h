#ifndef DARTSSTATISTICS_H
#define DARTSSTATISTICS_H

#include <QtCore/qglobal.h>
#include <DartsStatistics/Contracts/SLAs/idartsstatistics.h>
#include <DartsStatistics/Contracts/SLAs/servicescontext.h>

class DartsStatistics : public IDartsStatistics, public ServicesContext
{
public:
    void addPlayer(const QString &name) override;
    void addSnapShot(const QString &name, const int &score, const int &modCode) override;
    void reset() override;
    void clear() override;
    QByteArray createReport(const QString &name) const override;
    virtual bool removeSnapShot(const QString &name) override;
};

#endif // DARTSSTATISTICS_H
