#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,
         class TUuid,
         class TParameter,
         class TUserIds,
         class TUserNames,
         class TScores>
class IControllerBuilder
{
public:
    virtual TControllerInterface *assembleFTPGameController(const TUuid &tournament,
                                                            const TUuid &winner,
                                                            const TParameter &parameters,
                                                            const TUserIds& userIds,
                                                            const TUserNames& userNames,
                                                            const TScores& scores) = 0;
};

#endif // ICONTROLLERBUILDER_H
