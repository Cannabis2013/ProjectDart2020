#ifndef MODELBUILDERCOLLECTION_H
#define MODELBUILDERCOLLECTION_H

#include "modelbuildercontext.h"
#include "itournamentmodelbuilder.h"

#include "tournament.h"
#include "round.h"
#include "set.h"
#include "score.h"

typedef ITournament<QUuid,QList<QUuid>,QString> DefaultTournamentInterface;
typedef IRound<QUuid, QList<QUuid>> DefaultRoundInterface;
typedef ISet<QUuid,QList<QUuid>> DefaultSetInterface;
typedef IScore<QUuid> DefaultScoreInterface;


namespace DefaultModelBuilderContext
{
    enum ModelType {TournamentModel = 0x00,RoundModel = 0x02, SetModel = 0x04, ScoreModel = 0x06};
};

class TournamentModelBuilder :
        public ITournamentModelBuilder<DefaultTournamentInterface,
                                       TournamentParameters,
                                       DefaultScoreInterface,
                                       ScoreParameters,
                                       ModelOptions>
{
public:

    // ITournamentModelBuilder interface
public:
    DefaultTournamentInterface *buildTournamentModel(const TournamentParameters& params,
                                                     const ModelOptions& options) override
    {
        auto t = Tournament::createInstance()
                ->setTitle(params.title)
                ->setKeyPoint(params.keyPoint)
                ->setGameMode(params.gameMode)
                ->setNumberOfThrows(params.throws)
                ->setStatus(params.status)
                ->setAssignedPlayerIdentities(params.playerIdentities)
                ->setTerminateKeyCondition(params.winConditionKey)
                ->setType(DefaultModelBuilderContext::TournamentModel)
                ->setModelTableViewHint(params.modelTableViewHint)
                ->setInputMode(params.inputMode)
                ->setWinner(params.winner);
        if(options.generateUniqueId)
            t->setId(QUuid::createUuid());
        else
            t->setId(params.id);
        return t;

    }
    DefaultScoreInterface *buildScoreModel(const ScoreParameters& params,
                                           const ModelOptions& options) override
    {
        auto t = Score::createInstance()
                ->setRoundIndex(params.roundIndex)
                ->setSetIndex(params.setIndex)
                ->setThrowIndex(params.throwIndex)
                ->setPoint(params.pointValue)
                ->setScore(params.scoreValue)
                ->setPlayer(params.playerId)
                ->setParent(params.tournament)
                ->setKeyCode(params.keyCode)
                ->setHint(params.hint);
        if(options.generateUniqueId)
            t->setId(QUuid::createUuid());
        else
            t->setId(params.id);
        return t;
    }
};


#endif // MODELBUILDERCOLLECTION_H
