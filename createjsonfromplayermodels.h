#ifndef CREATEJSONFROMPLAYERMODELS_H
#define CREATEJSONFROMPLAYERMODELS_H

#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <QJsonObject>
#include <quuid.h>
#include "imodel.h"
#include "playermodel.h"
#include "icreatejsonfromplayermodels.h"

namespace DartsModelsContext {
    class CreateJsonFromPlayerModels : public ICreateJsonFromPlayerModels
    {
    public:
        virtual QByteArray createJson(QVector<const IPlayerModel *> models) const override;
    private:
        QJsonArray createJsonArray(QVector<const IPlayerModel *> models) const;
        QJsonObject createJsonObject(const IPlayerModel* model) const;
        QByteArray createByteArray(const QJsonArray &arr) const;
    };
}


#endif // PLAYERJSONASSEMBLER_H
