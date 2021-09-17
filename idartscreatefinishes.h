#ifndef IDARTSCREATEFINISHES_H
#define IDARTSCREATEFINISHES_H

#include <qvector.h>

class IDartsCreateFinishes
{
public:
    struct ScoreModel
    {
        QVector<char> multiplier;
        QVector<int> pointValue;
    };
    typedef QMultiHash<int,QString> TargetRows;
    typedef QVector<const TargetRows*> AllTargetRows;
    virtual AllTargetRows constructRows() const = 0;
};
#endif // IDARTSCONSTRUCTTARGETROW_H
