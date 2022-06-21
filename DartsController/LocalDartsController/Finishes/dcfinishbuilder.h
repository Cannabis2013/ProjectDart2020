#ifndef DCFINISHBUILDER_H
#define DCFINISHBUILDER_H

#include <DartsController/Contracts/Finishes/idcfinishbuilder.h>

class IDartsCreateFinishes;
class IDartsFinishesDb;

class DCFinishBuilder : public IDCFinishBuilder
{
public:
    virtual QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const override;
    IDartsFinishesDb *dbContext() const;
    void setDbContext(IDartsFinishesDb *service);
    IDartsCreateFinishes *constructTargetRows() const;
    void setConstructRow(IDartsCreateFinishes *service);
    void init();
private:
    QString getTargetRow(const int &turnIndex, const int &remainingScore) const;
    IDartsFinishesDb *_dbContext;
    IDartsCreateFinishes *_constructRow;
};
#endif // SCORECONTROLLER_H
