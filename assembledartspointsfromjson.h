#ifndef DARTSINPUTJSONEXTRACTOR_H
#define DARTSINPUTJSONEXTRACTOR_H

#include "iunaryservice.h"
#include "dartspointinput.h"
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include "qjsonobject.h"

namespace DartsModelsContext {
    class AssembleDartsPointsFromJson : public IUnaryService<
            const QJsonArray&,
            QVector<const IPlayerInput*>>
    {
    public:
        QVector<const IPlayerInput*> service(const QJsonArray &arr) override;
    private:
        const DartsModelsContext::DartsPointInput* assembleModelFromJsonObject(const QJsonObject& jsonObject);
    };
}


#endif // DARTSINPUTJSONEXTRACTOR_H
