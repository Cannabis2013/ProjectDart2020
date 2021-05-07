#include "assemblejsonarrayfromdartspoints.h"

QJsonArray AssembleJsonArrayFromDartsPoints::service(const QVector<const IDartsPointInput<QUuid> *> &modelsList)
{
    QJsonArray resultingJsonArray;
    for (const auto& model : modelsList) {
        auto ftpScoreModel = dynamic_cast<const DartsPointInput*>(model);
        QJsonObject scoreJSON;
        scoreJSON["Id"] = ftpScoreModel->id().toString();
        scoreJSON["Tournament"] = ftpScoreModel->tournament().toString();
        scoreJSON["PointValue"] = ftpScoreModel->point();
        scoreJSON["RoundIndex"] = ftpScoreModel->roundIndex();
        scoreJSON["SetIndex"] = ftpScoreModel->setIndex();
        scoreJSON["Attempt"] = ftpScoreModel->attempt();
        scoreJSON["PlayerId"] = ftpScoreModel->playerId().toString();
        scoreJSON["Hint"] = ftpScoreModel->hint();
        scoreJSON["KeyCode"] = ftpScoreModel->modKeyCode();
        resultingJsonArray << scoreJSON;
    }
    return resultingJsonArray;
}
