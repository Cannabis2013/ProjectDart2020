#ifndef GETDARTSINPUTMODELBYID_H
#define GETDARTSINPUTMODELBYID_H

#include "ibinaryservice.h"
#include "idartspointdb.h"
#include "idartspointinput.h"

namespace DartsModelsContext {
    class GetDartsInputModelById :
            public IBinaryService<const QUuid&,
                                  const IModelsDbContext<IModel<QUuid,QByteArray>,QUuid>*,
                                  const IModel<QUuid,QByteArray>*>
    {
    public:
        typedef IModelsDbContext<IModel<QUuid,QByteArray>,QUuid> ModelsDbService;
        const IModel<QUuid,QByteArray>* service(const QUuid& pointId, const ModelsDbService* dbService) override
        {
            auto models = dbService->models();
            for (const auto& model : models) {
                if(model->id() == pointId)
                    return model;
            }
            throw "Darts point model not found!";
        }
    };
}


#endif // GETDARTSINPUTMODELBYID_H
