#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,
         class TModelsContextInterface,
         class TApplicatonInterface,
         class TParameter,
         class TUuid>
class IControllerBuilder
{
public:
    virtual TControllerInterface *assembleFTPGameController(const TUuid& TTournamentId,
                                                            const TUuid& TWinnerId,
                                                            const TParameter&,
                                                            TApplicatonInterface*,
                                                            TModelsContextInterface*) = 0;
};

#endif // ICONTROLLERBUILDER_H
