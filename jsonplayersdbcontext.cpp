#include "jsonplayersdbcontext.h"

using namespace PlayersContext;

void JsonPlayersDbContext::fetchModels()
{
    try {
        _playerModels = createModelsFromJson()->create(readJsonFromFile()->read());
    } catch (...) {
        return;
    }
}

void JsonPlayersDbContext::saveState()
{
    writeJsonToFile()->write(createJsonFromModels()->createJson(_playerModels));
}

QVector<const IModel<QUuid> *> JsonPlayersDbContext::models() const
{
    return _playerModels;
}

void JsonPlayersDbContext::add(const IModel<QUuid> *player)
{
    _playerModels.append(player);
    saveState();
}

bool JsonPlayersDbContext::remove(const int &index)
{
    _playerModels.remove(index);
    saveState();
    return true;
}

int JsonPlayersDbContext::indexOf(const IModel<QUuid> *player) const
{
    auto index = _playerModels.indexOf(player);
    return index;
}

void JsonPlayersDbContext::replace(const int &index, const IModel<QUuid> *player)
{
    _playerModels.replace(index,player);
    saveState();
}

const IModel<QUuid> *JsonPlayersDbContext::model(const int &index) const
{
    auto count = _playerModels.count();
    if(index >= count)
        throw "Index out of range";
    auto model = _playerModels.at(index);
    return model;
}
