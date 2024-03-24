#include "dartsinputs.h"
#include "qjsonarray.h"
#include "src/input/models/dartsinput.h"
#include "src/FileIO/filejsonio.h"

DartsInputs::DartsInputs(const QString& filename)
    : _filename(filename)
{
}

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
        FileJsonIO jsonIO(_filename);
        auto jsonDoc = QJsonDocument::fromJson(jsonIO.read());
        if (!jsonDoc.isArray())
                return;
        auto arr = jsonDoc.array();
        for (auto ite = arr.begin(); ite != arr.end(); ++ite) {
                auto jsonObj = ite->toObject();
                _inputs.append(DartsInput(jsonObj));
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
        for (auto input : _inputs)
                jsonArr.append(input.toJsonObject());
        auto jsonDoc = new QJsonDocument(jsonArr);
        return jsonIO.write(jsonDoc->toJson(QJsonDocument::Compact));
}
