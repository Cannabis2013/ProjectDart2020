#ifndef DCFINISHBUILDER_H
#define DCFINISHBUILDER_H

#include "DartsController/DCFinishesSLAs/idcfinishbuilder.h"
#include <qstring.h>
#include "DartsController/DCFinishesSLAs/idartscreatefinishes.h"
#include "DartsController/DCFinishesSLAs/idartsfinishesdb.h"
#include "DartsController/DCFinishesSLAs/idartscreatefinishes.h"
class DCFinishBuilder : public IDCFinishBuilder
{
public:
    static DCFinishBuilder *createInstance(IDartsCreateFinishes *constructRows, IDartsFinishesDb *dbContext);
    virtual QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const override;
    IDartsFinishesDb *dbContext() const;
    void setDbContext(IDartsFinishesDb *service);
    IDartsCreateFinishes *constructTargetRows() const;
    void setConstructRow(IDartsCreateFinishes *service);
private:
    DCFinishBuilder(IDartsCreateFinishes *constructRows, IDartsFinishesDb *dbContext);
    QString getTargetRow(const int &turnIndex, const int &remainingScore) const;
    IDartsFinishesDb *_dbContext;
    IDartsCreateFinishes *_constructRow;
};
#endif // SCORECONTROLLER_H

