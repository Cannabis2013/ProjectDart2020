#ifndef IDCSTATUS_H
#define IDCSTATUS_H

class IDCStatus
{
public:
    virtual int get() const = 0;
    virtual void set(const int &value) = 0;
};
#endif // IDCMETASTATUS_H
