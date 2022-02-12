#ifndef IUPDATECURRENTSTATS_H
#define IUPDATECURRENTSTATS_H
template<typename T> class QVector;
struct SnapShot;
template<typename TInput>
class IUpdateCurrentStats
{
public:
    typedef TInput Ipt;
    typedef QVector<Ipt> Ipts;
    virtual void update(Ipt &input) = 0;
    virtual void update(Ipts &inputs) = 0;
};

#endif // IADDSTATSTOPLAYER_H
