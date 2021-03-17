#ifndef TOURNAMENTCONTEXTCOLLECTION_H
#define TOURNAMENTCONTEXTCOLLECTION_H

#include "itournamentbuilder.h"
#include "iftptournament.h"
#include "iscoremodel.h"
#include "tournamentbuildercontext.h"
#include "scorebuildercontext.h"
#include "IScoreBuilder.h"

namespace LMC {
    typedef ITournament<QUuid,QVector<QUuid>,QString> TournamentInterface;
    typedef IFTPTournament<QUuid,QVector<QUuid>,QString> FTPInterface;
    typedef IScore<QUuid> ScoreInterface;

    typedef ITournamentBuilder<TournamentInterface,
                               ITournamentParameter,
                               TBC::ModelOptions> ITournamentModelsBuilder;
    typedef IScoreBuilder<ScoreInterface,IScoreParameter,SBC::ModelOptions> IScoreModelsBuilder;
}

#endif // TOURNAMENTCONTEXTCOLLECTION_H
