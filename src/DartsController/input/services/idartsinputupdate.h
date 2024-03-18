#ifndef IDARTSINPUTUPDATE_H
#define IDARTSINPUTUPDATE_H

#include "src/DartsController/input/models/Input.h"

class IDartsInputUpdate {
public:
        virtual void removeExcessInputs() = 0;
        virtual void removeCurrentTurnInputs() = 0;
        virtual void save(const QString& mod, const int& point) = 0;
};

#endif // IDARTSINPUTUPDATE_H
