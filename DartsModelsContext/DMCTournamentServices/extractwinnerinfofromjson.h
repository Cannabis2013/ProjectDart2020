#ifndef EXTRACTWINNERINFOFROMJSON_H
#define EXTRACTWINNERINFOFROMJSON_H

#include "DartsModelsContext/TournamentsSLAs/iwinnerinfobuilder.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class ExtractWinnerInfoFromJson : public IWinnerInfoBuilder
{
public:
    virtual DataModel create(const QByteArray &json) const override;
private:
    DataModel createDataModelFromObject(const QJsonObject &obj) const;
    QJsonObject createJsonObject(const QByteArray &json) const;
};

#endif // GETDARTSTOURNAMENTDATAFROMJSON_H
