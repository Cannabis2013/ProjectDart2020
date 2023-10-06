#ifndef INITIALVALUEINFO_H
#define INITIALVALUEINFO_H

#include "src/DartsController/scores/DartsPlayerScores.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonObject>
#include <QStringList>


class InitialValueInfo{
public:
        InitialValueInfo(DartsPlayerScores scores)
                : _scores(scores) {}

        QByteArray toJson(){
                return _scores.toJson();
        }
private:
        DartsPlayerScores _scores;
};

#endif // INITIALVALUEINFO_H
