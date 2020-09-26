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
                                       DefaultRoundInterface,
                                       RoundParameters,
                                       DefaultSetInterface,
                                       SetParameters,
                                       DefaultScoreInterface,
                                       ScoreParameters,
                                       ModelOptions>
{
public:

    // ITournamentModelBuilder interface
public:
    DefaultTournamentInterface *buildTournamentModel(const TournamentParameters& p,
                                                     const ModelOptions& options) override
    {
        auto t = Tournament::createInstance()
                ->setTitle(p.title)
                ->setKeyPoint(p.keyPoint)
                ->setGameMode(p.gameMode)
                ->setNumberOfThrows(p.throws)
                ->setStatus(p.status)
                ->setAssignedPlayerIdentities(p.playerIdentities)
                ->setTerminateKeyCondition(p.winConditionKey)
                ->setType(DefaultModelBuilderContext::TournamentModel);
        if(options.generateUniqueId)
            t->setId(QUuid::createUuid());
        else
            t->setId(p.id);
        return t;

}
    DefaultRoundInterface *buildRoundModel(const RoundParameters& params, const ModelOptions &options) override
    {
        auto t = Round::createInstance()
                ->setIndex(params.roundIndex)
                ->setType(DefaultModelBuilderContext::RoundModel)
                ->setParent(params.tournamentId);
        if(options.generateUniqueId)
            t->setId(QUuid::createUuid());
        return t;
    }
    DefaultSetInterface *buildSetModel(const SetParameters& params, const ModelOptions& options) override
    {
        auto t = Set::createInstance()
                ->setIndex(params.index)
                ->setParent(params.roundId)
                ->setType(DefaultModelBuilderContext::SetModel);
        if(options.generateUniqueId)
            t->setId(QUuid::createUuid());
        return t;
    }
    DefaultScoreInterface *buildScoreModel(const ScoreParameters& params, const ModelOptions& options) override
    {
        auto t = Score::createInstance()
                ->setThrowIndex(params.throwIndex)
                ->setPoint(params.pointValue)
                ->setScore(params.scoreValue)
                ->setPlayer(params.playerId)
                ->setParent(params.setId)
                ->setKeyCode(params.keyCode)
                ->setHint(params.hint);
        if(options.generateUniqueId)
            t->setId(QUuid::createUuid());
        return t;
    }
};


#endif // MODELBUILDERCOLLECTION_H
