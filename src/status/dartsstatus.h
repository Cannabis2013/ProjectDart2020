#ifndef DARTSSTATUS_H
#define DARTSSTATUS_H

#include "src/status/idartsstatus.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

class DartsStatus : public IDartsStatus {
public:
        DartsStatus(const QString& filename);

        void init() override;
        void initFromStorage() override;
        bool saveState() override;
        void setWinner(const QString& name) override;
        void running() override;
        bool isWinnerFound() const override;

private:
        enum Status {
                Running,
                Winner
        };

        Status _status = Running;
        QString _filename;
        QString _winnerName;
};

#endif // DARTSSTATUS_H
