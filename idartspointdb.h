#ifndef IDARTSPOINTDB_H
#define IDARTSPOINTDB_H

#include <qvector.h>
#include <idartspointinput.h>

class IdartsPointDb
{
public:
    virtual void addDartsInputModel(const IDartsPointInput* model) = 0;
    virtual const IDartsPointInput* getDartsInputModelByIndex(const int& index) const = 0;
    virtual QVector<const IDartsPointInput*> dartsInputModels() const = 0;
    virtual void removeDartsInputModelByIndex(const int&) = 0;
    virtual int indexOfDartsInputModel(const IDartsPointInput*) = 0;
    virtual void replaceDartsInputModel(const int&, const IDartsPointInput*) = 0;
};

#endif // IDARTSPOINTDB_H
