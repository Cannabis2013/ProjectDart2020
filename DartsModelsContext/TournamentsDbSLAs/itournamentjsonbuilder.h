#ifndef ITOURNAMENTJSONBUILDER_H
#define ITOURNAMENTJSONBUILDER_H
#include "DartsModelsContext/DbSLAs/imodelconverter.h"
class QUuid;
template<typename T>
class IModel;
template<typename TModel, typename TJson>
class IDartsJsonBuilder  : public IModelConverter<IModel<QUuid>,TJson>
{
public:
    typedef TModel Model;
    typedef TJson JsonFormat;
    virtual JsonFormat create(Model *model) const = 0;
    virtual JsonFormat create(const QVector<Model*>& models) const = 0;
};
#endif // ICREATEJSONFROMDARTSINPUT_H
