#ifndef IDARTSINPUTBUILDER_H
#define IDARTSINPUTBUILDER_H
#include <qjsonobject.h>
#include "DartsModelsContext/InputModels/diptvals.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "ModelsContext/ModelsSLAs/imodel.h"
#include "ModelsContext/DbSLAs/icreatemodelsfrom.h"
template<typename TBaseModel, typename TSuperModel, typename TJsonFormat>
class IDartsInputBuilder : public ICreateModelsFrom<TJsonFormat,TBaseModel>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    typedef TBaseModel BaseModel;
    typedef TSuperModel SuperModel;
    typedef TJsonFormat JsonFormat;
    virtual SuperModel *create(DIptVals &vals, const QUuid &tournamentId, const bool &genId = true,
                               const int &hint = DisplayHint) const = 0;
    virtual QVector<BaseModel *> create(const JsonFormat &json) const override = 0;
};
#endif // IDARTSINPUTBUILDER_H
