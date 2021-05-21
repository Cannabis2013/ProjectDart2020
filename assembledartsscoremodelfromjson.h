#ifndef ASSEMBLEDARTSSCOREMODELFROMJSON_H
#define ASSEMBLEDARTSSCOREMODELFROMJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "dartsscoreinput.h"
#include <quuid.h>

namespace DartsModelsContext {
    class AssembleDartsScoreModelFromJson :
            public IUnaryService<const QByteArray&,const IDartsScoreInput*>
    {
    public:
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            allHints = 0x3
        };
        const IDartsScoreInput* service(const QByteArray& json) override
        {
            return DartsScoreInput::createInstance(json);
        }
    };
}


#endif // ASSEMBLEDARTSSCOREMODELFROMJSON_H
