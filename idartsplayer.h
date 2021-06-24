#ifndef IDARTSPLAYER_H
#define IDARTSPLAYER_H

#include <quuid.h>
#include "ijson.h"

namespace DartsScoreControllerContext
{
    template<typename TUuid, typename TString>
    class IDartsPlayer : public IJson<QByteArray>
    {
    public:
        typedef TUuid IdFormat;
        typedef TString StringFormat;
        virtual IdFormat playerId() const = 0;
        virtual TString playerName() const = 0;
    };
}


#endif // IDARTSPLAYER_H
