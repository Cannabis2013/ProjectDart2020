#ifndef DCPTUPLE_H
#define DCPTUPLE_H

#include <quuid.h>

namespace DCContext {
    struct DCScoreModel
    {
        DCScoreModel(QUuid _id, QString _name, int _score)
        {
            playerId = _id;
            playerName = _name;
            totalScore = _score;
        }
        DCScoreModel(){}
        bool operator==(const DCScoreModel& other){
            if(other.playerId != this->playerId)
                return false;
            else if(other.playerName != this->playerName)
                return false;
            else if(other.totalScore != this->totalScore)
                return false;
            return true;
        }
        QUuid playerId;
        QString playerName;
        int totalScore;
    };
}
#endif // DARTSPLAYERTUPLE_H
