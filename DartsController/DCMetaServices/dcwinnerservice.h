#ifndef DCWINNERSERVICE_H
#define DCWINNERSERVICE_H

#include "DartsController/DCMetaSLAs/idcwinnerservice.h"
#define INCONSISTENCY_EXCEPTION_MESSAGE "User inconsistency!"

class DCWinnerService : public IDCWinnerService
{
public:
    QUuid winnerId() const override;
    QString winnerName() const override;
    void setWinner(const QUuid &id, const QString &name) override;
private:
    QUuid _winnerId;
    QString _winnerName;
};
#endif
