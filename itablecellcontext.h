#ifndef ITABLECELLCONTEXT_H
#define ITABLECELLCONTEXT_H

template<typename T>
class ITableCellContext
{
public:
    virtual int initialValue() const = 0;
    virtual void setInitialValue(const int &value) = 0;
    virtual T defaultValues() const = 0;
};
#endif // ITABLECELLVALUES_H
