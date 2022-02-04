#ifndef IADDSTATSTOPLAYER_H
#define IADDSTATSTOPLAYER_H
template<typename T> class QVector;
struct Input;
class IAddStatsToPlayer
{
public:
    typedef QVector<Input> Inputs;
    virtual void update(Input &input) = 0;
    virtual void update(const Inputs &inputs) = 0;
};

#endif // IADDSTATSTOPLAYER_H
