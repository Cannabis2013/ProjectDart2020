#ifndef ERRORINFO_H
#define ERRORINFO_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qstring.h>

class ErrorInfo
{
public:
        ErrorInfo(const QString& message) : _message(message)
        {}

        QString message() const
        {
                return _message;
        }

        QByteArray toJson() const {
                QJsonObject jsonObj;
                jsonObj["message"] = _message;
                jsonObj["type"] = "error";
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

private:
        QString _message;
};

#endif // ERRORINFO_H
