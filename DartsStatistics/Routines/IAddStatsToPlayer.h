#ifndef IADDSTATSTOPLAYER_H
#define IADDSTATSTOPLAYER_H
template<typename T> class QVector;
struct Input;
template<typename TInput>
class IAddStatsToPlayer
{
public:
    typedef TInput Ipt;
    typedef QVector<Ipt> Ipts;
    virtual void update(Ipt &input) = 0;
    virtual void update(Ipts &inputs) = 0;
};

#endif // IADDSTATSTOPLAYER_H
