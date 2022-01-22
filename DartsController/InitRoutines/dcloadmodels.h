#ifndef DCLOADMODELS_H
#define DCLOADMODELS_H

#include "Models/dcmeta.h"

#include <qvector.h>
class DCInput;
template<typename T,typename U>
class IDCModelBuilder;
template<typename T,typename U>
class IDCModelsConverter;
class QJsonObject;
class DCPlayer;
template<typename T,typename U>
class IDCMetaBuilder;
class QByteArray;
class AbsDartsCtx;
class QUuid;
class DCLoadModels
{
public:
    // Typedefinitions
    typedef IDCMetaBuilder<DCMeta,QByteArray> MetaBuilder;
    typedef IDCModelsConverter<DCPlayer, QJsonObject> ConvertPlayers;
    typedef IDCModelBuilder<DCPlayer, QJsonObject> ConvertPlayer;
    typedef IDCModelsConverter<DCInput, QJsonObject> ConvertInputs;
    typedef IDCModelBuilder<DCInput, QJsonObject> ConvertInput;
    typedef QVector<DCPlayer> Players;
    typedef QVector<DCInput> Inputs;
    // Constructor
    DCLoadModels(MetaBuilder *metaBuilder,ConvertPlayer *convertPlayer, ConvertPlayers *convertPlayers,
                 ConvertInput *convertInput,ConvertInputs *convertInputs);
    // Load method
    void load(const QUuid &tournamentId, AbsDartsCtx *ctx);
    // Getters
    const DCMeta &meta() const;
    const Players &players() const;
    const Inputs &inputs() const;
private:
    DCMeta _meta;
    Players _players;
    Inputs _inputs;
    MetaBuilder *_metaBuilder;
    ConvertPlayer *_convertPlayer;
    ConvertPlayers *_convertPlayers;
    ConvertInput *_convertInput;
    ConvertInputs *_convertInputs;

};

#endif // DCLOADMODELS_H
