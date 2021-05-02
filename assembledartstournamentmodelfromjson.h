#ifndef BUILDDARTSTOURNAMENTMODELFROMJSON_H
#define BUILDDARTSTOURNAMENTMODELFROMJSON_H

#include "ibinary.h"
#include "dartstournament.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QJsonArray>
#include "localplayermodelscontext.h"


class AssembleDartsTournamentModelFromJson : public
        IBinary<const QByteArray&,LocalPlayerModelsContext*,
        const IDartsTournament<QUuid,QString>*>
{
public:

    // IUnary interface
public:
    const IDartsTournament<QUuid,QString>* service(const QByteArray& json,LocalPlayerModelsContext* playerModelsService) override;
private:
    const IDartsTournament<QUuid,QString>* buildModelFromParameters(const QString &title, const int &gameMode, const int &keyPoint, const int &terminalKeyCode, const int &displayHint, const int &inputHint, const int &attempts, const QVector<QUuid> &playerIds);
};

#endif // BUILDDARTSTOURNAMENTMODELFROMJSON_H
