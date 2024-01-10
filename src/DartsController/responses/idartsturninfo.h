#ifndef IDARTSTURNINFO_H
#define IDARTSTURNINFO_H

#include <qbytearray.h>

class IDartsTurnInfo {
public:
        virtual QByteArray report() = 0;
};

#endif // IDARTSTURNINFO_H
