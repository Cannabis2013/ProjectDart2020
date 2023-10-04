#ifndef IDARTSCONTROLLER_H
#define IDARTSCONTROLLER_H

#include <qbytearray.h>
#include <qstringlist.h>
#include <QObject>

class IDartsController : public QObject
{
public:
        virtual void init(const QStringList& playerNames) = 0;
        virtual void initFromSaved() = 0;
        virtual QByteArray turnInfo() const = 0;
        virtual QByteArray addInput(const QByteArray &json) = 0;
        virtual QByteArray undoTurn() = 0;
        virtual QByteArray redoTurn() = 0;
        virtual bool reset() = 0;
};

#endif // IDARTSCONTROLLER_H
