#include "dartscloseningfilter.h"
#include "src/FileIO/filejsonio.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/iscorescalculator.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"
#include "src/validation/iopeningfilter.h"

typedef QList<InputCandidate> Candidates;

DartsCloseningFilter::DartsCloseningFilter(ServiceCollection* services)
    : _services(services){}

void DartsCloseningFilter::init(bool enabled)
{
    _enabled = enabled;
    auto names = _services->players->names();
    _services->openingFilter->init(names,false);
}

const Candidates DartsCloseningFilter::filter(const Candidates &inputs)
{
    if(!_enabled)
        return inputs;
    Candidates accepted;
    auto turnIndex = _services->indexes->index().playerIndex();
    auto scoreObject = _services->scores->all().at(turnIndex);
    auto remaining = scoreObject.value();
    for (const auto &input : inputs) {
        auto score = _services->calculator->score(input.input());
        remaining -= score;
        accepted << input;
        if (remaining == 0 && (input.mod() == "D" || input.point() == 50))
            return accepted;
        else if (remaining < 0)
            return Candidates();
    }
    return accepted;
}

void DartsCloseningFilter::evaluateWinnerCondition() {
    auto scores = _services->scores->all();
    for (const auto& score : std::as_const(scores)) {
        auto player = &_services->playerFetcher->get(score.name());
        player->setWinner(score.value() <= 0);
    }
}

void DartsCloseningFilter::initFromFile() {
    FileJsonIO reader("closure.dat");
    auto jsonObj = reader.readAsJson().object();
    _enabled = jsonObj.value("enabled").toBool();
}

void DartsCloseningFilter::saveState() {
    FileJsonIO writer("closure.dat");
    QJsonObject jsonObj;
    jsonObj.insert("enabled",_enabled);
    writer.writeFromObject(jsonObj);
}
