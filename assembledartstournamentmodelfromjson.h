#ifndef BUILDDARTSTOURNAMENTMODELFROMJSON_H
#define BUILDDARTSTOURNAMENTMODELFROMJSON_H

#include "iunaryservice.h"
#include "dartstournament.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QJsonArray>
#include "iplayermodelsservice.h"


class AssembleDartsTournamentModelFromJson : public
        IUnaryService<const QByteArray&,
        const IDartsTournament*>
{
public:
    const IDartsTournament* service(const QByteArray& json) override;
private:
    const IDartsTournament* buildModelFromParameters(const QString &title,
                                                                    const int &gameMode,
                                                                    const int &keyPoint,
                                                                    const int &terminalKeyCode,
                                                                    const int &displayHint,
                                                                    const int &inputHint,
                                                                    const int &attempts);
};

#endif // BUILDDARTSTOURNAMENTMODELFROMJSON_H
