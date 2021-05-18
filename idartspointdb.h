#ifndef IDARTSPOINTDB_H
#define IDARTSPOINTDB_H

#include <qvector.h>
#include <idartspointinput.h>

class IDartsPointDb
{
public:
    virtual void addDartsInputModel(const DartsModelsContext::IDartsPointInput* model) = 0;
    virtual const DartsModelsContext::IDartsPointInput* getDartsInputModelByIndex(const int& index) const = 0;
    virtual QVector<const DartsModelsContext::IDartsPointInput*> dartsInputModels() const = 0;
    virtual void removeDartsInputModelByIndex(const int&) = 0;
    virtual int indexOfDartsInputModel(const DartsModelsContext::IDartsPointInput*) = 0;
    virtual void replaceDartsInputModel(const int&, const DartsModelsContext::IDartsPointInput*) = 0;
};

#endif // IDARTSPOINTDB_H
