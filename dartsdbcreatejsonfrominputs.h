#ifndef DARTSDBCREATEJSONFROMINPUTS_H
#define DARTSDBCREATEJSONFROMINPUTS_H

#include "ModelsContext/MCJsonSLAs/icreatejsonfrommodels.h"
#include <quuid.h>
#include "DartsModelsContext/DMCInputServices/dartsinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsDbContext {
    typedef QVector<const IPlayerInput*> ModelsList;
    class DartsDbCreatejsonFromInputs : public ICreateJsonFromModels
    {
    public:
        virtual QByteArray toJson(const QVector<const IModel<QUuid>*> &models) const override;
    private:
        QJsonArray createJsonArray(const QVector<const IModel<QUuid>*> &models) const;
        QJsonObject createJsonObject(const IModel<QUuid>* model) const;
        QByteArray createByteArray(const QJsonArray &arr) const;
        const QString _key = "DartsInputModels";
    };
}

#endif // DARTSINPUTJSONASSEMBLER_H
