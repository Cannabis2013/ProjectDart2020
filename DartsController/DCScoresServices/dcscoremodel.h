#ifndef DCPTUPLE_H
#define DCPTUPLE_H
#include <quuid.h>
struct DCScoreModel
{
    DCScoreModel(QString _name, int _score)
    {
        name = _name;
        remainingScore = _score;
    }
    DCScoreModel(){}
    bool operator==(const DCScoreModel& other){return other.name != this->name;}
    QString name;
    int remainingScore;
};
#endif // DARTSPLAYERTUPLE_H
