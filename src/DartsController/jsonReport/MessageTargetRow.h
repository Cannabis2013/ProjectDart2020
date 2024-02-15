#ifndef MESSAGETARGETROW_H
#define MESSAGETARGETROW_H

#include <QJsonObject>
#include <QString>

class MessageTargetRow {
public:
        MessageTargetRow(const QString& message)
            : _message(message)
        {
        }

        bool hasRow()
        {
                return _message != QString();
        }

        QJsonObject jsonobject()
        {
                QJsonObject jsonObj;
                jsonObj["iconUrl"] = _iconUrl;
                jsonObj["content"] = _message;
                return jsonObj;
        }

private:
        const QString _iconUrl = "qrc:/pictures/Ressources/Pictures/dartsplate.png";
        const QString _message;
};

#endif // MESSAGETARGETROW_H
