#ifndef IDARTSCONTROLLERDETAILS_H
#define IDARTSCONTROLLERDETAILS_H

namespace DartsBuilderContext {
    template<typename TUuid, typename TString>
    class IDartsControllerEntity
    {
    public:
        typedef TUuid IdFormat;
        typedef TString StringFormat;
        virtual IdFormat tournamentId() const = 0;
        virtual int keyPoint() const = 0;
        virtual int attempts() const = 0;
        virtual int terminalKeyCode() const = 0;
        virtual int inputHint() const = 0;
        virtual IdFormat winnerId() const = 0;
    };
}

#endif // IDARTSCONTROLLERDETAILS_H
