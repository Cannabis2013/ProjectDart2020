#ifndef DCPTUPLE_H
#define DCPTUPLE_H
#include <quuid.h>
struct DCPlayer
{
    DCPlayer(const QString &_name, const int &_score, const bool &_in)
    {
        name = _name;
        remScore = _score;
        in = _in;
    }
    DCPlayer(){}
    bool operator==(const DCPlayer& other){return other.name != this->name;}
    QString name;
    QUuid id;
    int remScore;
    bool in;
};
#endif // DARTSPLAYERTUPLE_H
