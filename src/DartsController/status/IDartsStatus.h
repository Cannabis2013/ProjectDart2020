#ifndef IDARTSSTATUS_H
#define IDARTSSTATUS_H

class IDartsStatus {
public:
        enum Status {
                Running,
                Winner
        };
        
        virtual void init() = 0;
        virtual void initFromFile() = 0;

        virtual bool saveState() = 0;

        virtual Status status() const = 0;
        virtual void updateStatus(const Status& status) = 0;
};

#endif // IDARTSSTATUS_H
