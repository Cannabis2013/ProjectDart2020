#ifndef DARTINITINFO_H
#define DARTINITINFO_H

#include <QStringList>
#include <qjsondocument.h>
#include <QJsonArray>
#include <QJsonObject>

class DartInitInfo
{
public:
        DartInitInfo(const QStringList& playerNames){
                _playerNames = playerNames;
                _playersCount = playerNames.count();
        }

        static DartInitInfo fromjson(const QByteArray &json){
                DartInitInfo info;
                auto jsonDoc = QJsonDocument::fromJson(json);
                QStringList names;
                if(!jsonDoc.isArray())
                        return DartInitInfo();
                auto arr = jsonDoc.array();
                for (auto i = arr.begin(); i != arr.end(); ++i)
                        names <<  i->toString();
                info._playerNames = names;
                info._playersCount = names.count();
                return info;
        }

        QStringList playerNames() const
        {
                return _playerNames;
        }


        int playersCount() const
        {
                return _playersCount;
        }

private:
        DartInitInfo(){}
        QStringList _playerNames;
        int _playersCount;
};

#endif // DARTINITINFO_H
