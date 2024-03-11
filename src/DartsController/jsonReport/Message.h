#ifndef MESSAGE_H
#define MESSAGE_H

#include <QJsonObject>
#include <QString>

class Message {
public:
        Message(const QString& message)
            : _message(message)
        {
        }

        QJsonObject jsonobject()
        {
                QJsonObject jsonObj;
                jsonObj["iconUrl"] = _iconUrl;
                jsonObj["content"] = _message;
                return jsonObj;
        }

        bool hasMessage()
        {
                return !_message.isEmpty();
        }

private:
        const QString _iconUrl = "qrc:/pictures/Ressources/Pictures/dartsplate.png";
        const QString _message;
};

#endif // MESSAGE_H
