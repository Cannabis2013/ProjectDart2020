#ifndef ISCORESSERVICE_H
#define ISCORESSERVICE_H

#include <qvector.h>


template<typename TModel>
class IScoresService
{
public:
    typedef QVector<TModel> DartsScoreModels;
    virtual const DartsScoreModels &scoreModels() = 0;
};

#endif // ISCORESSERVICE_H
