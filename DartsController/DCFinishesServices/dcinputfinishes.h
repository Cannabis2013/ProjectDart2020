#ifndef DCINPUTFINISHES_H
#define DCINPUTFINISHES_H

#include "DartsController/DCFinishesSLAs/idartsinputfinishes.h"
#include "DartsControllerBuilder/DCBMetaSLAs/idcmetainfo.h"
#include <qstring.h>
#include "DartsController/DCFinishesSLAs/idartscreatefinishes.h"
#include "DartsController/DCFinishesSLAs/idartsfinishesdb.h"
#include "DartsControllerBuilder/DCBMetaSLAs/idcmetainfo.h"
#include "DartsController/DCFinishesSLAs/idartscreatefinishes.h"
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

