#ifndef USERSCORESCONTROLLERINTERFACE_H
#define USERSCORESCONTROLLERINTERFACE_H

#include <quuid.h>
#include <qpair.h>
#include <qvector.h>

namespace DartsScoreMultiAttemptContext {
    template<typename TDartsScore>
    class IPlayerScoreService
    {
    public:
        virtual QUuid winnerId() const = 0;
        virtual IPlayerScoreService* setWinner(const QUuid& id) = 0;
        virtual QString winnerUserName() const = 0;

        virtual void addPlayerEntity(const QUuid&,const QString&) = 0;
        virtual int subtractPlayerScoreByModel(const TDartsScore*) = 0;
        virtual void subtractPlayerScoreByModels(const QVector<const TDartsScore*>&) = 0;
        virtual int addPlayerScore(const QUuid&, const int&) = 0;

        virtual int playerScoreByIndex(const int& index) const = 0;
        virtual int playerScoreByIndex(const QUuid&) const = 0;
        virtual void setPlayerScoreByIndex(const int &index, const int &input) = 0;
        virtual void setPlayerScoresByList(const QVector<int>& list) = 0;
        virtual void setPlayerScoreById(const QUuid &id, const int &input) = 0;

        virtual QString playerNameByIndex(const int &index) const = 0;
        virtual QString playerNameById(const QUuid& id) const = 0;
        virtual QVector<QString> playerNames() const = 0;
        virtual QUuid playerIdAtIndex(const int &index) const = 0;

        virtual int playersCount() const = 0;
        virtual int initialScore() const = 0;
        virtual int calculateAccumulatedScoreCandidate(const int& index, const int& score) const = 0;
        virtual void resetScores() = 0;
    };
}


#endif // USERSCORESCONTROLLERINTERFACE_H
