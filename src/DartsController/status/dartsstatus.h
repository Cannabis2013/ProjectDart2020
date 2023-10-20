#ifndef DARTSSTATUS_H
#define DARTSSTATUS_H

#include "src/DartsController/status/IDartsStatus.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#define _FILE "status.dat"

class DartsStatus : public IDartsStatus {
public:
        void init() override;

        void initFromFile() override;
        bool saveState() override;
        void winnerFound() override;
        void running() override;
        bool isWinnerFound() const override;

private:
        enum Status {
                Running,
                Winner
        };

        Status _status = Running;
};

#endif // DARTSSTATUS_H
