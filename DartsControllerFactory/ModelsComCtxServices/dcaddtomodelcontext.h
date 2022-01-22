#ifndef DCADDTOMODELCONTEXT_H
#define DCADDTOMODELCONTEXT_H
#include "ModelsComCtxSLAs/idcaddtomdsctx.h"
#include "DCInputSLAs/idcinputbuilder.h"
#include "Models/dcinput.h"
#include "SLAs/absdartsctx.h"
#include "ConverterSLAs/idcindexconverter.h"
#include "Models/dcindex.h"
#include "Models/dcmeta.h"

#include <qjsondocument.h>
class DCAddToModelsContext : public IDCAddToMdsCtx
{
    // IDCAddToMdsCtx interface
public:
    virtual bool add(DCInput &ipt, const DCIndex &idx, const DCMeta &meta,
                     AbsDartsCtx *mdsCtx, InputBuilder *cvtr, IDCIndexConverter *idxCvt) override
    {
        auto cvtdIdx = idxCvt->convert(idx);
        auto inputBa = cvtr->create(ipt);
        auto r1 = mdsCtx->addInput(meta.tournamentId,toByteArray(inputBa));
        auto r2 = mdsCtx->updateTournamentIndex(meta.tournamentId,cvtdIdx);
        return r1 && r2;
    }
private:
    QByteArray toByteArray(const QJsonObject &json)
    {
        return QJsonDocument(json).toJson();
    }
};



#endif // DCADDTOMODELCONTEXT_H
