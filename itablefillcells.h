#ifndef ITABLEFILLCELLS_H
#define ITABLEFILLCELLS_H

template<typename T, typename U>
class ITableFillCells
{
public:
    virtual void fill(const int &start, const int &delta, const int &count, T &cells, const U &defaultValue) const = 0;
};
#endif // IFILLDATA_H
