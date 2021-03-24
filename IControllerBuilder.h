#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,
         class TModelsContextInterface,
         class TApplicatonInterface,
         class TParameter,
         class TUserIds,
         class TUserNames,
         class TScoreValues>
class IControllerBuilder
{
public:
    virtual TControllerInterface *assembleFTPGameController(const TUserIds&,
                                                            const TParameter&,
                                                            const TUserIds&,
                                                            const TUserNames&,
                                                            const TScoreValues&,
                                                            TApplicatonInterface*,
                                                            TModelsContextInterface*) = 0;
};

#endif // ICONTROLLERBUILDER_H
