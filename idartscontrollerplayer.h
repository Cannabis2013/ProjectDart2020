#ifndef IDARTSCONTROLLERPLAYER_H
#define IDARTSCONTROLLERPLAYER_H

namespace DartsPointControllerContext {
    template<typename TUuid, typename TString>
    class IDartsControllerPlayer
    {
    public:
        typedef TUuid IdFormat;
        typedef TString StringFormat ;
        virtual IdFormat playerId() const = 0;
        virtual StringFormat playerName() const = 0;
    };
}

#endif // IDARTSCONTROLLERPLAYER_H
