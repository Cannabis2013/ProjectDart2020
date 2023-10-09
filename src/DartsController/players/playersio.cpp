#include "playersio.h"
#include "qjsonarray.h"
#include "src/FileIO/filejsonio.h"

#include <QJsonDocument>

PlayersIO::PlayersIO(const QString& filePath)
{
        _filePath = filePath;
}

QStringList PlayersIO::initFromFile()
{
        QStringList names;
        FileJsonIO jsonIO(_filePath);
        auto jsonDoc = QJsonDocument::fromJson(jsonIO.read());
        if(!jsonDoc.isArray())
                return QStringList();
        const auto localArray =  jsonDoc.array();
        for (const auto &val : localArray)
                names.append(val.toString(""));
        return names;
}

bool PlayersIO::saveToFile(const QStringList& names)
{
        FileJsonIO jsonIO(_filePath);
        QJsonArray jsonArr;
        for (auto& name : qAsConst(names))
                jsonArr.append(name);
        auto jsonDoc = new QJsonDocument(jsonArr);
        return jsonIO.write(jsonDoc->toJson());
}
