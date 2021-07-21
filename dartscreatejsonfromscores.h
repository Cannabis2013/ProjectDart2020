#ifndef DARTSCREATEJSONFROMSCORES_H
#define DARTSCREATEJSONFROMSCORES_H

#include "idartscreatejsonfromscores.h"
#include "idartsscoreinput.h"
#include <qbytearray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace ModelsContext {
    class DartsCreateJsonFromScores : public IDartsCreateJsonFromScores
    {
    public:
        QByteArray createJson(const QVector<const IModel<QUuid>*> &) const override;
    private:
        QJsonArray createJsonArray(const QVector<const IModel<QUuid>*> &models) const;
        QJsonObject createJsonObject(const IModel<QUuid>* model) const;
        QByteArray createByteArray(const QJsonArray &arr) const;
    };
}

#endif // DARTSSCOREJSONSERVICE_H
