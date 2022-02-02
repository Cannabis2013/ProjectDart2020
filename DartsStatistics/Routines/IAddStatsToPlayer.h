#ifndef IADDSTATSTOPLAYER_H
#define IADDSTATSTOPLAYER_H
class Input;
class IAddStatsToPlayer
{
public:
    virtual void update(Input &input) = 0;
};

#endif // IADDSTATSTOPLAYER_H
