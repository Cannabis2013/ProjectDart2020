#ifndef IDARTSCONTROLLERDETAILS_H
#define IDARTSCONTROLLERDETAILS_H

#include <quuid.h>

namespace DCBuilding {
    class IDCMetaInfo
    {
    public:
        typedef QUuid IdFormat;
        typedef QString StringFormat;
        virtual IdFormat tournamentId() const = 0;
        virtual int keyPoint() const = 0;
        virtual int inputHint() const = 0;
        virtual int displayHint() const = 0;
        virtual IdFormat winnerId() const = 0;
    };
}
#endif // IDARTSCONTROLLERDETAILS_H
