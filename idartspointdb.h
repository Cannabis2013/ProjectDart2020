#ifndef IDARTSPOINTDB_H
#define IDARTSPOINTDB_H

#include <qvector.h>

template<typename TModelInterface>
class IdartsPointDb
{
public:
    virtual void addDartsInputModel(const TModelInterface* model) = 0;
    virtual const TModelInterface* getDartsInputModelByIndex(const int& index) const = 0;
    virtual QVector<const TModelInterface*> dartsInputModels() const = 0;
    virtual void removeDartsInputModelByIndex(const int&) = 0;
    virtual int indexOfDartsInputModel(const TModelInterface*) = 0;
    virtual void replaceDartsInputModel(const int&, const TModelInterface*) = 0;
};

#endif // IDARTSPOINTDB_H
