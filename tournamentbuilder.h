#ifndef MODELBUILDERCOLLECTION_H
#define MODELBUILDERCOLLECTION_H

#include "tournamentbuildercontext.h"
#include "itournamentbuilder.h"

#include "dartstournamentmodel.h"
#include "dartspointinput.h"

typedef ITournament<QUuid,QVector<QUuid>,QString> TournamentInterface;
typedef IDartsPointInput<QUuid> FTPScoreInterface;


namespace DefaultModelBuilderContext
{
    enum ModelType {TournamentModel = 0x01,ScoreModel = 0x02};
};

class TournamentBuilder :
        public ITournamentBuilder<TournamentInterface,
                                  ITournamentParameter,
                                  TBC::ModelOptions>
{
public:
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket = 0x4
    };
    // ITournamentModelBuilder interface
    TournamentInterface *buildFTPTournament(const ITournamentParameter& p,
                                            const TBC::ModelOptions& options) override
    {
        auto params = dynamic_cast<const TBC::FTPParameters&>(p);
        auto t = DartsTournamentModel::createInstance()
                ->setTitle(params.title)
                ->setKeyPoint(params.keyPoint)
                ->setGameMode(params.gameMode)
                ->setAttempts(params.attempts)
                ->setStatus(params.status)
                ->setAssignedPlayerIdentities(params.playerIdentities)
                ->setTerminalKeyCode(params.terminalKeyCode)
                ->setDisplayHint(params.displayHint)
                ->setInputMode(params.inputHint)
                ->setWinnerId(params.winner);
        if(options.generateUniqueId && !options.useProvidedId)
            t->setId(QUuid::createUuid());
        else
            t->setId(params.id);
        return t;
    }
    virtual TournamentInterface* editFTPTournament(const TournamentInterface* tournament,
                                                const ITournamentParameter& p,
                                                const TBC::ModelOptions &options) override
    {
        auto ftpTournament = dynamic_cast<const DartsTournamentModel*>(tournament);
        auto params = dynamic_cast<const TBC::FTPParameters&>(p);
        auto title = params.title != "" ? params.title = tournament->title() : ftpTournament->title();
        auto keyPoint = params.keyPoint != -1 ? params.keyPoint : ftpTournament->keyPoint();
        auto gameMode = params.gameMode != -1 ? params.gameMode : ftpTournament->gameMode();
        auto attempts = params.attempts != -1 ? params.attempts : ftpTournament->attempts();
        auto status = params.status != -1 ? params.status: ftpTournament->status();
        auto assignedPlayerIdentities = params.playerIdentities != QVector<QUuid>() ?
                    params.playerIdentities : ftpTournament->assignedPlayerIdentities();
        auto terminalKeyCode = params.terminalKeyCode != -1 ? params.terminalKeyCode : ftpTournament->terminalKeyCode();
        auto displayHint = params.displayHint != -1 ? params.displayHint : ftpTournament->displayHint();
        auto inputMode = params.inputHint != -1 ? params.inputHint : ftpTournament->inputHint();
        auto winnerId = options.useProvidedId ? params.winner : ftpTournament->winnerId();
        auto model = DartsTournamentModel::createInstance()
                ->setId(ftpTournament->id())
                ->setTitle(title)
                ->setKeyPoint(keyPoint)
                ->setGameMode(gameMode)
                ->setAttempts(attempts)
                ->setStatus(status)
                ->setAssignedPlayerIdentities(assignedPlayerIdentities)
                ->setTerminalKeyCode(terminalKeyCode)
                ->setDisplayHint(displayHint)
                ->setInputMode(inputMode)
                ->setWinnerId(winnerId);
        return model;
    }
};


#endif // MODELBUILDERCOLLECTION_H
