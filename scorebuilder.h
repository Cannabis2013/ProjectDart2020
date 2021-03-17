#ifndef SCOREBUILDER_H
#define SCOREBUILDER_H

#include "IScoreBuilder.h"
#include "iscoremodel.h"
#include "iscoreparameter.h"
#include <quuid.h>
#include "scorebuildercontext.h"
#include "firsttopostscore.h"

class ScoreBuilder : public IScoreBuilder<IScore<QUuid>,IScoreParameter,SBC::ModelOptions>
{
public:
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket = 0x4
    };
    // IScoreBuilder interface
    virtual IScore<QUuid> *buildFTPScoreModel(const IScoreParameter &p,
                                           const SBC::ModelOptions &options) override
    {
        auto params = dynamic_cast<const SBC::FTPScoreParameters&>(p);
        auto t = FirstToPostScore::createInstance()
                ->setRoundIndex(params.roundIndex)
                ->setSetIndex(params.setIndex)
                ->setAttempt(params.attempt)
                ->setPointValue(params.pointValue)
                ->setScoreValue(params.scoreValue)
                ->setPlayer(params.playerId)
                ->setParent(params.tournament)
                ->setKeyCode(params.keyCode)
                ->setDisplayHint(params.hint)
                ->setGameMode(params.gameMode);
        if(options.generateUniqueId)
            t->setId(QUuid::createUuid());
        else
            t->setId(params.id);
        return t;
    }
private:
};
#endif // SCOREBUILDER_H
