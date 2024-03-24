#ifndef INPUTCANDIDATE_H
#define INPUTCANDIDATE_H

#include "qjsonarray.h"
#include "src/input/models/dartsinput.h"
#include <QJsonObject>
#include <QString>

class InputCandidate {
public:
        static QList<InputCandidate> fromJsonArray(const QJsonArray& jsonArr)
        {
                QList<InputCandidate> candidates;
                for (const auto& jsonVal : jsonArr) {
                        auto jsonObj = jsonVal.toObject();
                        candidates << jsonObj;
                }
                return candidates;
        }

        QString mod() const
        {
                return _mod;
        }
        int point() const
        {
                return _point;
        }

        DartsInput input() const
        {
                return { _mod, _point };
        }

private:
        InputCandidate(const QJsonObject& jsonObj)
        {
                _mod = jsonObj.value("modId").toString("S");
                _point = jsonObj.value("point").toInt(-1);
        }

        QString _mod;
        int _point;
};

#endif // INPUTCANDIDATE_H
