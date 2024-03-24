#ifndef IDARTSINPUTSUPDATER_H
#define IDARTSINPUTSUPDATER_H

#include "src/input/models/inputCandidate.h"

class IDartsInputsUpdater {
public:
        virtual void save(const QList<InputCandidate>& candidates) = 0;
        virtual void removeExcessInputs() = 0;
};

#endif // IDARTSINPUTSUPDATER_H
