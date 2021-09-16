#ifndef DCINPUTSUGGESTIONS_H
#define DCINPUTSUGGESTIONS_H

#include "idartsinputsuggestions.h"
#include <idcmetainfo.h>
#include <qstring.h>
#include "idartsconstructrow.h"

#include "idclogisticdb.h"
#include "idcmetainfo.h"
#include "idartsconstructrow.h"
class DCInputSuggestions : public IDartsInputSuggestions
{
public:
    static DCInputSuggestions *createInstance(IDartsConstructRow *constructRows, IDCLogisticDb *dbContext);
    virtual QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const override;
    IDCLogisticDb *dbContext() const;
    void setDbContext(IDCLogisticDb *service);
    IDartsConstructRow *constructTargetRows() const;
    void setConstructRow(IDartsConstructRow *newConstructRow);

private:
    DCInputSuggestions(IDartsConstructRow *constructRows, IDCLogisticDb *dbContext);
    QString getTargetRow(const int &turnIndex, const int &remainingScore) const;
    IDCLogisticDb *_dbContext;
    IDartsConstructRow *_constructRow;
};
#endif // SCORECONTROLLER_H

