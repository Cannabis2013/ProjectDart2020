#ifndef DARTSINPUTSUPDATER_H
#define DARTSINPUTSUPDATER_H

#include "idartsinputsupdater.h"
#include "src/input/models/inputCandidate.h"

class ServiceCollection;

class DartsInputsUpdater : public IDartsInputsUpdater {
public:
        DartsInputsUpdater(ServiceCollection* services);

        void save(const QList<InputCandidate>& candidates) override;
        void removeExcessInputs() override;

private:
        typedef QList<InputCandidate> Candidates;
        typedef QList<DartsInput> Inputs;
        Inputs toInputs(const Candidates& candidates);
        ServiceCollection* _services;
};

#endif // DARTSINPUTSUPDATER_H
