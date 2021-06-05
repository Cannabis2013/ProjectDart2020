#ifndef IDARTSSCOREJSONSERVICE_H
#define IDARTSSCOREJSONSERVICE_H

#include <qvector.h>

template<typename  TModelInterface, typename TModelIndexes, typename TJsonFormat>
class IDartsScoreJsonService
{
public:
    typedef TModelInterface ModelInterface;
    typedef TModelIndexes ModelIndexes;
    typedef TJsonFormat JsonFormat;
    virtual JsonFormat assembleJsonDartsScoreIndexes(const ModelIndexes*) const = 0;
    virtual JsonFormat assembleJsonFromDartsMultiAttemptScores(const QVector<const ModelInterface *>&) const = 0;
};

#endif // IDARTSSCOREJSONSERVICE_H
