#ifndef ITABLEINITROWVALUES_H
#define ITABLEINITROWVALUES_H
template<typename T, typename U>
class ITableInitRowValues
{
public:
    virtual void fill(const int &start, const int &delta, const int &count, T &cells, const U &defaultValue) const = 0;
};
#endif
