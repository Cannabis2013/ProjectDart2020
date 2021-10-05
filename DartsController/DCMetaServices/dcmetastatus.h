#ifndef DCMETASTATUS_H
#define DCMETASTATUS_H

#include "DartsController/DCMetaSLAs/idcstatus.h"
class DCMetaStatus : public IDCStatus
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
