#ifndef DCSCORESCONTEXT_H
#define DCSCORESCONTEXT_H
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
class DCScoresContext : public AbstractDCScoresCtx
{
public:
    DCScoresContext(IDCMetaCtx *metaContext)
    {
        setMetaContext(metaContext);
    }
    DartsScoreModels &scores() override
    {
        return _scoreModels;
    }
    DCScoreModel &score(const QString &name) override
    {
        for (auto &scoreModel : _scoreModels) {
            if(scoreModel.name == name)
                return scoreModel;
        }
        throw "SCOREMODEL NOT FOUND";
    }
    virtual void reset() override
    {
        auto defaultScore = metaContext()->get().initRemScore;
        for (auto &scoreModel : _scoreModels)
            scoreModel.remScore = defaultScore;
    }
    virtual DartsScoreModels scores() const override
    {
        return _scoreModels;
    }
private:
    DartsScoreModels _scoreModels;
};
#endif // DARTSSCORES_H
