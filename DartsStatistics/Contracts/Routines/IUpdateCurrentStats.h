#ifndef IUPDATECURRENTSTATS_H
#define IUPDATECURRENTSTATS_H

#include <QVector>

template<typename TInput>
class IUpdateCurrentStats
{
public:
    typedef TInput Ipt;
    typedef QVector<Ipt> Inputs;
    virtual void update(Ipt &input) = 0;
    virtual void update(Inputs &inputs) = 0;
};

#endif // IADDSTATSTOPLAYER_H
