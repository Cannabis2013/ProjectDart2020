#ifndef IDARTSSTATISTICS_H
#define IDARTSSTATISTICS_H
template<typename T>
class QVector;
class QString;
class IDartsStatistics
{
public:
    typedef struct Ipt Input;
    virtual void init(const QVector<Input*> &data) = 0;
    virtual void reset() = 0;
    virtual void clear() = 0;
    virtual void update(const QString &name, const int &point, const int &score, const int &modCode) = 0;
};

#endif // IDARTSSTATISTICS_H
