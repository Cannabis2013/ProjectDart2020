#ifndef ICREATEINPUT_H
#define ICREATEINPUT_H
class QString;
class Input;
class ICreateInput
{
public:
    virtual Input create(const QString &name, const int &point, const int &score, const int &modCode) const = 0;
};

#endif // ICREATEINPUT_H
