#ifndef DCMETA_H
#define DCMETA_H

#include "idcmetainfo.h"
#include <quuid.h>

namespace DCBuilding {
    class DCMeta : public IDCMetaInfo
    {
    public:
        virtual IdFormat tournamentId() const override;
        void setTournamentId(const IdFormat &newTournamentId);
        virtual int keyPoint() const override;
        void setKeyPoint(int newKeyPoint);
        virtual int inputHint() const override;
        void setInputHint(int newInputHint);
        virtual IdFormat winnerId() const override;
        void setWinnerId(const IdFormat &newWinnerId);
        int displayHint() const override;
        void setDisplayHint(const int hint);
    private:
        IdFormat _tournamentId;
        IdFormat _winnerId;
        int _keyPoint;
        int _attempt;
        int _terminalKeyCode;
        int _inputHint;
        int _displayHint;
    };
}


#endif // DARTSCONTROLLERENTITY_H
