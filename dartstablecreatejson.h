#ifndef DARTSTABLECREATEJSON_H
#define DARTSTABLECREATEJSON_H

#include "itablecreatevariant.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class DartsTableCreateJson : public ITableCreateVariant<QPair<int,int>>
{
    // ITableCreateVariant interface
public:
    typedef QPair<int,int> PointInput;
    virtual QVariant create(const PointInput &model) const override
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
