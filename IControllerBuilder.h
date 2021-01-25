#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,
         class TModelsContextInterface,
         class TApplicatonInterface,
         class TParameter,
         class TUserIds,
         class TUserNames>
class IControllerBuilder
{
public:
    virtual TControllerInterface *assembleFTPGameController(const TUserIds& tournamentIds,
                                                            const TParameter &values,
                                                            const TUserIds& userIds,
                                                            const TUserNames& userNames,
                                                            TApplicatonInterface* applicationInterface,
                                                            TModelsContextInterface* modelsContext) = 0;
};

#endif // ICONTROLLERBUILDER_H
