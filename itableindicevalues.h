#ifndef ITABLEINDICEVALUES_H
#define ITABLEINDICEVALUES_H

struct IndiceValues
{
    int first;
    int last;
    int count;
};
class ITableIndiceValues
{
public:
    virtual IndiceValues createIndiceValues(const int &start, const int &delta, const int &count) const = 0;
};
#endif // ICREATEROWINDICES_H
