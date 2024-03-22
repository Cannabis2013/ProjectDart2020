#ifndef IDARTSSTATUS_H
#define IDARTSSTATUS_H

class IDartsStatus {
public:
        virtual void init() = 0;
        virtual void initFromStorage() = 0;
        virtual bool saveState() = 0;

        virtual void running() = 0;
        virtual void winnerFound() = 0;
        virtual bool isWinnerFound() const = 0;
};

#endif // IDARTSSTATUS_H
