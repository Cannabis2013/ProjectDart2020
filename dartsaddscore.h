#ifndef DARTSADDSCORE_H
#define DARTSADDSCORE_H

#include "idartsaddscore.h"

class DartsAddScore : public IDartsAddScore
{
public:
    virtual int addPlayerScore(const QUuid &id, const int &score, IDCScoresService *scoresService) const override
    {
        auto tuple = getTupleFromScoresService(id,scoresService);
        auto indexOfTuple = indexOf(tuple,scoresService);
        updateTuple(tuple,sum(tuple.totalScore,score));
        replaceTuple(indexOfTuple,tuple,scoresService);
        return tuple.totalScore;
    }
private:
    void updateTuple(DCContext::DCPTuple &tuple, const int &score) const
    {
        if(score < 0)
            throw "Invalid score";
        tuple.totalScore = score;
    }
    DCContext::DCPTuple getTupleFromScoresService(const QUuid& id, IDCScoresService *scoresService) const
    {
        auto tuples = scoresService->tuples();
        for (int i = 0; i < tuples.count(); ++i) {
            auto tuple = tuples.at(i);
            auto _id = tuple.id;
            if(id == _id)
                return tuple;
        }
        return DCContext::DCPTuple();
    }
    int indexOf(const DCContext::DCPTuple& tuple, IDCScoresService *scoresService) const
    {
        auto tuples = scoresService->tuples();
        for (int i = 0; i < tuples.count(); ++i) {
            auto t = tuples.at(i);
            if(t == tuple)
                return i;
        }
        return -1;
    }
    int sum(const int &score, const int &newSum) const
    {
        return score + newSum;
    }
    void replaceTuple(const int &index,const DCContext::DCPTuple &tuple, IDCScoresService *scoresService) const
    {
        auto tuples = scoresService->tuples();
        tuples.replace(index, tuple);
    }
};
#endif // DARTSADDSCORE_H
