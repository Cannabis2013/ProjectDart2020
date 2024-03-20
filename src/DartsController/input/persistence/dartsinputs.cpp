#include "dartsinputs.h"
#include "qjsonarray.h"
#include "src/DartsController/input/models/Input.h"
#include "src/FileIO/filejsonio.h"

DartsInputs::DartsInputs()
{
}

void DartsInputs::initFromFile()
{
        FileJsonIO jsonIO("dartsInputs.dat");
        auto jsonDoc = QJsonDocument::fromJson(jsonIO.read());
        if (!jsonDoc.isArray())
                return;
        auto arr = jsonDoc.array();
        for (auto ite = arr.begin(); ite != arr.end(); ++ite) {
                auto jsonObj = ite->toObject();
                _inputs.append(Input(jsonObj));
        }
}

QList<Input> DartsInputs::all() const
{
        return _inputs;
}

bool DartsInputs::saveState()
{
        FileJsonIO jsonIO("dartsInputs.dat");
        QJsonArray jsonArr;
        for (auto input : _inputs)
                jsonArr.append(input.toJsonObject());
        auto jsonDoc = new QJsonDocument(jsonArr);
        return jsonIO.write(jsonDoc->toJson(QJsonDocument::Compact));
}
