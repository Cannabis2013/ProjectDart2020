#ifndef DARTSDBCREATEJSONFROMPOINTS_H
#define DARTSDBCREATEJSONFROMPOINTS_H

#include "icreatejsonfrommodels.h"
#include <quuid.h>
#include "dartsinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsDbContext {
    typedef QVector<const IPlayerInput*> ModelsList;
    class DartsDbCreatejsonFromPoints : public ICreateJsonFromModels
    {
    public:
        virtual QByteArray createJson(const QVector<const IModel<QUuid>*> &models) const override;
    private:
        QJsonArray createJsonArray(const QVector<const IModel<QUuid>*> &models) const;
        QJsonObject createJsonObject(const IModel<QUuid>* model) const;
        QByteArray createByteArray(const QJsonArray &arr) const;
        const QString _key = "DartsPointInputs";
    };
}

#endif // DARTSINPUTJSONASSEMBLER_H
