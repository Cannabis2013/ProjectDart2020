#include "inputsio.h"
#include "src/FileIO/filejsonio.h"

#include <qjsonarray.h>

InputsIO::InputsIO(const QString &filePath): _filePath(filePath){}

bool InputsIO::toFile(const QList<Input>& _inputs)
{
        FileJsonIO jsonIO(_filePath);
        QJsonArray jsonArr;
        for (auto input : _inputs)
                jsonArr.append(input.toJsonObject());
        auto jsonDoc = new QJsonDocument(jsonArr);
        return jsonIO.write(jsonDoc->toJson(QJsonDocument::Compact));
}

QList<Input> InputsIO::fromFile() const
{
        FileJsonIO jsonIO(_filePath);
        auto jsonDoc = QJsonDocument::fromJson(jsonIO.read());
        QList<Input> inputs;
        if(!jsonDoc.isArray())
            return QList<Input>();
        auto arr = jsonDoc.array();
        for (auto ite = arr.begin(); ite != arr.end(); ++ite) {
                auto jsonObj = ite->toObject();
                inputs.append(Input(jsonObj));
        }
        return inputs;
}
