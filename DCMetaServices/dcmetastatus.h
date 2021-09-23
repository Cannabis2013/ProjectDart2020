#ifndef DCMETASTATUS_H
#define DCMETASTATUS_H

#include "DCMetaSLAs/idcmetastatus.h"
class DCMetaStatus : public IDCMetaStatus
{
public:
    int get() const override
    {
        return _status;
    }
    void set(const int &newStatus) override
    {
        _status = newStatus;
    }
private:
    int _status;
};
#endif // DCMETASTATUS_H
