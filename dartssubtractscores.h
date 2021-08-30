#ifndef DARTSSUBTRACTSCORES_H
#define DARTSSUBTRACTSCORES_H

#include "idartssubtractscores.h"

class DartsSubtractScores : public IDartsSubtractScore
{
public:
    virtual int subtractPlayerScore(const DSCContext::IDSCModel *model, IDCScoresService *scoresService) override
    {
        auto tuple = getTupleFromScoresService(model->playerId(),scoresService);
        auto indexOfTuple = indexOf(tuple,scoresService);
        auto tupleScore = tuple.totalScore;
        auto newTupleScore = tupleScore - model->score();
        tuple.totalScore = newTupleScore;
        replaceTuple(indexOfTuple,tuple,scoresService);
        return newTupleScore;
    }
    virtual void subtractPlayerScore(const QVector<DSCContext::IDSCModel*> &models, IDCScoresService *scoresService) override
    {
        for (const auto& model : models) {
            auto tuple = getTupleFromScoresService(model->playerId(),scoresService);
            auto indexOfTuple = indexOf(tuple,scoresService);
            auto tupleScore = tuple.totalScore;
            auto newTupleScore = tupleScore - model->score();
            tuple.totalScore = newTupleScore;
            replaceTuple(indexOfTuple,tuple,scoresService);
        }
    }
private:
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
    int indexOf(const DCContext::DCPTuple& tuple, IDCScoresService *scoresService)
    {
        auto tuples = scoresService->tuples();
        for (int i = 0; i < tuples.count(); ++i) {
            auto t = tuples.at(i);
            if(t == tuple)
                return i;
        }
        return -1;
    }
    void replaceTuple(const int &index,const DCContext::DCPTuple &tuple, IDCScoresService *scoresService)
    {
        auto tuples = scoresService->tuples();
        tuples.replace(index, tuple);
    }
};

#endif // DARTSSUBTRACTSCORES_H
