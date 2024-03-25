#ifndef DARTSINDEXREPORT_H
#define DARTSINDEXREPORT_H

#include "iindexreport.h"

class ServiceCollection;

class DartsIndexReport : public IIndexReport {
public:
        DartsIndexReport(ServiceCollection* services);

        QByteArray report() const override;

private:
        ServiceCollection* const _services;
};

#endif // DARTSINDEXREPORT_H
