#ifndef CREATEJSONFROMPLAYERMODELS_H
#define CREATEJSONFROMPLAYERMODELS_H

#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <QJsonObject>
#include <quuid.h>
#include "imodel.h"
#include "iplayermodel.h"
#include "icreatejsonfrommodels.h"

namespace PlayersContext {
    class CreateJsonFromPlayerModels : public ICreateJsonFromModels
    {
    public:
        virtual QByteArray toJson(const QVector<const IModel<QUuid>*>& models) const override;
    private:
        QJsonArray createJsonArray(QVector<const IModel<QUuid>*> models) const;
        QJsonObject createJsonObject(const IModel<QUuid> *model) const;
        QByteArray createByteArray(const QJsonArray &arr) const;
    };
}


#endif // PLAYERJSONASSEMBLER_H
