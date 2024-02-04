#ifndef IDARTSSTATISTICS_H
#define IDARTSSTATISTICS_H

class QString;
class QJsonObject;

class IDartsStatistics {
public:
        virtual QJsonObject report(const QString& name) const = 0;
};

#endif // IDARTSSTATISTICS_H
