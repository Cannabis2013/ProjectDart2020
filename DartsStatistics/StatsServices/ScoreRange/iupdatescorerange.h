#ifndef IUPDATESCORERANGE_H
#define IUPDATESCORERANGE_H
template<typename TInput, typename TStats>
class IUpdateScoreRange
{
public:
    typedef TInput Ipt;
    typedef TStats TempStats;
    virtual void update(Ipt &input, TempStats *stats) const = 0;
};

#endif // IUPDATESCORERANGE_H
