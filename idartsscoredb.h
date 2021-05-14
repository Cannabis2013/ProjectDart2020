#ifndef IDARTSSCOREDB_H
#define IDARTSSCOREDB_H

#include <qvector.h>
#include "idartsscoreinput.h"

class IDartsScoreDb
{
public:
    virtual void addDartsInputModel(const IDartsScoreInput* model) = 0;
    virtual const IDartsScoreInput* getDartsInputModelByIndex(const int& index) const = 0;
    virtual QVector<const IDartsScoreInput*> dartsScoreModels() const = 0;
    virtual void removeDartsInputModelByIndex(const int&) = 0;
    virtual int indexOfDartsInputModel(const IDartsScoreInput*) = 0;
    virtual void replaceDartsInputModel(const int&, const IDartsScoreInput*) = 0;
};

#endif // IDARTSSCOREDB_H
