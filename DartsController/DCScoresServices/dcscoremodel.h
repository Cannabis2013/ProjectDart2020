#ifndef DCPTUPLE_H
#define DCPTUPLE_H
#include <quuid.h>
struct DCScoreModel
{
    DCScoreModel(QString _name, int _score)
    {
        name = _name;
        remScore = _score;
    }
    DCScoreModel(){}
    bool operator==(const DCScoreModel& other){return other.name != this->name;}
    QString name;
    int remScore;
};
#endif // DARTSPLAYERTUPLE_H
