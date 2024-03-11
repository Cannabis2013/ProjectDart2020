#include "dartsjsonreport.h"

#include "qjsondocument.h"
#include "src/DartsController/jsonReport/imessagesreport.h"
#include "src/DartsController/jsonReport/istatusreport.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/iscoresreport.h"
#include "src/DartsController/stats/istatsreport.h"
#include <QJsonArray>
#include <QJsonObject>

DartsJsonReport::DartsJsonReport(IStatsReport* statsReport,
    IScoresReport* scoresReport,
    IStatusReport* statusReport,
    IMessagesReport* messagesReport)
    : _statsReport(statsReport)
    , _scoresReport(scoresReport)
    , _statusReport(statusReport)
    , _messagesReport(messagesReport)
{
}

QByteArray DartsJsonReport::report()
{
        QJsonObject jsonObj;
        jsonObj["turnReport"] = _statusReport->report();
        jsonObj["statsReport"] = _statsReport->report();
        jsonObj["scoresReport"] = _scoresReport->report();
        jsonObj["messages"] = _messagesReport->report();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}
