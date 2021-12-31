#ifndef IDARTSCREATEFINISHES_H
#define IDARTSCREATEFINISHES_H
template<typename T, typename U>
class QMultiHash;
class QString;
template<typename T>
class QVector;
class IDartsCreateFinishes
{
public:
    struct ScoreModel
    {
        QVector<char> multiplier;
        QVector<int> pointValue;
    };
    typedef QMultiHash<int,QString> TargetRows;
    typedef QVector<TargetRows*> AllTargetRows;
    virtual AllTargetRows constructRows() const = 0;
};
#endif // IDARTSCONSTRUCTTARGETROW_H
