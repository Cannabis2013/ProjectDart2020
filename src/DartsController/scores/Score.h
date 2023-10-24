#ifndef DARTSINTERNALSCORE_H
#define DARTSINTERNALSCORE_H

#include <qjsonobject.h>
#include <qstring.h>

class Score{
public:
        Score(QString name, int score)
            : _name(name)
            , _score(score)
        {
        }

        Score(QString name)
            : _name(name)
        {
        }

        Score(const QJsonObject &jsonObj){
                _name = jsonObj["playerName"].toString("");
                _score = jsonObj["playerScore"].toInt(-1);
        }

        QJsonObject toJsonObject() const{
                QJsonObject jsonObj;
                jsonObj["playerName"] = _name;
                jsonObj["playerScore"] =  _score;
                return jsonObj;
        }

        QString name() const
        {
                return _name;
        }

        int score() const
        {
                return _score;
        }

private:
        QString _name;
        int _score = 0;
};





#endif // DARTSINTERNALSCORE_H
