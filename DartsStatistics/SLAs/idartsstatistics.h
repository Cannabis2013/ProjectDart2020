#ifndef IDARTSSTATISTICS_H
#define IDARTSSTATISTICS_H
#include <qobject.h>
class QByteArray;
template<typename T>
class QVector;
class QString;
class IDartsStatistics : public QObject
{
public:
    typedef QByteArray ByteArray;
    Q_INVOKABLE virtual void initPlayers(const ByteArray &data) = 0;
    Q_INVOKABLE virtual void initInputs(const ByteArray &data) = 0;
    Q_INVOKABLE virtual void reset() = 0;
    Q_INVOKABLE virtual void clear() = 0;
    Q_INVOKABLE virtual bool takeInput(const QString &name) = 0;
    Q_INVOKABLE virtual void update(const QString &name, const int &score, const int &modCode) = 0;
    Q_INVOKABLE virtual QByteArray createReport(const QString &name) const = 0;
};

#endif // IDARTSSTATISTICS_H
