#ifndef ITOURNAMENTJSONBUILDER_H
#define ITOURNAMENTJSONBUILDER_H
#include "DbSLAs/imodelconverter.h"
class QUuid;
template<typename T>
class IModel;
template<typename TModel, typename TJson>
class IDartsJsonBuilder  : public IModelConverter<IModel<QUuid>,TJson>
{
public:
    typedef TModel Model;
    typedef TJson Json;
    virtual Json create(const QVector<Model*>& from, Json& to) const override = 0;
    virtual Json create(Model *model) const = 0;
    virtual Json create(const QVector<Model*>& models) const = 0;
};
#endif // ICREATEJSONFROMDARTSINPUT_H
