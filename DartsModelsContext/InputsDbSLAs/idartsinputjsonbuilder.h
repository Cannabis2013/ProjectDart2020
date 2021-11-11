#ifndef IDARTSINPUTJSONBUILDER_H
#define IDARTSINPUTJSONBUILDER_H
#include <qjsonarray.h>
#include <quuid.h>
#include "DartsModelsContext/TournamentModels/dartsmetamodel.h"
#include "ModelsContext/ModelsSLAs/imodel.h"
class IDartsInputJsonBuilder
{
public:
    virtual QByteArray json(IModel<QUuid> *model, const DartsMetaModel &meta = DartsMetaModel()) const = 0;
    virtual QByteArray json(const QVector<IModel<QUuid>*> &models) const = 0;
    virtual QJsonArray jsonArray(const QVector<IModel<QUuid>*> &models) const = 0;
};
#endif // ICREATEJSONFROMDARTSINPUTS_H
