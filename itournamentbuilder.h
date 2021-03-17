#ifndef IDATAMODELBUILDER_H
#define IDATAMODELBUILDER_H

template<class TTournamentModel,
         class TTournamentParameters,
         class TOptions>
class ITournamentBuilder
{
public:
    virtual TTournamentModel *buildFTPTournament(const TTournamentParameters&, const TOptions&) = 0;
    virtual TTournamentModel* editFTPTournament(const TTournamentModel*,
                                             const TTournamentParameters&,
                                             const TOptions&) = 0;
};

#endif // IDATAMODELBUILDER_H
