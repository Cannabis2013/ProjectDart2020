#ifndef CREATEJSONFROMPLAYERMODELS_H
#define CREATEJSONFROMPLAYERMODELS_H

#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <QJsonObject>
#include <quuid.h>
#include "imodel.h"
#include "iplayermodel.h"
#include "icreatejsonfromplayermodels.h"

namespace ModelsContext {
    class CreateJsonFromPlayerModels : public ICreateJsonFromPlayerModels
    {
    public:
        virtual QByteArray createJson(QVector<const IModel<QUuid>*> models) const override;
    private:
        QJsonArray createJsonArray(QVector<const IModel<QUuid>*> models) const;
        QJsonObject createJsonObject(const IModel<QUuid> *model) const;
        QByteArray createByteArray(const QJsonArray &arr) const;
    };
}


#endif // PLAYERJSONASSEMBLER_H
