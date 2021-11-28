#ifndef TESTJSONDARTSBUILDER_H
#define TESTJSONDARTSBUILDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
class TestJsonDartsBuilder
{
public:
    enum InputModes{
        pointMode = 0x5,
        scoreMode = 0x6
    };
    enum GameModes{
        darts = 0x1,
        circular = 0x2
    };
    enum InitialPoints{
        threeHundredAndOne = 301,
        fiveHundredAndOne = 501,
        sevenHundredAndOne = 701,
        nineHundredAndOne = 901
    };

    QByteArray dartsTournamentOne()
    {
        QJsonObject obj;
        obj["title"] = "DSSC";
        obj["gameMode"] = darts;
        obj["inputHint"] = scoreMode;
        obj["keyPoint"] = fiveHundredAndOne;
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
private:
    QJsonArray toJsonArray(std::initializer_list<int> list)
    {
        QJsonArray arr;
        for (auto i = list.begin();i != list.end();i++ )
            arr.append(*i);
        return arr;
    }
};

#endif // TESTJSONDARTSBUILDER_H
