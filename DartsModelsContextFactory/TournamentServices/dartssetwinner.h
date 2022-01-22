#ifndef DARTSSETWINNER_H
#define DARTSSETWINNER_H
#include "TournamentsSLAs/IDartsSetWinner.h"
template<typename T>
class IModel;
class QUuid;
class DartsSetWinner : public IDartsSetWinner<IModel<QUuid>>
{
public:;
    void setWinner(const QUuid &tournamentId, const Models &models,
                   const QString &name, const QUuid &playerId) const override;
private:
    Model *findModel(const QUuid &tournamentId, const Models &models) const;
};

#endif // DARTSSETWINNER_H
