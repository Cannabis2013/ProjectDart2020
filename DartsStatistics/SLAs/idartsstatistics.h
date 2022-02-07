#ifndef IDARTSSTATISTICS_H
#define IDARTSSTATISTICS_H
class QByteArray;
template<typename T>
class QVector;
class QString;
class IDartsStatistics
{
public:
    typedef QByteArray ByteArray;
    virtual void initPlayers(const ByteArray &data) = 0;
    virtual void initInputs(const ByteArray &data) = 0;
    virtual void reset() = 0;
    virtual void clear() = 0;
    virtual bool takeInput(const QString &name) = 0;
    virtual void update(const QString &name, const int &score, const int &modCode) = 0;
    virtual QByteArray createReport(const QString &name) const = 0;
};

#endif // IDARTSSTATISTICS_H
