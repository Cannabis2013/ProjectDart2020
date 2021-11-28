#ifndef TESTJSONPLAYERBUILDER_H
#define TESTJSONPLAYERBUILDER_H
#include <qjsondocument.h>
#include <qjsonobject.h>
class TestJsonPlayerBuilder
{
public:
    QByteArray testPersonOne()
    {
        QJsonObject obj;
        obj["playerName"] = "Kent KillerHertz";
        obj["playerMail"] = "KillerHertz@gmail.com";
        return QJsonDocument(obj).toJson();
    }
    QByteArray testPersonTwo()
    {
        QJsonObject obj;
        obj["playerName"] = "Jesper Daa";
        obj["playerMail"] = "Daa@gmail.com";
        return QJsonDocument(obj).toJson();
    }
};
#endif // TSTPLABDR_H
