#ifndef DARTSCONTROLLERENTITY_H
#define DARTSCONTROLLERENTITY_H

#include "idartscontrollerentity.h"
#include <quuid.h>

namespace DartsBuilderContext {
    class DartsControllerEntity : public IDartsControllerEntity<QUuid,QString>
    {
    public:
        virtual IdFormat tournamentId() const override;
        void setTournamentId(const IdFormat &newTournamentId);
        virtual int keyPoint() const override;
        void setKeyPoint(int newKeyPoint);
        virtual int attempts() const override;
        void setAttempt(int newAttempt);
        virtual int terminalKeyCode() const override;
        void setTerminalKeyCode(int newTerminalKeyCode);
        virtual int inputHint() const override;
        void setInputHint(int newInputHint);
        virtual IdFormat winnerId() const override;
        void setWinnerId(const IdFormat &newWinnerId);
    private:
        IdFormat _tournamentId;
        IdFormat _winnerId;
        int _keyPoint;
        int _attempt;
        int _terminalKeyCode;
        int _inputHint;
    };
}


#endif // DARTSCONTROLLERENTITY_H
