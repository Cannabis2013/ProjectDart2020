#ifndef MODELBUILDERC5OLLECTION_H
#define MODELBUILDERCOLLECTION_H

#include "modelbuildercontext.h"
#include "igenericdatamodelbuilder.h"


#include "tournament.h"
#include "round.h"
#include "set.h"
#include "point.h"

typedef ITournament<QUuid,QList<QUuid>,QString> DefaultTournamentInterface;
typedef IRound<QUuid, QList<QUuid>> DefaultRoundInterface;
typedef ISet<QUuid,QList<QUuid>> DefaultSetInterface;
typedef IPoint<QUuid> DefaultPointInterface;

typedef IGenericDataModelBuilder<DefaultTournamentInterface, TournamentParameters,ModelOptions> ITournamentBuilder;
typedef IGenericDataModelBuilder<DefaultRoundInterface, RoundParameters,ModelOptions> IRoundBuilder;
typedef IGenericDataModelBuilder<DefaultSetInterface, SetParameters,ModelOptions> ISetBuilder;
typedef IGenericDataModelBuilder<DefaultPointInterface, PointParameters,ModelOptions> IPointBuilder;

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

        model->setType(ModelBuilderContext::TournamentModel);
        model->setTitle(args.title);
        model->setGameMode(args.gameMode);
        model->setStatus(args.status);
        model->setKeyPoint(args.keyPoint);
        model->setNumberOfLegs(args.numberOfLegs);
        model->setMaximumAllowedPlayers(args.maxPlayers);

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

        return model;
    }
};

#endif // MODELBUILDERCOLLECTION_H
