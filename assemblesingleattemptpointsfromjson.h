#ifndef DARTSINPUTJSONEXTRACTOR_H
#define DARTSINPUTJSONEXTRACTOR_H

#include "iunaryservice.h"
#include "dartspointinput.h"
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include "qjsonobject.h"

class AssembleSingleAttemptPointsFromJson : public IUnaryService<
        const QJsonArray&,
        QVector<const IDartsPointInput*>>
{
public:
    QVector<const IDartsPointInput *> service(const QJsonArray &arr) override;
private:
    const DartsPointInput* assembleModelFromJsonObject(const QJsonObject& JsonObject);
};

#endif // DARTSINPUTJSONEXTRACTOR_H
