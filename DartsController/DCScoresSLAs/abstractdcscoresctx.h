#ifndef IDSCSCORESSERVICE_H
#define IDSCSCORESSERVICE_H
#include <quuid.h>
#include <qvector.h>
#include "DartsController/DCMetaSLAs/idcmetactx.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"
class AbstractDCScoresCtx
{
public:
    typedef QVector<DCScoreModel> DartsScoreModels;
    virtual void reset() = 0;
    virtual DCScoreModel &score(const QUuid &playerId) = 0;
    virtual DartsScoreModels &scores() = 0;
    virtual DartsScoreModels scores() const = 0;
    IDCMetaCtx *metaContext() const
    {
        return _metaContext;
    }
    void setMetaContext(IDCMetaCtx *newMetaContext)
    {
        _metaContext = newMetaContext;
    }
private:
    IDCMetaCtx *_metaContext;
};
#endif // IDARTSSCORES_H
