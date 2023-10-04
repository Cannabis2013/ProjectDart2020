#ifndef INITIALVALUEINFO_H
#define INITIALVALUEINFO_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>


class InitialValueInfo{
public:
        InitialValueInfo(QStringList playerNames, QVector<int> scores)
                : _playerNames(playerNames), _playerScores(scores) {}

        QByteArray toJson(){
                QJsonObject jsonObj;
                QJsonArray playerNames, playerScores;
                for (auto& name : qAsConst(_playerNames))
                        playerNames.append(name);
                for (auto& score : qAsConst(_playerScores))
                        playerScores.append(score);
                jsonObj["playerNames"] = playerNames;
                jsonObj["playerScores"] = playerScores;
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }
private:
        QStringList _playerNames;
        QVector<int> _playerScores;
};

#endif // INITIALVALUEINFO_H
