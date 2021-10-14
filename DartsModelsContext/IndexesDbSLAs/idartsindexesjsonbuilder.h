#ifndef IDARTSINDEXESJSONBUILDER_H
#define IDARTSINDEXESJSONBUILDER_H

#include "ModelsContext/MCModelsSLAs/imodel.h"
#include <quuid.h>

class IDartsIndexesJsonBuilder
{
public:
    virtual QByteArray indexesModelJson(IModel<QUuid>* &model) const = 0;
    virtual QByteArray indexesModelsJson(const QVector<IModel<QUuid>*> &models) const = 0;
};
#endif // IDARTSINDEXESJSONBUILDER_H
