#ifndef ICREATEINPUT_H
#define ICREATEINPUT_H
class QString;
template<typename TInput>
class ICreateInput
{
public:
    typedef TInput Ipt;
    virtual Ipt create(const QString &name, const int &point, const int &score, const int &modCode) const = 0;
};

#endif // ICREATEINPUT_H
