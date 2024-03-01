#ifndef IMESSAGESREPORT_H
#define IMESSAGESREPORT_H

class QJsonArray;

class IMessagesReport {
public:
        virtual QJsonArray report() const = 0;
};

#endif // IMESSAGESREPORT_H
