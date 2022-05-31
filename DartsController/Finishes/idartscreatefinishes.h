#ifndef IDARTSCREATEFINISHES_H
#define IDARTSCREATEFINISHES_H
#include "dartsconstructslas.h"
template<typename T, typename U>
class QMultiHash;
class QString;
template<typename T>
class QVector;
class IDartsCreateFinishes : public DartsConstructSLAs
{
public:
                typedef QMultiHash<int,QString> TargetRows;
                typedef QVector<TargetRows*> AllTargetRows;
                virtual AllTargetRows constructRows() const = 0;
};
#endif // IDARTSCONSTRUCTTARGETROW_H
