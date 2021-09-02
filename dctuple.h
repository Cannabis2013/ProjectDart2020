#ifndef DCPTUPLE_H
#define DCPTUPLE_H

#include <quuid.h>

namespace DCContext {
    struct DCPTuple
    {
        DCPTuple(QUuid _id, QString _name, int _score)
        {
            id = _id;
            name = _name;
            totalScore = _score;
        }
        DCPTuple(){}
        bool operator==(const DCPTuple& other){
            if(other.id != this->id)
                return false;
            else if(other.name != this->name)
                return false;
            else if(other.totalScore != this->totalScore)
                return false;
            return true;
        }
        QUuid id;
        QString name;
        int totalScore;
    };
}
#endif // DARTSPLAYERTUPLE_H
