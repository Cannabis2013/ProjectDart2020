#ifndef IDARTSCONTROLLERPLAYER_H
#define IDARTSCONTROLLERPLAYER_H

#include "ijson.h"

namespace DartsPointControllerContext {
    template<typename TUuid, typename TString, typename TJsonFormat>
    class IDartsControllerPlayer : public IJson<TJsonFormat>
    {
    public:
        typedef TUuid IdFormat;
        typedef TString StringFormat;
        typedef TJsonFormat JsonFormat;
        virtual IdFormat playerId() const = 0;
        virtual StringFormat playerName() const = 0;
        virtual JsonFormat toJson() const = 0;
    };
}

#endif // IDARTSCONTROLLERPLAYER_H
