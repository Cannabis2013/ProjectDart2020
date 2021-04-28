#ifndef SCOREBUILDER_H
#define SCOREBUILDER_H

#include "IScoreBuilder.h"
#include "idartspointinput.h"
#include "iscoreparameter.h"
#include <quuid.h>
#include "scorebuildercontext.h"
#include "dartspointinput.h"

class DartsScoreBuilder : public IScoreBuilder<IModel<QUuid>,SBC::DartsPointParameters,SBC::ModelOptions>
{
public:
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket = 0x4
    };
    // IScoreBuilder interface
    virtual IDartsPointInput<QUuid> *buildDartsPoint(const SBC::DartsPointParameters &p,
                                           const SBC::ModelOptions &options) override
    {
        auto params = dynamic_cast<const SBC::DartsPointParameters&>(p);
        auto t = DartsPointInput::createInstance()
                ->setRoundIndex(params.roundIndex)
                ->setSetIndex(params.setIndex)
                ->setAttempt(params.attempt)
                ->setPointValue(params.pointValue)
                ->setScoreValue(params.scoreValue)
                ->setAccumulatedScore(params.accumulatedScoreValue)
                ->setPlayer(params.playerId)
                ->setParent(params.tournament)
                ->setModKeyCode(params.keyCode)
                ->setDisplayHint(params.hint);
        if(options.generateUniqueId)
            t->setId(QUuid::createUuid());
        else
            t->setId(params.id);
        return t;
    }
private:
};
#endif // SCOREBUILDER_H
