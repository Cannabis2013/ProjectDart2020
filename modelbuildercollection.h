#ifndef MODELBUILDERCOLLECTION_H
#define MODELBUILDERCOLLECTION_H

#include "modelbuildercontext.h"
#include "idatamodelbuilder.h"

#include "tournament.h"
#include "round.h"
#include "set.h"
#include "score.h"

typedef ITournament<QUuid,QList<QUuid>,QString> DefaultTournamentInterface;
typedef IRound<QUuid, QList<QUuid>> DefaultRoundInterface;
typedef ISet<QUuid,QList<QUuid>> DefaultSetInterface;
typedef IScore<QUuid> DefaultPointInterface;

typedef IDataModelBuilder<DefaultTournamentInterface, TournamentParameters,ModelOptions> ITournamentBuilder;
typedef IDataModelBuilder<DefaultRoundInterface, RoundParameters,ModelOptions> IRoundBuilder;
typedef IDataModelBuilder<DefaultSetInterface, SetParameters,ModelOptions> ISetBuilder;
typedef IDataModelBuilder<DefaultPointInterface, PointParameters,ModelOptions> IPointBuilder;

namespace DefaultModelBuilderContext
{
    class TournamentBuilder;
    enum ModelType {TournamentModel = 0x00,RoundModel = 0x02, SetModel = 0x04, ScoreModel = 0x06};
};

class TournamentModelBuilder : public ITournamentBuilder
{
public:
    DefaultTournamentInterface *buildModel(const TournamentParameters &args, const ModelOptions &options) override
    {
        auto model = new Tournament();
        if(!options.customUuid && options.generateUniqueId)
            model->setId(QUuid::createUuid());
        else if(!options.generateUniqueId)
            model->setId(args.id);
        auto title = args.title != "" ? args.title : args.defaultTitle + QString("[%1]").arg(args.tournamentsCount);
        auto gameMode = args.gameMode != -1 ? args.gameMode : args.defaultGameMode;
        auto status = args.initialStatus;
        auto legCount = args.throws > 0 ? args.throws : args.defaultLegCount;
        auto keyPoint = args.keyPoint >= 0 ? args.keyPoint : args.defaultKeyPoint;
        auto playerIdentitties = args.playerIdentities;
        auto winner = args.winner;
        model->setType(DefaultModelBuilderContext::TournamentModel);
        model->setTitle(title);
        model->setGameMode(gameMode);
        model->setStatus(status);
        model->setKeyPoint(keyPoint);
        model->setNumberOfThrows(legCount);
        model->setWinner(winner);
        model->setTerminateKeyCondition(args.winConditionKey);
        model->setAssignedPlayerIdentities(playerIdentitties);
        model->setType(DefaultModelBuilderContext::TournamentModel);
        return model;
    }
};

class RoundBuilder : public IRoundBuilder
{
public:
    DefaultRoundInterface *buildModel(const RoundParameters &args, const ModelOptions &options) override
    {
        auto model = new Round();
        if(!options.customUuid && options.generateUniqueId)
            model->setId(QUuid::createUuid());
        else if(!options.generateUniqueId)
            model->setId(args.id);
        model->setType(DefaultModelBuilderContext::RoundModel);
        model->setIndex(args.roundIndex);
        model->setParent(args.tournamentId);
        model->setType(DefaultModelBuilderContext::RoundModel);

        return model;
    }
};

class SetBuilder : public ISetBuilder
{
    // IGenericDataModelBuilder interface
public:
    DefaultSetInterface *buildModel(const SetParameters &args, const ModelOptions &options) override
    {
        auto model = new Set();

        if(!options.customUuid && options.generateUniqueId)
            model->setId(QUuid::createUuid());
        else if(!options.generateUniqueId)
            model->setId(args.id);

        model->setIndex(args.index);
        model->setParent(args.roundId);
        model->setType(DefaultModelBuilderContext::SetModel);

        return model;
    }
};

class PointBuilder : public IPointBuilder
{

    // IGenericDataModelBuilder interface
public:
    DefaultPointInterface *buildModel(const PointParameters &args, const ModelOptions &options) override
    {
        auto model = new Score();
        if(!options.customUuid && options.generateUniqueId)
            model->setId(QUuid::createUuid());
        else if(!options.generateUniqueId)
            model->setId(args.id);
        model->setType(DefaultModelBuilderContext::ScoreModel);
        model->setParent(args.setId);
        model->setPoint(args.pointValue);
        model->setPlayer(args.playerId);
        model->setLegIndex(args.throwIndex);
        model->setHint(options.modelHint);
        model->setScore(args.scoreValue);
        return model;
    }
};

#endif // MODELBUILDERCOLLECTION_H
