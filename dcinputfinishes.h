#ifndef DCINPUTFINISHES_H
#define DCINPUTFINISHES_H

#include "DCInputsSLA/idartsinputfinishes.h"
#include "idcmetainfo.h"
#include <qstring.h>
#include "idartscreatefinishes.h"
#include "idartsfinishesdb.h"
#include "idcmetainfo.h"
#include "idartscreatefinishes.h"
class DCInputFinishes : public IDartsInputFinishes
{
public:
    static DCInputFinishes *createInstance(IDartsCreateFinishes *constructRows, IDartsFinishesDb *dbContext);
    virtual QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const override;
    IDartsFinishesDb *dbContext() const;
    void setDbContext(IDartsFinishesDb *service);
    IDartsCreateFinishes *constructTargetRows() const;
    void setConstructRow(IDartsCreateFinishes *newConstructRow);
private:
    DCInputFinishes(IDartsCreateFinishes *constructRows, IDartsFinishesDb *dbContext);
    QString getTargetRow(const int &turnIndex, const int &remainingScore) const;
    IDartsFinishesDb *_dbContext;
    IDartsCreateFinishes *_constructRow;
};
#endif // SCORECONTROLLER_H

