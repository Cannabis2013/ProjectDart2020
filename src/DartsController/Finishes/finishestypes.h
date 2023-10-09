#ifndef FINISHESTYPES_H
#define FINISHESTYPES_H

#include <qvector.h>

namespace FinishesTypes {
        typedef QMultiHash<int, QString> TargetRow;
        typedef QVector<TargetRow*> TargetRows;
} // namespace DartsFinishes

#endif // FINISHESTYPES_H
