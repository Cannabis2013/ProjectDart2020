#ifndef DARTSCREATEJSONFROMSCORES_H
#define DARTSCREATEJSONFROMSCORES_H

#include "idartscreatejsonfromscores.h"
#include "idartsscoreinput.h"
#include <qbytearray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsModelsContext {
    class DartsCreateJsonFromScores : public
            IDartsCreateJsonFromScores
    {
    public:
        QByteArray createJson(const QVector<const IPlayerInput*> &) const override;
    private:
        QJsonArray createJsonArray(const QVector<const IPlayerInput*> &models) const;
        QJsonObject createJsonObject(const IPlayerInput* model) const;
        QByteArray createByteArray(const QJsonArray &arr) const;
    };
}

#endif // DARTSSCOREJSONSERVICE_H
