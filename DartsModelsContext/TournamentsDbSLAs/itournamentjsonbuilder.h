#ifndef ITOURNAMENTJSONBUILDER_H
#define ITOURNAMENTJSONBUILDER_H
#include <qjsonobject.h>
#include <quuid.h>
#include <qvector.h>
#include "ModelsContext/DbSLAs/icreatedatafrom.h"
#include "ModelsContext/ModelsSLAs/imodel.h"
template<typename TModel, typename TJsonFormat>
class IDartsJsonBuilder  : public ICreateDataFrom<IModel<QUuid>,TJsonFormat>
{
public:
    typedef TModel Model;
    typedef TJsonFormat JsonFormat;
    virtual JsonFormat create(Model *model) const = 0;
    virtual JsonFormat create(const QVector<Model*>& models) const = 0;
};
#endif // ICREATEJSONFROMDARTSINPUT_H
