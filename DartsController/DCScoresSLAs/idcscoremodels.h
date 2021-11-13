#ifndef IDSCSCORESSERVICE_H
#define IDSCSCORESSERVICE_H
#include <quuid.h>
#include <qvector.h>
#include "DartsController/DCScoresServices/dcscoremodel.h"
class IDCScoreModels
{
public:
    typedef QVector<DCScoreModel> DartsScoreModels;
    virtual void reset(const int &defaultScore) = 0;
    virtual DCScoreModel &score(const QUuid &playerId) = 0;
    virtual DartsScoreModels &scores() = 0;
};
#endif // IDARTSSCORES_H
