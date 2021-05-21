#include "assembledartstournamentmodelfromjson.h"

const IDartsTournament *AssembleDartsTournamentModelFromJson::service(const QByteArray &json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    // Extract Darts tournament values
    auto title = jsonObject.value("title").toString();
    auto gameMode = jsonObject.value("gameMode").toInt();
    auto keyPoint = jsonObject.value("keyPoint").toInt();
    auto terminalKeyCode = jsonObject.value("terminalKeyCode").toInt();
    auto displayHint = jsonObject.value("displayHint").toInt();
    auto inputHint = jsonObject.value("inputHint").toInt();
    auto attempts = jsonObject.value("attempts").toInt();
    auto model = buildModelFromParameters(title,gameMode,keyPoint,terminalKeyCode,
                                          displayHint,inputHint,attempts);

    return model;
}

const IDartsTournament *AssembleDartsTournamentModelFromJson::buildModelFromParameters(const QString &title,
                                                                                                       const int& gameMode,
                                                                                                       const int& keyPoint,
                                                                                                       const int& terminalKeyCode,
                                                                                                       const int& displayHint,
                                                                                                       const int& inputHint,
                                                                                                       const int& attempts)
{
    using namespace DartsModelsContext;
    auto model = DartsTournament::createInstance()
            ->setTitle(title)
            ->setKeyPoint(keyPoint)
            ->setGameMode(gameMode)
            ->setAttempts(attempts)
            ->setTerminalKeyCode(terminalKeyCode)
            ->setDisplayHint(displayHint)
            ->setInputMode(inputHint)
            ->setId(QUuid::createUuid());
    return model;
}

QVector<QUuid> AssembleDartsTournamentModelFromJson::assembleListOfQuuidsFromJsonArray(const QJsonArray &arr)
{
    QVector<int> list;
    for (const auto& jsonValue : arr) {
        list << jsonValue.toInt();
    }
}
