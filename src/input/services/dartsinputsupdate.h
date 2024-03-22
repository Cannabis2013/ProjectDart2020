#ifndef DARTSINPUTSUPDATE_H
#define DARTSINPUTSUPDATE_H

#include "idartsinputupdate.h"

class ServiceCollection;

class DartsInputsUpdate : public IDartsInputUpdate {
public:
        DartsInputsUpdate(ServiceCollection* services);
        void removeExcessInputs() override;
        void removeCurrentTurnInputs() override;
        void save(const QString& mod, const int& point) override;

private:
        ServiceCollection* _services;
};

#endif // DARTSINPUTSUPDATE_H
