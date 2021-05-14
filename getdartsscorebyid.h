#ifndef GETDARTSSCOREBYID_H
#define GETDARTSSCOREBYID_H

#include "ibinaryservice.h"
#include "idartsscoreinput.h"
#include "idartsscoredb.h"

class GetDartsScoreById : public
        IBinaryService<const QUuid&,const IDartsScoreDb*,const IDartsScoreInput*>
{
public:
    const IDartsScoreInput* service(const QUuid& scoreId, const IDartsScoreDb* dbService) override
    {
        auto models = dbService->dartsScoreModels();
        for (const auto& model : models) {
            if(model->id() == scoreId)
                return model;
        }
        return nullptr;
    }
};

#endif // GETDARTSSCOREBYID_H
