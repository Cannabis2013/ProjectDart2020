#ifndef CREATEDARTSINPUTVALUES_H
#define CREATEDARTSINPUTVALUES_H
#include <qvector.h>
#include <quuid.h>
#include "InputSLAs/icreatemodelvalues.h"
#include "InputModels/diptvals.h"
#include "InputModelsSLAs/abstractdartsinput.h"
#include "ModelSLAs/imodel.h"
class CreateDartsInputValues : public ICreateModelValues<AbstractDartsInput,DIptVals>
{
public:
    virtual Container create(Model *model) const override
    {
        if(model != nullptr)
            return convert(model);
        return DIptVals();
    }
    virtual Containers create(const Models &models) const override
    {
        Containers cList;
        for (auto i = models.begin(); i != models.end(); ++i)
            cList << convert(*i);
        return cList;
    }
private:
    Container convert(Model *model) const
    {
        Container c;
        c.approved = model->approved();
        c.roundIndex = model->roundIndex();
        c.setIndex = model->setIndex();
        c.attempt = model->attempt();
        c.inGame = model->inGame();
        c.min = model->currentMinimum();
        c.mid = model->middleValue();
        c.max = model->currentMaximum();
        c.score = model->score();
        c.point = model->point();
        c.modKeyCode = model->modKeyCode();
        c.playerName = model->playerName();
        c.remainingScore = model->remainingScore();
        return c;
    }
};
#endif // CREATEDARTSINPUTVALUES_H
