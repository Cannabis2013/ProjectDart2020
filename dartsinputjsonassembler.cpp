#include "dartsinputjsonassembler.h"



QJsonArray DartsInputJsonAssembler::assembleDartsPointJson(const InputAssemblerContext::modelsList& modelsList)
{
    QJsonArray resultingJsonArray;
    for (const auto& model : modelsList) {
        auto ftpScoreModel = dynamic_cast<const DartsPointInput*>(model);
        QJsonObject scoreJSON;
        scoreJSON["Id"] = ftpScoreModel->id().toString();
        scoreJSON["Tournament"] = ftpScoreModel->tournament().toString();
        scoreJSON["PointValue"] = ftpScoreModel->point();
        scoreJSON["ScoreValue"] = ftpScoreModel->score();
        scoreJSON["RoundIndex"] = ftpScoreModel->roundIndex();
        scoreJSON["SetIndex"] = ftpScoreModel->setIndex();
        scoreJSON["Attempt"] = ftpScoreModel->attempt();
        scoreJSON["PlayerId"] = ftpScoreModel->player().toString();
        scoreJSON["Hint"] = ftpScoreModel->hint();
        scoreJSON["KeyCode"] = ftpScoreModel->modKeyCode();
        resultingJsonArray << scoreJSON;
    }
    return resultingJsonArray;
}

QJsonArray DartsInputJsonAssembler::assembleDartsScoreJson(const InputAssemblerContext::modelsList& modelsList)
{

}
