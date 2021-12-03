#ifndef DCCREATESCOREMODELS_H
#define DCCREATESCOREMODELS_H
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
class DCCreateScoreModels : public IDCScoreBuilder
{
public:
    virtual QVector<DCScoreModel> createScores(const QStringList &names, const int &initialScore) const override
    {
        QVector<DCScoreModel> scoreModels;
        for (const auto &name : names)
            scoreModels << toModel(name,initialScore);
        return scoreModels;
    }
private:
    DCScoreModel toModel(const QString &name, const int &initialScore) const
    {
        DCScoreModel scoreModel;
        scoreModel.name = name;
        scoreModel.remainingScore = initialScore;
        return scoreModel;
    }
};
#endif // DCCREATESCORETUPLES_H
