#ifndef DARTSSTATUS_H
#define DARTSSTATUS_H

#include "src/DartsController/status/IDartsStatus.h"
#include "src/FileIO/filejsonio.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#define _FILE "status.dat"

class DartsStatus : public IDartsStatus {
public:
        virtual Status status() const override
        {
                return _status;
        }

        virtual void updateStatus(const Status& status) override
        {
                _status = status;
        }

        virtual void init() override
        {
                _status = Running;
        }

        virtual void initFromFile() override
        {
                FileJsonIO in(_FILE);
                auto json = in.read();
                auto jsonDoc = QJsonDocument::fromJson(json);
                auto jsonObj = jsonDoc.object();
                _status = static_cast<Status>(jsonObj["status"].toInt());
        }

        virtual bool saveState() override
        {
                QJsonObject jsonObj;
                jsonObj["status"] = _status;
                auto jsonDoc = new QJsonDocument(jsonObj);
                auto json = jsonDoc->toJson(QJsonDocument::Compact);
                FileJsonIO out(_FILE);
                return out.write(json);
        }

private:
        Status _status = Running;
};

#endif // DARTSSTATUS_H
