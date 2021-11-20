#ifndef IDARTSINPUTBUILDER_H
#define IDARTSINPUTBUILDER_H
#include <quuid.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
class IDartsInputBuilder
{
public:
    virtual QVector<IModel<QUuid> *> createInputs(const QByteArray &json) const = 0;
};
#endif // IDARTSINPUTBUILDER_H
