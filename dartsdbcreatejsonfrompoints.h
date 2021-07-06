#ifndef DARTSDBCREATEJSONFROMPOINTS_H
#define DARTSDBCREATEJSONFROMPOINTS_H

#include "icreatejsonfrominputs.h"
#include <quuid.h>
#include "dartspointinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsDbContext {
    typedef QVector<const IPlayerInput*> ModelsList;
    class DartsDbCreatejsonFromPoints : public ICreateJsonFromInputs
    {
    public:
        virtual QByteArray createJson(const QVector<const IPlayerInput*> &models) const override;
    private:
        QJsonArray createJsonArray(const QVector<const IPlayerInput*> &models) const;
        QJsonObject createJsonObject(const IPlayerInput* model) const;
        QByteArray createByteArray(const QJsonArray &arr) const;
        const QString _key = "DartsPointInputs";
    };
}

#endif // DARTSINPUTJSONASSEMBLER_H
