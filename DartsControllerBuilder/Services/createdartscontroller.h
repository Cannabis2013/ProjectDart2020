#ifndef CREATEDARTSCONTROLLER_H
#define CREATEDARTSCONTROLLER_H
#include "DartsController/Controller/dartscontroller.h"
#include "DartsControllerBuilder/SLAs/abstractdcbuilder.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h"
#include "DartsController/DartsScoreController/createdsc.h"
#include "DartsController/DPController/createdpc.h"
class CreateDartsController : public AbstractDCBuilder
{
public:
    enum AbstractRouteByInputHint{
        PointHint = 0x5,
        ScoreHint = 0x6
    };
    CreateDartsController(ICreateDartsController *createDPC, ICreateDartsController *createDSC, ICreateDCMetaInfo *createMeta)
    {
        _createDPC = createDPC;
        _createDSC = createDSC;
        _createMeta = createMeta;
    }
    virtual void createController(const QByteArray &json) override
    {
        auto meta = _createMeta->service(json);
        auto controller = createDC(meta);
        emit sendController(controller);
    }
private:
    AbstractDartsController *createDC(const DCBMeta &meta)
    {
        if(meta.inputHint == PointHint)
            return _createDPC->create(meta);
        else if(meta.inputHint == ScoreHint)
            return _createDSC->create(meta);
        else
            throw "Illegal input hint";
    }
    ICreateDCMetaInfo* _createMeta;
    ICreateDartsController *_createDPC;
    ICreateDartsController *_createDSC;
};
#endif // BUILDDARTSSCORECONTROLLER_H
