#ifndef DARTSINPUTBUILDER_H
#define DARTSINPUTBUILDER_H

#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include "qjsonobject.h"
#include "DartsModelsContext/DMCInputServices/dartsinput.h"
#include "DartsModelsContext/InputsDbSLAs/idartsinputbuilder.h"

class DartsInputBuilder : public IDartsInputBuilder
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    virtual IModel<QUuid> *createInput(const QByteArray &json) const override;
    virtual QVector<IModel<QUuid> *> createInputs(const QByteArray &json) const override;
private:
    const QJsonObject toJsonObject(const QByteArray &json) const;
    const QJsonArray toJsonArray(const QByteArray &json) const;
    QVector<IModel<QUuid> *> createInputsFromJsonArray(const QJsonArray &arr) const;
    ModelsContext::IDartsInput *toInputModel(const QJsonObject& jsonObject) const;
    QUuid toId(const QJsonObject &obj, const QString &key) const;
};
#endif // DARTSINPUTJSONEXTRACTOR_H
