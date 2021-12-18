#ifndef IDARTSINPUTBUILDER_H
#define IDARTSINPUTBUILDER_H
#include <qjsonobject.h>
#include "InputModels/diptvals.h"
#include "InputModelsSLAs/abstractdartsinput.h"
#include "DbSLAs/iconverttomodels.h"
template<typename TBaseModel, typename TSuperModel, typename TJsonFormat, typename TCtrlVals>
class IDartsInputBuilder : public IConvertToModels<TJsonFormat,TBaseModel>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    typedef TBaseModel Model;
    typedef TSuperModel SuperModel;
    typedef TJsonFormat Json;
    typedef TCtrlVals ctrlVals;
    virtual SuperModel *convert(ctrlVals vals, const QUuid &tournamentId, const QUuid &playerId, const int &hint = DisplayHint) const = 0;
    virtual QVector<Model *> convert(const Json &json) const override = 0;
};
#endif // IDARTSINPUTBUILDER_H
