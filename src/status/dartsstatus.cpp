#include "dartsstatus.h"
#include "src/FileIO/filejsonio.h"

void DartsStatus::init()
{
        _status = Running;
}

void DartsStatus::initFromStorage()
{
        FileJsonIO in(_filename);
        auto json = in.read();
        auto jsonDoc = QJsonDocument::fromJson(json);
        auto jsonObj = jsonDoc.object();
        _status = static_cast<Status>(jsonObj["status"].toInt());
}

bool DartsStatus::saveState()
{
        QJsonObject jsonObj;
        jsonObj["status"] = _status;
        auto jsonDoc = new QJsonDocument(jsonObj);
        auto json = jsonDoc->toJson(QJsonDocument::Compact);
        FileJsonIO out(_filename);
        return out.write(json);
}

void DartsStatus::winnerFound()
{
        _status = DartsStatus::Winner;
}

void DartsStatus::running()
{
        _status = DartsStatus::Running;
}

bool DartsStatus::isWinnerFound() const
{
        return _status == DartsStatus::Winner;
}

DartsStatus::DartsStatus(const QString& filename)
    : _filename(filename)
{
}
