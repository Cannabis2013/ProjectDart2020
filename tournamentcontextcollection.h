#ifndef TOURNAMENTCONTEXTCOLLECTION_H
#define TOURNAMENTCONTEXTCOLLECTION_H

#include "itournamentbuilder.h"
#include "idartstournament.h"
#include "idartspointinput.h"
#include "tournamentbuildercontext.h"
#include "scorebuildercontext.h"
#include "IScoreBuilder.h"

namespace TCC {
    typedef ITournament<QUuid,QVector<QUuid>,QString> TournamentInterface;
    typedef IDartsTournament<QUuid,QVector<QUuid>,QString> FTPInterface;

    typedef ITournamentBuilder<TournamentInterface,
                               ITournamentParameter,
                               TBC::ModelOptions> ITournamentModelsBuilder;
    typedef IScoreBuilder<IModel<QUuid>,
                          SBC::DartsPointParameters,
                          SBC::ModelOptions> ScoreBuilderInterface;
}

#endif // TOURNAMENTCONTEXTCOLLECTION_H
