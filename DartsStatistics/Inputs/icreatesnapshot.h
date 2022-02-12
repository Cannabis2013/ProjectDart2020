#ifndef ICREATESNAPSHOT_H
#define ICREATESNAPSHOT_H
class QString;
template<typename TInput>
class ICreateSnapShot
{
public:
    typedef TInput Ipt;
    virtual Ipt create(const QString &name, const int &score, const int &modCode) const = 0;
};

#endif // ICREATEINPUT_H
