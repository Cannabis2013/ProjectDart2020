#ifndef ASSEMBLEDARTSSCOREBYJSON_H
#define ASSEMBLEDARTSSCOREBYJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "qjsonarray.h"
#include "dartsscore.h"

namespace DartsScoreMultiAttemptContext {
    class AssembleDartsScoreByJson : public
            IUnaryService<const QByteArray&,
                          const IDartsScore*>
    {
    public:
        const IDartsScore* service(const QByteArray& json) override
        {
            return DartsScore::createInstance(json);
        }
    };
};



#endif // ASSEMBLEDARTSSCOREBYJSON_H
