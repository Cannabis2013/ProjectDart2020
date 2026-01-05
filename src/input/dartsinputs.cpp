#include "dartsinputs.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "qjsonarray.h"
#include "src/FileIO/filejsonio.h"
#include "src/input/dartsinput.h"

void DartsInputs::init()
{
        _inputs = QList<DartsInput>();
}

void DartsInputs::setInputs(const QList<DartsInput>& inputs)
{
        _inputs = inputs;
}

void DartsInputs::initFromFile()
{
    _inputs.clear();
    FileJsonIO jsonIO(_filename);
    auto jsonDoc = QJsonDocument::fromJson(jsonIO.read());
    auto arr = jsonDoc.isArray() ?  jsonDoc.array() : QJsonArray();
    for (const auto& obj : std::as_const(arr)) {
        auto jsonObj = obj.toObject();
        _inputs.append(jsonObj);
    }
}

QList<DartsInput> DartsInputs::all() const
{
        return _inputs;
}

bool DartsInputs::saveState()
{
        FileJsonIO jsonIO(_filename);
        QJsonArray jsonArr;
        for (const auto &input : std::as_const(_inputs))
                jsonArr.append(input.toJsonObject());
        auto jsonDoc = new QJsonDocument(jsonArr);
        return jsonIO.write(jsonDoc->toJson(QJsonDocument::Compact));
}
