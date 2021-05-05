#ifndef DARTSINPUTJSONEXTRACTOR_H
#define DARTSINPUTJSONEXTRACTOR_H

#include "iunaryservice.h"
#include "dartspointinput.h"
#include "dartsscoreinput.h"
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include "qjsonobject.h"



class DartsInputJsonExtractor : public IUnaryService<
        const QJsonArray&,
        QVector<const IModel<QUuid>*>>
{
public:
    QVector<const IModel<QUuid> *> service(const QJsonArray &arr) override;
private:
    const DartsPointInput* assembleModelFromJsonObject(const QJsonObject& JsonObject);
};

#endif // DARTSINPUTJSONEXTRACTOR_H
