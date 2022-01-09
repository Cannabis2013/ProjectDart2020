#ifndef ABSDCCREATESCORE_H
#define ABSDCCREATESCORE_H
class AbsDCCreateScore
{
public:
    virtual int calc(const int &scoreCandidate, const int &remScore) const = 0;
};
#endif // ABSDCCALCSCORE_H
