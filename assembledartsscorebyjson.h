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
                          const DartsScore*>
    {
    public:
        const DartsScore* service(const QByteArray& json) override
        {
            return DartsScore::fromJson(json);
        }
    };
};



#endif // ASSEMBLEDARTSSCOREBYJSON_H
