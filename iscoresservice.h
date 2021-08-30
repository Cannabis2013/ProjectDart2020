#ifndef ISCORESSERVICE_H
#define ISCORESSERVICE_H

#include <qvector.h>


template<typename TPlayerModel, typename TTuple, typename MetaInfoService>
class IScoresService
{
public:
    typedef QVector<TTuple> DartsPlayerTuples;
    typedef QVector<TPlayerModel> PlayerModels;
    virtual const DartsPlayerTuples &tuples() = 0;
};

#endif // ISCORESSERVICE_H
