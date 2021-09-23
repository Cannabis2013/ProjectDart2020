#ifndef IDCMETASTATUS_H
#define IDCMETASTATUS_H

class IDCMetaStatus
{
public:
    virtual int get() const = 0;
    virtual void set(const int &value) = 0;
};
#endif // IDCMETASTATUS_H
