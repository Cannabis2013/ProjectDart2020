#ifndef IDCUNDOTURN_H
#define IDCUNDOTURN_H

#include <qbytearray.h>

class IDCUndoTurn {
      public:
        virtual QByteArray undo() = 0;
};

#endif // IDCUNDOTURN_H
