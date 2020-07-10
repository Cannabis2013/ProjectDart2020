#ifndef MODELBUILDERC5OLLECTION_H
#define MODELBUILDERCOLLECTION_H

#include "modelbuildercontext.h"
#include "idatamodelbuilder.h"

#include "tournament.h"
#include "round.h"
#include "set.h"
#include "point.h"

typedef ITournament<QUuid,QList<QUuid>,QString> DefaultTournamentInterface;
typedef IRound<QUuid, QList<QUuid>> DefaultRoundInterface;
typedef ISet<QUuid,QList<QUuid>> DefaultSetInterface;
typedef IPoint<QUuid> DefaultPointInterface;

typedef IDataModelBuilder<DefaultTournamentInterface, TournamentParameters,ModelOptions> ITournamentBuilder;
typedef IDataModelBuilder<DefaultRoundInterface, RoundParameters,ModelOptions> IRoundBuilder;
typedef IDataModelBuilder<DefaultSetInterface, SetParameters,ModelOptions> ISetBuilder;
typedef IDataModelBuilder<DefaultPointInterface, PointParameters,ModelOptions> IPointBuilder;

namespace ModelBuilderContext
{
    class TournamentBuilder;
    enum ModelType {TournamentModel = 0x00,RoundModel = 0x02, SetModel = 0x04, PointModel = 0x06};
};

class TournamentBuilder : public ITournamentBuilder
{
public:
    DefaultTournamentInterface *buildModel(const TournamentParameters &args, const ModelOptions &options) override
    {
        auto model = new Tournament();
        if(!options.customUuid && options.generateUniqueId)
            model->setId(QUuid::createUuid());
        else if(!options.generateUniqueId)
            model->setId(args.id);
        auto title = args.title != "" ? args.title : options.defaultTitle + QString("[%1]").arg(options.tournamentsCount);
        auto gameMode = args.gameMode != -1 ? args.gameMode : options.defaultGameMode;
        auto status = options.initialStatus;
        auto legCount = args.numberOfLegs > 0 ? args.numberOfLegs : options.defaultLegCount;
        auto maxPlayers = args.maxPlayers > 0 ? args.maxPlayers : options.defaultMaxPlayerCount;
        auto keyPoint = args.keyPoint >= 0 ? args.keyPoint : options.defaultKeyPoint;
        auto playerIdentitties = args.playerIdentities;
        model->setType(ModelBuilderContext::TournamentModel);
        model->setTitle(title);
        model->setGameMode(gameMode);
        model->setStatus(status);
        model->setKeyPoint(keyPoint);
        model->setNumberOfLegs(legCount);
        model->setMaximumAllowedPlayers(maxPlayers);
        model->setAssignedPlayerIdentities(playerIdentitties);

        model->setType(ModelBuilderContext::TournamentModel);

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

        model->setType(ModelBuilderContext::RoundModel);
        model->setIndex(args.roundIndex);
        model->setTournament(args.tournamentId);

        model->setType(ModelBuilderContext::RoundModel);

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

        model->setType(ModelBuilderContext::SetModel);
        model->setIndex(args.index);
        model->setRound(args.roundId);

        return model;
    }
};

class PointBuilder : public IPointBuilder
{

    // IGenericDataModelBuilder interface
public:
    DefaultPointInterface *buildModel(const PointParameters &args, const ModelOptions &options) override
    {
        auto model = new Point();

        if(!options.customUuid && options.generateUniqueId)
            model->setId(QUuid::createUuid());
        else if(!options.generateUniqueId)
            model->setId(args.id);

        model->setType(ModelBuilderContext::PointModel);
        model->setSet(args.setId);
        model->setPoint(args.pointValue);
        model->setPlayer(args.playerId);
        model->setLegIndex(args.legIndex);
        return model;
    }
};

#endif // MODELBUILDERCOLLECTION_H
