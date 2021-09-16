#ifndef ISCORESSERVICE_H
#define ISCORESSERVICE_H

#include <qvector.h>


template<typename TTuple>
class IScoresService
{
public:
    typedef QVector<TTuple> DartsScoreModels;
    virtual const DartsScoreModels &scoreModels() = 0;
};

#endif // ISCORESSERVICE_H
