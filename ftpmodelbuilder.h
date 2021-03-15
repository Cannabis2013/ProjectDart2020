#ifndef MODELBUILDERCOLLECTION_H
#define MODELBUILDERCOLLECTION_H

#include "modelbuildercontext.h"
#include "itournamentmodelbuilder.h"

#include "ftptournament.h"
#include "firsttopostscore.h"

typedef FTPTournamentModelInterface<QUuid,QVector<QUuid>,QString> FTPInterface;
typedef IScore<QUuid> FTPScoreInterface;


namespace DefaultModelBuilderContext
{
    enum ModelType {TournamentModel = 0x00,RoundModel = 0x02, SetModel = 0x04, ScoreModel = 0x06};
};

class FTPModelBuilder :
        public ITournamentModelBuilder<FTPInterface,
                                       FTPParameters,
                                       FTPScoreInterface,
                                       FTPScoreParameters,
                                       ModelOptions>
{
public:
    // ITournamentModelBuilder interface
    FTPInterface *buildFTPTournament(const FTPParameters& params,
                                                     const ModelOptions& options) override
    {
        auto t = FTPTournament::createInstance()
                ->setTitle(params.title)
                ->setKeyPoint(params.initialPoint)
                ->setGameMode(params.gameMode)
                ->setNumberOfThrows(params.attempts)
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
    FTPScoreInterface *buildScoreModel(const FTPScoreParameters& params,
                                           const ModelOptions& options) override
    {
        auto t = FirstToPostScore::createInstance()
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
