#ifndef IADDTOTALSCORETODARTSPOINTS_H
#define IADDTOTALSCORETODARTSPOINTS_H

#include "idartscontrollerpoint.h"
#include "idartscontrollerplayer.h"
#include <qvector.h>
#include <quuid.h>

namespace DartsPointControllerContext {
    class IAddTotalScoreToDartsInputs
    {
    public:
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> InputModel;
        typedef QVector<const InputModel *> InputModels;
        virtual void addTotalScoreToInputs(const InputModels &inputs, const int &initialPoint) const = 0;
    };
}


#endif // IADDTOTALSCORETODARTSPOINTS_H
