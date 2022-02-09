#ifndef IUPDATESCORERANGE_H
#define IUPDATESCORERANGE_H
template<typename TSnapShot, typename TStat>
class IUpdateScoreRange
{
public:
    virtual void update(TSnapShot &input, TStat *stats) const = 0;
};

#endif // IUPDATESCORERANGE_H
