#ifndef ITOURNAMENTINPUTROUTER_H
#define ITOURNAMENTINPUTROUTER_H

#include <QObject>
#include <qbytearray.h>
#include <quuid.h>

class AbstractRouteByInputHint : public QObject
{
    Q_OBJECT
public slots:
    virtual void  processTournamentDetails(const QByteArray &json, const int &inputHint) = 0;
signals:
    void requestBuildDartsPointController(const QByteArray &json);
    void requestBuildDartsScoreController(const QByteArray &json);


};

#endif // ITOURNAMENTINPUTROUTER_H
