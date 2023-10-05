#include "inputsio.h"
#include "src/FileIO/filejsonio.h"

#include <qjsonarray.h>

InputsIO::InputsIO(const QString &filePath): _filePath(filePath){}

bool InputsIO::toFile(const QList<DartInput>& _inputs)
{
        FileJsonIO jsonIO(_filePath);
        QJsonArray jsonArr;
        for (auto input : qAsConst(_inputs))
                jsonArr.append(input.toJsonObject());
        auto jsonDoc = new QJsonDocument(jsonArr);
        return jsonIO.write(jsonDoc->toJson());
}

QList<DartInput> InputsIO::fromFile() const
{
        FileJsonIO jsonIO(_filePath);
        auto jsonDoc = QJsonDocument::fromJson(jsonIO.read());
        QList<DartInput> inputs;
        if(!jsonDoc.isArray())
                return QList<DartInput>();
        auto arr = jsonDoc.array();
        for (auto ite = arr.begin(); ite != arr.end(); ++ite) {
                auto jsonObj = ite->toObject();
                inputs.append(DartInput::fromJson(jsonObj));
        }
        return inputs;
}
