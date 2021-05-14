#ifndef GETDARTSSCOREMODELBYID_H
#define GETDARTSSCOREMODELBYID_H

#include "ibinaryservice.h"
#include "idartspointdb.h"
#include "idartspointinput.h"

class GetDartsPointModelById :
        public IBinaryService<const QUuid&,
                              const IDartsPointDb*,
                              const IDartsPointInput*>
{
public:
    const IDartsPointInput* service(const QUuid& pointId, const IDartsPointDb* dbService) override
    {
        auto models = dbService->dartsInputModels();
        for (const auto& model : models) {
            if(model->id() == pointId)
                return model;
        }
        throw "Darts point model not found!";
    }
};

#endif // GETDARTSSCOREMODELBYID_H
