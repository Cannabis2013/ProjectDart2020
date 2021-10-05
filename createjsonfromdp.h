#ifndef CREATEJSONFROMDP_H
#define CREATEJSONFROMDP_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include "iqmldatabuilder.h"

class CreateJsonFromDP : public IQMLDataBuilder<QPair<int,int>,QVariant>
{
public:
    typedef QPair<int,int> PointInput;
    virtual QVariant createItem(const PointInput &model) const override
    {
        auto json = toJson(model);
        return QVariant(json);
    }
private:
    QByteArray toJson(const PointInput &model) const
    {
        QJsonObject obj;
        obj["point"] = toString(model.first);
        obj["score"] = toString(model.second);
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
    QString toString(const int &value) const
    {
        if(value != -1)
            return QString::number(value);
        else
            return QString();
    }
};

#endif // DARTSTABLECREATEJSON_H
