#ifndef IDATAMODELBUILDER_H
#define IDATAMODELBUILDER_H

template<class TTournamentModel,
         class TTournamentParameters,
         class TScoreModel,
         class TScoreParameters,
         class TOptions>
class ITournamentModelBuilder
{
public:
    virtual TTournamentModel *buildTournamentModel(const TTournamentParameters&, const TOptions&) = 0;
    virtual TScoreModel *buildScoreModel(const TScoreParameters&, const TOptions&) = 0;
};

#endif // IDATAMODELBUILDER_H
